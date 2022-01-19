#ifndef HURRICANE_MESHY_H
#define HURRICANE_MESHY_H

#include "epoll/EPollClient.h"
#include "epoll/EpollConnection.h"
#include "epoll/EPollSever.h"
#include "epoll/EPollClient.h"

namespace meshy {
    typedef EPollServer TcpServer;
    typedef EPollConnection TcpConnection;
    typedef EPollclient TcpClient;
    typedef EPollStream TcpStream;
}
#endif //HURRICANE_MESHY_H
