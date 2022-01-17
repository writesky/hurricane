//
// Created by yankaixin on 2021/12/26.
//

#ifndef HURRICANE_PACKAGEDATASINK_H
#define HURRICANE_PACKAGEDATASINK_H
#pragma once

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/DataSink.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/bytearray.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/thread_pool.h"

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
