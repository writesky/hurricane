//
// Created by yankaixin on 2022/1/3.
//

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollSever.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollLoop.h"
#include <unistd.h>
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/logger.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/common_utils.h"
#include <cstdint>
#include <cassert>

#ifndef DISABLE_ASSERT
#ifdef assert
#undef assert
#endif

#define assert(x)
#endif

namespace meshy{
    int32_t EPollServer::_Bind(const std::string &host, int32_t port) {
        int32_t listenfd;
        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  //生成服务器套接字·
            TRACE_ERROR("Create socket failed!");
            exit(1);
        }

        SetNativeSocket(listenfd);
        int32_t option = 1;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        // make socket non-blocking
        meshy::SetNonBlocking(listenfd);

        NativeSocketAddress addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(host.c_str());

        int32_t errorCode = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
        if (errorCode < 0) {
            TRACE_ERROR("Bind socket failed!");
            assert(0);
            return errorCode;
        }

        return 0;
    }

    int32_t EPollServer::Listen(const std::string &host, int32_t port, int32_t backlog) {  //启动监听服务
        _Bind(host,port);
        int32_t listenfd = GetNativeSocket();

        int32_t errorCode = listen(listenfd, backlog);  //启动监听
        if (-1 == errorCode) {
            TRACE_ERROR("Listen socket failed!");
            assert(0);
            return errorCode;
        }

        errorCode = EPollLoop::Get()->AddEpollEvents(EPOLLIN, listenfd);//监听成功则将套接字加入EPoll循环队列中

        if (errorCode == -1) {
            TRACE_ERROR("FATAL epoll_ctl: listen_sock!");
            assert(0);
            return errorCode;
        }

        EPollLoop::Get()->AddServer(listenfd, this);  //将自身作为服务器添加到EPollLoop中
    }

    EPollConnectionPtr EPollServer::Accept(int32_t sockfd) {
        int32_t conn_sock;
        int32_t addrlen;
        int32_t remote;

        int32_t listenfd = GetNativeSocket();
        while ((conn_sock = accept(listenfd, (struct sockaddr *) &remote,  //获得链接
                                   (socklen_t * ) & addrlen)) > 0) {
            meshy::SetNonBlocking(conn_sock);

            NativeSocketEvent ev;
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;

            if (epoll_ctl(sockfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                perror("epoll_ctl: add");
                exit(EXIT_FAILURE);
            }

            EPollConnectionPtr connection = std::make_shared<EPollConnection>(conn_sock);
            if ( _connectHandler ) {
                _connectHandler(connection.get());
            }

            return connection;
        } // while

        if (conn_sock == -1) {
            if (errno != EAGAIN && errno != ECONNABORTED
                && errno != EPROTO && errno != EINTR)
                perror("accept");
        }

        return EPollConnectionPtr(nullptr);
    }
}