//
// Created by yankaixin on 2021/12/27.
//

#ifndef HURRICANE_IOCPLOOP_H
#define HURRICANE_IOCPLOOP_H

#pragma once

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/loop.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/DataSink.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/iocp/IOCPServer.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/iocp/IOCPConnection.h"

#include <WinSock2.h>
#include <Windows.h>
#include <vector>
#include <memory>
#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>

namespace meshy{
    class EventQueue;

    class IOCPLoop:public Loop{
    public:
        static IOCPLoop* Get();   //静态函数，获取IOCPLoop单例
        void AddServer(IOCPServer* server);  //将一个服务器添加到循环对象中

    private:
        IOCPLoop();
        virtual ~IOCPLoop();
        void SetDataSink(DataSink* dataSink);

    protected:
        virtual void _Run() override;

    private:
        void _Initialize();  //初始化事件循环

        void _IOCPThread();  //IOCP事件循环主线程函数

        void _IOCPConnectionThread(IOCPServer* server);  //接收客户端链接

        void _WorkThread(int32_t listenfd,HANDLE completionPort);  //工作线程的线程函数

        void _Enqueue(IOCPStreamPtr stream,const char* buf,int64_t nread);  //将接收到数据发送到上层
    private:
        std::string                 _host;
        int                         _port;
        DataSink*                   _dataSink;
        bool                        _shutdown;
        SYSTEM_INFO                 _systemInfo;

        ConcurrentQueue<IOCPServer*>            _serverQueue;
        std::map<NativeSocket,IOCPServer*>      _servers;
        std::map<NativeSocket,WSAConnectionPtr> _streams;
    };
}
#endif //HURRICANE_IOCPLOOP_H
