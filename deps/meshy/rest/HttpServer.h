

#ifndef HURRICANE_HTTPSERVER_H
#define HURRICANE_HTTPSERVER_H

#include "../Meshy.h"
#include "HttpConnection.h"
#include <vector>
#include <functional>

namespace meshy{
    class IoLoop;

    class HttpServer{
    public:
        typedef std::function<void(HttpConnection* connection)> ConnectionHandler;  //处理用户连接

        HttpServer();
        virtual ~HttpServer();

        void Listen(const std::string& host,int port,int backlog=20);  //监听用户请求
        void OnConnection(ConnectionHandler handler){   //设置处理连接事件的回调函数
            _connectionHandler=handler;
        }
    private:
        TcpServer _server;
        ConnectionHandler _connectionHandler;
    };
}
#endif //HURRICANE_HTTPSERVER_H
