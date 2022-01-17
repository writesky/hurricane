//
// Created by yankaixin on 2021/12/14.
//

#ifndef HURRICANE_ITASK_H
#define HURRICANE_ITASK_H
#pragma once

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/collector/OutputCollector.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/Fields.h"
#include <memory>
#include <vector>

namespace hurricane{
    namespace base{
        class ITask{
        public:
            struct Strategy{
                enum Values{
                    Global=0;
                    Random=1;
                    Group=2;
                };
            };
            virtual ~ITask();
            virtual Fields DeclareFields() const=0;   //声明任务的字段名

            Strategy::Values GetStrategy() const{
                return _strategy;
            }
            void SetStrategy(Strategy::Values strategy){
                strategy=_strategy;
            }
//            virtual void Prepare(std::shared_ptr<hurricane::collector::OutputCollector> outputCollector)=0;
//            virtual void Cleanup()=0;
//            virtual std::vector<std::string> DeclareFiled()=0;

        private:
            Strategy::Values _strategy;
        };
    }
}
#endif //HURRICANE_ITASK_H
