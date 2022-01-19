
#include "../../iocp/IOCPLoop.h"
#include "../../iocp/IOCPConnection.h"
#include "../../IoLoop.h"
#include "../../utils/logger.h"

#include "../../eventqueue.h"

#include <thread>
#include <vector>
#include <iostream>

namespace meshy{

    IOCPLoop *IOCPLoop::Get() {
        static IOCPLoop IOCPLoop;  //线程安全的静态变量初始化
        return &IOCPLoop;
    }

    void IOCPLoop::AddServer(IOCPServer *server) {   //将服务器指针添加到服务器队列中
        _serverQueue.Push(IOCPServer* server);
    }

    IOCPLoop::IOCPLoop() :_dataSink(nullptr),_shutdown(false),_systemInfo(),_servers(),_streams(){
        GetSystemInfo(&_systemInfo);  //获取系统信息
    }

    IOCPLoop::~IOCPLoop() {
    }

    void IOCPLoop::_Run() {
        auto iocpFunc=std::bind(&IOCPLoop::_IOCPThread,this);  //绑定成员函数
        std::thread iocpThread(iocpFunc);  //启动线程
        iocpThread.detach();
    }

    void IOCPLoop::_Initialize()
    {

    }

    void IOCPLoop::_IOCPThread() {  //主线程函数
        TRACE_DEBUG("Server ready, wait for new connection ...");
        HANDLE completionPort = IOCP::GetCompletionPort();  //创建端口

        while (!_shutdown) {  //无限循环
            IOCPServer* server = nullptr;
            _serverQueue.Pop(server, true); // blocked process
            NativeSocket listenfd = server->GetNativeSocket();  //获取服务器
            server->SetCompletionPort(completionPort);  //从服务器队列获取服务器并将该套接字与创建的端口绑定，可以通过端口通知该套接字事件

            if (nullptr != server)
            {
                // Create the threads for the server according to the number of processors
                for (DWORD i = 0; i < (_systemInfo.dwNumberOfProcessors * 2); ++i) {
                    // Create server worker thread and pass the completion port to the thread.
                    auto workerFunc = std::bind(&IOCPLoop::_WorkThread, this, listenfd, completionPort);//从服务器队列获取服务器并将该套接字与创建的端口绑定，可以通过端口通知该套接字事件
                    std::thread workerThread(workerFunc);
                    workerThread.detach();
                }

                // Handle accept
                auto connectionFunc = std::bind(&IOCPLoop::_IOCPConnectionThread, this, server);
                std::thread acceptThread(connectionFunc);
                acceptThread.detach();
            }
        }
    }

    void IOCPLoop::_IOCPConnectionThread(IOCPServer *server) {  //接收服务器链接的线程函数
        while(!_shutdown){
            std::cout << "to accept" << std::endl;
            WSAConnectionPtr connection=server->Accept(server->GetNativeSocket());  //接受链接
            if (connection != nullptr) {
                _streams[connection->GetNativeSocket()] = connection;  //将连接保存到循环的数据流列表中保存起来
            }
        }
    }

    void IOCPLoop::_Enqueue(IOCPStreamPtr stream, const char* buf, int64_t nread)  //将从数据流中接收到的数据上传到应用层
    {
        TRACE_DEBUG("_Enqueue");
        if (stream->GetDataSink()) {
            TRACE_DEBUG("_Enqueue, datasink registered.");
            stream->GetDataSink()->OnDataIndication(stream.get(), buf, nread);  //OnDataIndication回调实现上传
        }
    }

    void IOCPLoop::SetDataSink(DataSink* dataSink) {
        _dataSink = dataSink;
    }

    void IOCPLoop::_WorkThread(int32_t listenfd, int completionPort) {
        DWORD bytesReceived;
        LPOVERLAPPED lpOverlapped;
        PULONG key = 0;
        IOCP::OperationData* perIOData = nullptr;
        DWORD flags = 0;
        BOOL result = false;

        while (!_shutdown) {
            // Check the errors of socket
            result = GetQueuedCompletionStatus(completionPort, &bytesReceived, (PULONG_PTR)&key, (LPOVERLAPPED*)&lpOverlapped, INFINITE);  //从端口中获取事件
            if (0 == result) {
                TRACE_ERROR("GetQueuedCompletionStatus Error: " + GetLastError());
                if (nullptr != lpOverlapped) {
                    // TODO: 显示删除
                }
                continue;
            }

            //从重叠结构体中获取表示连接的原始结构体，并将接收到的数据与数据长度通过_Enqueue传递到上层应用中
            perIOData = (IOCP::OperationData*)CONTAINING_RECORD(lpOverlapped, IOCP::OperationData, overlapped);

            if ( 0 == bytesReceived) {
                perIOData->stream = nullptr;
                delete perIOData;
                continue;
            }

            // Begin to process data received from client.
            //ByteArray data(perIOData->databuff.buf, bytesReceived);
            //if ( _dataSink ) {
            //	_dataSink->OnDataIndication(perIOData->stream, perIOData->databuff.buf, bytesReceived);
            //}

            IOCPStreamPtr stream = _streams[perIOData->stream->GetNativeSocket()];
            this->_Enqueue(stream, perIOData->databuff.buf, bytesReceived);
            IOCP::ResetOperationData(perIOData); //重置io数据结构体

            DWORD RecvBytes;
            // Receive normal data.
            DWORD Flags = 0;

            WSARecv(stream->GetNativeSocket(),
                    &(stream->GetOperationData()->databuff), 1, &RecvBytes, &Flags,
                    &(stream->GetOperationData()->overlapped), NULL);
        }
    }
}