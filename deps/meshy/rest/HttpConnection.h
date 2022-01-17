//
// Created by yankaixin on 2021/12/28.
//

#ifndef HURRICANE_HTTPCONNECTION_H
#define HURRICANE_HTTPCONNECTION_H

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpResponse.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpRequest.h"
#include <functional>

namespace meshy{
    class HttpConnection{
    public:
        typedef std::function<void(const HttpRequest& request)> RequestHandler;  //Http请求到来时的回调函数
        typedef std::function<void(const std::string& data)> DataHandler;  //Http数据到来时的回调函数

        HttpConnection(TcpConnection* connection);

        void HandleData(const char* buffer,int64_t size);  //处理TCP连接的数据时间，将其翻译成HTTP消息

        void OnData(DataHandler dataHandler) {
            _dataHandler = dataHandler;
        }

        void OnRequest(RequestHandler requestHandler) {
            _requestHandler = requestHandler;
        }

        void SendResponse(const HttpResponse& response);  //发送HTTP响应
    private:
        TcpConnection* _connection;
        HttpRequest _request;
        HttpResponse _response;
        DataHandler _dataHandler;
        RequestHandler _requestHandler;
    };
}
#endif //HURRICANE_HTTPCONNECTION_H
