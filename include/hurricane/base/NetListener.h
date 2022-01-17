//
// Created by yankaixin on 2021/12/23.
//

#ifndef HURRICANE_NETLISTENER_H
#define HURRICANE_NETLISTENER_H
#pragma once

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/NetAddress.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/net.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"

#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <functional>
#include <cstdint>
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"

typedef std::function<void (meshy::TcpStream* connection,const char* buffer,int32_t size)> DataReceiver;  //数据接收处理函数

class NetListener{  //网络监听器
public:
    NetListener(const hurricane::base::NetAddress& host):
    _host(host){
    }

    const hurricane::base::NetAddress& GetHost() const{
        return _host;
    }

    void SetHost(const hurricane::base::NetAddress& host){
        _host=host;
    }

    void StartListen();  //启动网络监听器

    void DataThreadMain(std::shared_ptr<meshy::TcpConnection> connection);  //网络监听器线程入口
    void OnData(DataReceiver receiver){  //注册监听数据消息的回调函数
        _receiver=receiver;
    }
private:
    hurricane::base::NetAddress _host;
    DataReceiver _receiver;
    meshy::TcpServer _server;
};
#endif //HURRICANE_NETLISTENER_H
