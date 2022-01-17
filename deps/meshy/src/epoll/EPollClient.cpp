//
// Created by yankaixin on 2022/1/3.
//
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollClient.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/common_utils.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollLoop.h"
#include <unistd.h>
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/logger.h"

namespace meshy{
    void EPollclient::Connect(const std::string &host, int32_t port) {
        struct sockaddr_in serv_addr;

        bzero((char* ) &serv_addr,sizeof (serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(host.c_str());  //初始化服务器地址
        serv_addr.sin_port = htons(port);

        meshy::SetNonBlocking(GetNativeSocket());  //设为非阻塞模式

        connect(GetNativeSocket(),(struct sockaddr* )& serv_addr, sizeof(serv_addr));  //连接到服务器
    }

    EPollclientPtr EPollclient::Connect(const std::string &ip, int32_t port, DataSink *dataSink) {
        int32_t clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //创建客户端套接字
        //connect
        EPollclientPtr client=EPollclientPtr (new EPollclient(clientSocket));  //生成客户端对象
        client->SetDataSink(dataSink);  //将数据接收器赋予客户端
        client->Connect(ip,port);

        EPollLoop *ePollLoop=EPollLoop::Get();   //获取EPollLoop并将新创建的客户端套接字绑定到epoll中

        client->_events=EPOLLIN | EPOLLET;
        if ( ePollLoop->AddEpollEvents(client->_events, clientSocket) == -1 ) {
            perror("epoll_ctl: add");
            exit(EXIT_FAILURE);
        }

        ePollLoop->AddStream(client);

        return client;
    }

    int32_t EPollclient::Receive(char *buffer, int32_t bufferSize, int32_t &readSize) {
        readSize=0;
        int32_t nread=0;
        NativeSocketEvent ev;

        while ((nread = read(GetNativeSocket(), buffer + readSize, bufferSize - 1)) > 0) {  //不断从链接套接字中获取数据
            readSize += nread;
        }

        return nread;
    }

    int32_t EPollclient::Send(const ByteArray &byteArray) {
        TRACE_DEBUG("EPollConnection::Send");

        struct epoll_event ev;
        NativeSocket clientSocket = GetNativeSocket();
        if ( EPollLoop::Get()->ModifyEpollEvents(_events | EPOLLOUT, clientSocket) ) {
            // TODO: MARK ERASE
            TRACE_ERROR("FATAL epoll_ctl: mod failed!");
        }

        const char *buf = byteArray.data();
        int32_t size = byteArray.size();
        int32_t n = size;

        while (n > 0) {
            int32_t nwrite;
            nwrite = write(clientSocket, buf + size - n, n);
            if (nwrite < n) {
                if (nwrite == -1 && errno != EAGAIN) {
                    TRACE_ERROR("FATAL write data to peer failed!");
                }
                break;
            }
            n -= nwrite;
        }

        return 0;
    }
}
