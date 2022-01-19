
#ifndef HURRICANE_THREAD_POOL_TCC
#define HURRICANE_THREAD_POOL_TCC
#pragma once

namespace meshy{
    template<class Type>
    ThreadPool<Type>::ThreadPool(int32_t threads, std::function<void(Type &record)> handler)
            : _shutdown(false),
              _threads(threads),
              _handler(handler),
              _workers(),
              _tasks() {
        if (_threads < MIN_THREADS)
            _threads = MIN_THREADS;

        for (int32_t i = 0; i < _threads; ++i)
            _workers.emplace_back(
                    [this] {
                        while (!_shutdown) {
                            Type record;
                            _tasks.Pop(record, true);  //从队列中获取数据
                            _handler(record);  //执行用户指定的处理函数
                        }
                    }
            );
    }

    template<class Type>
    ThreadPool<Type>::~ThreadPool() {  //遍历所有线程并逐一等待，直到所有线程结束
        for (std::thread &worker: _workers)
            worker.join();
    }

    template<class Type>
    void ThreadPool<Type>::Submit(Type record) {   //直接讲一个记录对象放入任务队列
        _tasks.Push(record);
    }
}
#endif //HURRICANE_THREAD_POOL_TCC
