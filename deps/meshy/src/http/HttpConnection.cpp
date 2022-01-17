//
// Created by yankaixin on 2022/1/3.
//

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpConnection.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/bytearray.h"
#include <iostream>

namespace meshy{
    HttpConnection::HttpConnection(TcpConnection* connection) :
            _connection(connection) {
        std::cout << _connection << std::endl;
        auto tcpDataHandler = std::bind(&::meshy::HttpConnection::HandleData, this, std::placeholders::_1, std::placeholders::_2);
        _connection->OnDataIndication(tcpDataHandler);
    }

    void HttpConnection::HandleData(const char *buffer, int64_t size) {
        std::cout << buffer << std::endl;
        std::cout << size << std::endl;
        std::string requestText(buffer, size);

        _request.ParseStdString(requestText);

        if ( _requestHandler ) {
            _requestHandler(_request);
        }

        if ( _dataHandler && _request.GetContent().size() > 0 ) {
            _dataHandler(_request.GetContent());
        }
    }

    void HttpConnection::SendResponse(const HttpResponse &response) {
        _response=response;

        _connection->Send(ByteArray(_response.ToStdString())); //将用户指定的响应体抓换成字符串，发送出去即可
    }
}