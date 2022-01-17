//
// Created by yankaixin on 2022/1/2.
//

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/bolt/BoltExector.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/bolt/BoltMessage.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/message/MessageLoop.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/message/SupervisorCommander.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/bolt/BoltOutputCollector.h"

#include <iostream>
#include <thread>
#include <chrono>

namespace hurricane{
    namespace bolt{
        BoltExecutor::BoltExecutor() :base::Executor<bolt::IBolt>(){   //消息注册
            _messageLoop.MessageMap(BoltMessage::MessageType::Data,
                                    this, &BoltExecutor::OnData);
        }

        void BoltExecutor::SendData(const base::Values& values)
        {
            _messageLoop.PostMessage(new BoltMessage(values));
        }

        void BoltExecutor::OnData(hurricane::message::Message* message) {  //处理消息
            BoltMessage* boltMessage = dynamic_cast<BoltMessage*>(message);
            _task->Execute(boltMessage->GetValues());

            delete message;
        }

        void BoltExecutor::OnCreate()
        {
            std::cout << "Start Bolt Task" << std::endl;

            if ( _task->GetStrategy() == base::ITask::Strategy::Global ) {
                BoltOutputCollector outputCollector(GetTaskName(), base::OutputCollector::Strategy::Global, this);
                RandomDestination(&outputCollector);

                _task->Prepare(outputCollector);
            }
        }

        void BoltExecutor::OnStop()
        {
            std::cout << "Stop Bolt Task" << std::endl;

            _task->Cleanup();
        }

        void BoltExecutor::RandomDestination(BoltOutputCollector * outputCollector)
        {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->RandomDestination("bolt", _executorIndex, &host, &port, &destIndex);
            outputCollector->SetCommander(new message::SupervisorCommander(
                    base::NetAddress(host, port), _commander->GetSupervisorName()));
            outputCollector->SetTaskIndex(destIndex);
        }

        void BoltExecutor::GroupDestination(BoltOutputCollector *outputCollector, int fieldIndex) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->GroupDestination("bolt", _executorIndex,
                                         &host, &port, &destIndex, fieldIndex);
            outputCollector->SetCommander(new message::SupervisorCommander(
                    base::NetAddress(host, port), _commander->GetSupervisorName()));
            outputCollector->SetTaskIndex(destIndex);

        }
    }
}