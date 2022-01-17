//
// Created by yankaixin on 2021/12/26.
//

#ifndef HURRICANE_NET_LINUX_H
#define HURRICANE_NET_LINUX_H
#include <cstdint>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>

namespace meshy{
    typedef int32_t NativeSocket;
    typedef ::sockaddr_in NativeSocketAddress;
    typedef ::epoll_event NativeSocketEvent;
}
#endif //HURRICANE_NET_LINUX_H
