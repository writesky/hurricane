
#include "../../iocp/IOCPServer.h"
#include "../../iocp/IOCPLoop.h"
#include "../../utils/logger.h"
#include "../../utils/common_utils.h"
#include <cstdint>
#include <cassert>
#include <memory>
#include <WS2tcpip.h>

#ifndef DISABLE_ASSERT
#ifdef assert
#undef assert
#endif

#define assert(x)
#endif

namespace meshy{
    IOCPServer::IOCPServer() :_completionPort(nullptr),_socket(0),_dataSink(nullptr),_ioOperationDataGroup(){
        WindowsSocketInitializer::Initialize();  //window的API进行初始化
    }

    IOCPServer::~IOCPServer() {
    }

    int32_t IOCPServer::Bind(const std::string host, int32_t port) {
        _completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);  //创建端口
        if (nullptr == _completionPort) {
            TRACE_ERROR("CreateIoCompletionPort failed. Error: " + GetLastError());
            assert(false);
            return -1;
        }

        SOCKET listenfd= socket(AF_INET,SOCK_STREAM,0);  //创建套接字
        SetNativeSocket(listenfd);

        SOCKADDR_IN srvAddr;
        inet_pton(AF_INET, host.c_str(), &(srvAddr.sin_addr));
        srvAddr.sin_family = AF_INET;
        srvAddr.sin_port = htons(port);
        int32_t errorCode = ::bind(listenfd, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR));  //bind函数绑定套接字
        if (SOCKET_ERROR == errorCode) {
            TRACE_ERROR("Bind failed. Error: " + GetLastError());
            assert(false);
            return errorCode;
        }

        return 0;
    }

    int32_t IOCPServer::Listen(DataSink *dataSink, int32_t backlog) {
        int32_t listenfd = GetNativeSocket();
        int32_t errorCode = listen(listenfd, backlog);  //在套接字上监听
        if (-1 == errorCode) {
            TRACE_ERROR("Listen socket failed!");
            assert(0);
            return errorCode;
        }

        this->SetDataSink(dataSink);
        IOCPLoop::Get()->AddServer(this);  //保存用户传入的数据接收器，并将服务器添加到IOCPLoop中

        return 0;
    }

    void IOCPServer::SetDataSink(DataSink *dataSink) {
        _dataSink=dataSink;
    }

    DataSink* IOCPServer::GetDataSink() const
    {
        return _dataSink;
    }

    void IOCPServer::SetCompletionPort(HANDLE completionPort)
    {
        _completionPort = completionPort;
    }

    HANDLE IOCPServer::GetCompletionPort() const
    {
        return _completionPort;
    }


    void IOCPServer::OnConnectIndication(ConnectIndicationHandler handler) {
        this->_connectHandler = handler;

    }
    void IOCPServer::OnDisconnectIndication(DisconnectIndicationHandler handler) {
        this->_disconnectHandler = handler;
    }


    //好好理解，302页
    WSAConnectionPtr IOCPServer::Accept(int32_t listenfd) {
        SOCKADDR_IN saRemote;
        int RemoteLen;
        SOCKET acceptSocket;

        RemoteLen = sizeof(saRemote);
        acceptSocket = accept(GetNativeSocket(), (SOCKADDR*)&saRemote, &RemoteLen); // blocked
        if (SOCKET_ERROR == acceptSocket)
        {
            std::cerr << "Accept Socket Error: " << GetLastError() << std::endl;
            throw std::exception("Accept Socket Error: ");
        }

        WSAConnectionPtr connection = std::make_shared<WSAConnection>(acceptSocket, saRemote);
        connection->SetDataSink(GetDataSink());

        IOCP::OperationDataPtr perIOData = IOCP::CreateOperationData(connection, this->GetCompletionPort());
        _ioOperationDataGroup.push_back(perIOData);
        connection->SetOperationData(perIOData);

        DWORD flags = 0;
        DWORD RecvBytes = 0;
        WSARecv(connection->GetNativeSocket(),
                &(connection->GetOperationData()->databuff), 1, &RecvBytes, &flags,
                &(connection->GetOperationData()->overlapped), NULL);

        return connection;
    }
}