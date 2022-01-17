//
// Created by yankaixin on 2021/12/22.
//

#ifndef HURRICANE_DATASINK_H
#define HURRICANE_DATASINK_H
#pragma once

#include <cstdint>

namespace meshy{
    class IStream;

    class DataSink{
    public:
        virtual int32_t OnDataIndication(IStream* stream,const char *buf,int64_t bytes)=0;
    };
}
#endif //HURRICANE_DATASINK_H
