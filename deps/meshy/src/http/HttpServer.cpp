
#include "../../rest/HttpServer.h"
#include "../../rest/HttpConnection.h"
#include "../../PackageDataSink.h"

namespace meshy{
    HttpServer::HttpServer() {
    }

    HttpServer::~HttpServer() {
    }

    void HttpServer::Listen(const std::string &host, int port, int backlog) {  //监听客户端请求
        _server.Listen(host,port,backlog);

        _server.OnConnectIndication([this](IStream* stream){  //在tcp服务器上注册连接事件
            TcpConnection* connection=dynamic_cast<TcpConnection*>(stream);
            HttpConnection* httpConnection=new HttpConnection(connection);
            if ( _connectionHandler ) {
                _connectionHandler(httpConnection);
            }
        });
    }
}