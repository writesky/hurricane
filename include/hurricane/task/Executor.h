//
// Created by yankaixin on 2021/12/15.
//

#ifndef HURRICANE_EXECUTOR_H
#define HURRICANE_EXECUTOR_H
#pragma once
#include"/Users/yankaixin/Desktop/hurricane/include/hurricane/task/ITask.h"

namespace hurricane {
    namespace task {
        class Executor {
        public:
            struct MessageType {
                emue{
                    OnTuple
                };
            };
            virtual ~Executor(){}

            virtual void Start()=0;
        };
    }
}
#endif //HURRICANE_EXECUTOR_H
