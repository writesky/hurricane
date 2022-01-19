
#ifndef HURRICANE_EVENTQUEUELOOP_H
#define HURRICANE_EVENTQUEUELOOP_H

#pragma once

#include "loop.h"
#include <memory>

namespace meshy{
    class EventQueue;

    class BaseEvent;

    class EventQueueLoop:public Loop{
    public:
        EventQueueLoop(EventQueue *queue);

    protected:
        virtual void _Run();

        virtual void OnEvent(std::shared_ptr<BaseEvent> event)=0;  //指定触发某个事件时的回调函数（异步
    private:
        EventQueue* _queue;
    };
}
#endif //HURRICANE_EVENTQUEUELOOP_H
