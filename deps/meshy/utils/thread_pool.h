
#ifndef HURRICANE_THREAD_POOL_H
#define HURRICANE_THREAD_POOL_H

#include "concurrent_queue.h"

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#define MIN_THREADS 10

namespace meshy{
    template<class Type>
    class ThreadPool{  //线程池
        ThreadPool &operator=(const ThreadPool &) = delete;  //禁止复制

        ThreadPool(const ThreadPool& other)=delete;  //删除复制构造函数

    public:
        ThreadPool(int32_t threads, std::function<void(Type &record)> handler);

        virtual ~ThreadPool();

        void Submit(Type record);  //提交一个记录，并由线程池中的工作线程处理
    private:
        bool _shutdown;
        int32_t  _threads;
        std::function<void(Type &record)> _handler;  //记录的工作线程线程处理函数
        std::vector<std::thread> _workers;   //存放所有的工作线程
        ConcurrentQueue<Type> _tasks;
    };
}
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/template/utils/thread_pool.tcc"
#endif //HURRICANE_THREAD_POOL_H
