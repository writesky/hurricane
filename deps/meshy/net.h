//
// Created by yankaixin on 2021/12/23.
//

#ifndef HURRICANE_NET_H
#define HURRICANE_NET_H

#pragma once


#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/linux/net_linux.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/bytearray.h"
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <unistd.h>

namespace meshy{
    class Socket{
    public:
        Socket():_nativeSocket(0){
        }

        Socket(NativeSocket nativeSocket):_nativeSocket(nativeSocket){
        }


        virtual ~Socket(){
            close(_nativeSocket);
        }

        NativeSocket GetNativeSocket() const{
            return _nativeSocket;
        }

        void SetNativeSocket(NativeSocket nativeSocket){  //设置本地套接字
            _nativeSocket=nativeSocket;
        }

    private:
        NativeSocket _nativeSocket;
    };

    class DataSink;

    class IStream{   //通用数据流
    public:
        typedef std::function<void(const char* buf,int64_t size)> DataIndicationHandler;

        virtual int32_t Receive(char* buffer,int32_t bufferSize,int32_t &readSize)=0; //接收数据到用户指定缓冲区
        virtual int32_t Send(const ByteArray& byteArray)=0;  //发送数据将用户传递的字节数组发送到对端

        virtual void OnDataIndication(DataIndicationHandler handler)=0;  //设置数据收集器
        virtual DataIndicationHandler GetDataIndication()=0;   //获取数据收集器
    };

    class IConnectable{  //连接到其他服务器的接口
        virtual void Connect(const std::string& host,int32_t port)=0; //连接到指定主机上的特定服务
    };

    template<class ConnectionType>
    class BasicServer:public Socket{  //基本服务器类
    public:
        typedef std::function<void(IStream* stream)> ConnectIndicationHandler;
        typedef std::function<void(IStream* stream)> DisconnectIndicationHandler;

        BasicServer() {}

        virtual int32_t Listen(const std::string& host, int32_t port, int backlog) = 0;
        virtual void OnConnectIndication(ConnectIndicationHandler handler) = 0;
        virtual void OnDisconnectIndication(DisconnectIndicationHandler handler) = 0;

        virtual ConnectionType Accept(int32_t listenfd) = 0;
    };

    class BasicStream:public IStream,public Socket{  //基本数据流
    public:
        BasicStream()=default;

        BasicStream(NativeSocket nativeSocket):Socket(nativeSocket){  //指定套接字，将在套接字基础上建立数据流
        }

        BasicStream(const BasicStream& stream) =delete;

        virtual void SetDataSink(DataSink* dataSink) {
            _dataSink = dataSink;
        }

        virtual DataSink* GetDataSink() {
            return _dataSink;
        }

        virtual const DataSink* GetDataSink() const {
            return _dataSink;
        }
    private:
        DataSink* _dataSink;

    };
}

#endif //HURRICANE_NET_H
