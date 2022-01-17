//
// Created by yankaixin on 2021/12/26.
//

#ifndef HURRICANE_EPOLLCONNECTION_H
#define HURRICANE_EPOLLCONNECTION_H

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/linux/net_linux.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/net.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EpollStream.h"

namespace meshy{
    class EPollLoop;

    class EPollConnection:public EPollStream{
    public:
        EPollConnection(NativeSocket nativeSocket):
                EPollStream(nativeSocket){
        }

        virtual ~EPollConnection(){}

        EPollConnection(const EPollConnection& connection)=delete;
    };
    typedef std::shared_ptr<EPollConnection> EPollConnectionPtr;
}
#endif //HURRICANE_EPOLLCONNECTION_H
