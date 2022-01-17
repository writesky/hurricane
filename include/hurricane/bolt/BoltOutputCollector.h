//
// Created by yankaixin on 2022/1/2.
//

#ifndef HURRICANE_BOLTOUTPUTCOLLECTOR_H
#define HURRICANE_BOLTOUTPUTCOLLECTOR_H

#pragma once
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/collector/OutputCollector.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/Values.h"

namespace hurricane {
    namespace bolt {
        class BoltExecutor;

        class BoltOutputCollector : public base::OutputCollector {
        public:
            BoltOutputCollector(const std::string& src, int strategy, BoltExecutor* executor) :
                    base::OutputCollector(src, strategy), _executor(executor) {
            }

            virtual void RandomDestination() override;
            virtual void GroupDestination() override;

            void Ack(const base::Values& values);
            void Fail(const base::Values& values);

        private:
            BoltExecutor* _executor;
        };
    }
}

#endif //HURRICANE_BOLTOUTPUTCOLLECTOR_H
