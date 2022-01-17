//
// Created by yankaixin on 2021/12/23.
//

#ifndef HURRICANE_BOLTEXECTOR_H
#define HURRICANE_BOLTEXECTOR_H
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/Executor.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/bolt/IBolt.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/Values.h"
#include "BoltOutputCollector.h"

namespace hurricane{
    namespace topology{
        class ITopology;
    }

    namespace message{
        class Message;
        class SupervisorCommander;
    }

    namespace bolt{  //消息处理单元
        class BoltMessageLoop;
        class BoltOutPutCollector;

        class BoltExecutor:public base::Executor<bolt::IBolt>{
        public:
            BoltExecutor();

            void SetExecutorIndex(int executorIndex){
                _executorIndex=executorIndex;
            }

            void SendData(const base::Values& values);
            void OnData(hurricane::message::Message* message);

            void OnCreate() override;
            void OnStop() override;

            void SetCommander(message::SupervisorCommander* commander){
                _commander=commander;
            }

            void RandomDestination(hurricane::bolt::BoltOutputCollector *outputCollector);
            void GroupDestination(BoltOutputCollector *outputCollector, int fieldIndex);

        private:
            topology::ITopology* _topology;
            message::SupervisorCommander* _commander;
            int _executorIndex;
        };
    }
}
#endif //HURRICANE_BOLTEXECTOR_H
