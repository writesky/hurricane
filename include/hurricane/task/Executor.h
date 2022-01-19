

#ifndef HURRICANE_EXECUTOR_H
#define HURRICANE_EXECUTOR_H
#pragma once
#include"ITask.h"

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
