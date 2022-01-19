#ifndef HURRICANE_PACKAGEDATASINK_H
#define HURRICANE_PACKAGEDATASINK_H
#pragma once

#include "DataSink.h"
#include "bytearray.h"
#include "utils/thread_pool.h"

namespace meshy{
    class EventQueue;

    class BaseEvent;

    class PackageDataSink:public DataSink{
        PackageDataSink(EventQueue *eventQueue);

        ~PackageDataSink();

        int32_t OnDataIndication(IStream* stream,const char *buf,int64_t bytes) override;

    private:
        EventQueue *_eventQueue;
        ThreadPool<BaseEvent> *threadPool;
        ByteArray _data;
        int32_t _totalSize;
    };
}
#endif //HURRICANE_PACKAGEDATASINK_H
