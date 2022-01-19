
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

#include "../linux/net_linux.h"
#include "../net.h"
#include "EpollStream.h"

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
