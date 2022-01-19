
//数据接收器

#ifndef HURRICANE_OUTPUTCOLLECTOR_H
#define HURRICANE_OUTPUTCOLLECTOR_H
#pragma once
#include "../base/Values.h"
#include "../message/SupervisorCommander.h"

namespace hurricane{

    namespace topology{
        class ITopolgy;
    }

    namespace base{
        class OutputCollector{    //数据收集器，进行数据传递
        public:
            struct Strategy{
                enum Values{  //数据接收器的发送策略
                    Global=0,
                    Random=1;
                    Group=2;
                };
            };
            OutputCollector(const std::string& src,int strategy):_src(src),_strategy(strategy),_commander(nullptr){}

            virtual void Emit(const Values& values);  //发送元组

            void SetCommander(hurricane::message::SupervisorCommander* commander) {  //设置一个命令执行器
                if ( _commander ) {
                    delete _commander;
                }

                _commander = commander;
            }

            void SetTaskIndex(int taskIndex){
                _taskIndex=taskIndex;
            }

            void SetGroupField(int groupField) {
                _groupField = groupField;
            }

            int GetGroupField() const {
                return _groupField;
            }

            int GetStrategy() const {
                return _strategy;
            }

            virtual void RandomDestination() {};  //随机选择目的消息处理单元
            virtual void GroupDestination() {};   //根据字段选择元祖发送的目标消息处理单元

        private:
            std::string _src;  //消息接收器来源的任务名称
            int _strategy;   //策略编号
            int _taskIndex;   //目标任务编号
            hurricane::message::SupervisorCommander* _commander;  //命令发送器
            int _groupField;   //分组策略中指定分组使用的字段编号
        };
    }
}
#endif //HURRICANE_OUTPUTCOLLECTOR_H
