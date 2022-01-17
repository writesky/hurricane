//
// Created by yankaixin on 2022/1/3.
//

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpServer.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpConnection.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/PackageDataSink.h"

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