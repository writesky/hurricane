//
// Created by yankaixin on 2021/12/22.
//

#ifndef HURRICANE_NETCONNECTOR_H
#define HURRICANE_NETCONNECTOR_H
#pragma once

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/NetAddress.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"

#include <cstdint>
#include <memory>

class NetConnector{
public:
    NetConnector(const hurricane::base::NetAddress& host):_host(host){
    }

    const hurricane::base::NetAddress& GetHost() const{
        return _host;
    }

    void SetHost(const hurricane::base::NetAddress& host){
        _host=host;
    }

    void Connect();
    int32_t SendAndReceive(const char* buffer,int32_t size,char* resultBuffer,int32_t resultSize);  //连接到某个服务器并与之通信
private:
    hurricane::base::NetAddress _host;
    std::shared_ptr<meshy::TcpClient> _client;
};
#endif //HURRICANE_NETCONNECTOR_H
