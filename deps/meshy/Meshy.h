//
// Created by yankaixin on 2021/12/22.
//

#ifndef HURRICANE_MESHY_H
#define HURRICANE_MESHY_H

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollClient.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EpollConnection.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollSever.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollClient.h"

namespace meshy {
    typedef EPollServer TcpServer;
    typedef EPollConnection TcpConnection;
    typedef EPollclient TcpClient;
    typedef EPollStream TcpStream;
}
#endif //HURRICANE_MESHY_H
