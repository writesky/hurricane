//
// Created by yankaixin on 2021/12/26.
//

#ifndef HURRICANE_EPOLLLOOP_H
#define HURRICANE_EPOLLLOOP_H
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/loop.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollClient.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EpollConnection.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EpollStream.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/epoll/EPollSever.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/net.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/DataSink.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/linux/common.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/linux/net_linux.h"
#include <sys/epoll.h>
#include <map>
#include <memory>
#include <thread>
#include <string>

namespace meshy{
    class EventQueue;

    class EPollServer;

    class EPollLoop:public Loop{
    public:
        static EPollLoop* Get();   //获取EPollLoop对象的唯一实例，所以EPollLoop为典型的单例模式后

        virtual ~EPollLoop() override;

        void AddServer(NativeSocket socket,EPollServer* server);  //在事件中循环监听socket套接字，将触发的消息传给server
        void AddStream(EPollStreamPtr stream); //将流对象的指针添加到Loop中，Loop会帮助流对象监听输入输出事件，有消息即通过回调函数通知流对象

        int32_t AddEpollEvents(int32_t events, int32_t fd);  //在Loop中添加一个Epoll事件
        int32_t ModifyEpollEvents(int32_t events, int32_t fd);  //改变Loop中监听的Epoll事件
    protected:
        EPollLoop();

        virtual void _Run() override;

    private:
        void _Initialize();

        void _EPollThread();  //循环线程的主函数

        void _HandleEvent(int32_t eventfd, struct epoll_event *events, int32_t nfds); //处理特定EPoll事件

        int32_t _Accept(int32_t eventfd, int32_t listenfd);  //响应epoll中的accect事件

        void _Read(int32_t eventfd, int32_t fd, uint32_t events);  //响应epoll中数据流的读取事件

        void _Enqueue(EPollStreamPtr connection, const char* buf, int64_t nread);  //将读取到的内容发送到系统数据读取队列中

    private:
        int32_t _eventfd;
        bool _shutdown;

        std::map<NativeSocket,EPollServer*> _servers;   //存储套接字与服务器之间的关系
        std::map<NativeSocket ,EPollStreamPtr > _streams;  //统一管理所有的流，便于使用套接字来寻找对应的流对象
    };
}
#endif //HURRICANE_EPOLLLOOP_H
