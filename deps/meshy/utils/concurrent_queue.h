//
// Created by yankaixin on 2021/12/25.
//

#ifndef HURRICANE_CONCURRENT_QUEUE_H
#define HURRICANE_CONCURRENT_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

namespace meshy{
    template<class Type>
    class ConcurrentQueue{  //消息队列
        ConcurrentQueue &operator=(const ConcurrentQueue &)=delete;  //禁止赋值

        ConcurrentQueue(const ConcurrentQueue& other)=delete; //禁止复制

    public:
        ConcurrentQueue():_queue(),_mutex(),_condition(){}

        virtual ~ConcurrentQueue(){};

        void Push(Type record){  //将记录放到队列中
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push(record);
            _condition.notify_one();  //随机激活某个线程
        }

        bool Pop(Type &record,bool isBlocked=true){
            if(isBlocked){   //若是阻塞模式，循环等待队列·非空
                std::unique_lock<std::mutex> lock(_mutex);
                while(_queue.empty()){
                    _condition.wait(lock);
                }
            }else{  //非阻塞模式，检察队列是否有元素，没有则返回false；
                std::lock_guard<std::mutex> lock(_mutex);
                if(_queue.empty()) {
                    return false;
                }
            }
            //有元素从队列中取出，利用move触发移动构造函数，将值赋予用户传递的值，
            record=std::move(_queue.front());
            _queue.pop(); //删除元素
            return true;
        }

        int32_t Size(){ //返回队列长度
            std::lock_guard<std::mutex> lock(_mutex);
            return _queue.size();
        }

        bool Empty(){
            std::lock_guard<std::mutex> lock(_mutex);
            return _queue.empty();
        }
    private:
        std::queue<Type> _queue;
        mutable std::mutex _mutex;  //可改变const修饰方法，但不影响该方法
        std::condition_variable _condition;
    };
}
#endif //HURRICANE_CONCURRENT_QUEUE_H
