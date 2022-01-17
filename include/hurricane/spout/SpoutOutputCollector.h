//
// Created by yankaixin on 2021/12/22.
//

#ifndef HURRICANE_SPOUTOUTPUTCOLLECTOR_H
#define HURRICANE_SPOUTOUTPUTCOLLECTOR_H
#pragma once

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/collector/OutputCollector.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/Values.h"

namespace hurricane {
    namespace spout {
        class SpoutExecutor;

        class SpoutOutputCollector : public base::OutputCollector {
        public:
            SpoutOutputCollector(const std::string& src, int strategy, SpoutExecutor* executor) :
                    base::OutputCollector(src, strategy), _executor(executor) {
            }

            virtual void RandomDestination() override;
            virtual void GroupDestination() override;
            void Emit(const base::Values& values, int msgId);

        private:
            SpoutExecutor* _executor;
        };
    }
}
#endif //HURRICANE_SPOUTOUTPUTCOLLECTOR_H
