
#ifndef HURRICANE_SPOUTEXECTOR_H
#define HURRICANE_SPOUTEXECTOR_H
#include "../base/Executor.h"
#include "../spout/ISpout.h"

#include<iostream>

namespace hurricane{
    namespace topology{
        class ITopology;
    }

    namespace message{
        class SupervisorCommander;
    }

    namespace spout{

        class SpoutOutputCollector;

        class SpoutExecutor:public base::Executor<spout::ISpot>{  //消息源执行器
        public:
            SpoutExecutor():
            base::Executor<spout::ISpot>(),_needToStop(false){
            }

            void StopTask() override;
            void OnCreate() override;
            void OnStop() override;

            void SetExecutorIndex(int executorIndex){
                _executorIndex=executorIndex;
            }

            void SetCommander(message::SupervisorCommander* commander);  //设置该executor当前的命令执行器
            void RandomDestination(SpoutOutputCollector* outputCollector);  //随机数据发送策略的实现
            void GroupDestination(SpoutOutputCollector* outputCollector,int fieldIndex);  //字段分组发送策略实现

        private:
            topology::ITopology* _topology;  //正在执行的拓扑结构
            bool _needToStop;
            message::SupervisorCommander* _commander;  //命令执行器，用于与其他节点进行消息通信
            int _executorIndex;  //执行器在所属manager中的执行器编号
        };
    }
}
#endif //HURRICANE_SPOUTEXECTOR_H
