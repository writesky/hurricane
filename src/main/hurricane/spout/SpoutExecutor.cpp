
#include "../../../../include/hurricane/spout/SpoutExector.h"
#include "../../../../include/hurricane/message/SupervisorCommander.h"
#include "../../../../include/hurricane/spout/SpoutOutputCollector.h"

#include <iostream>
#include <string>

namespace hurricane{
    namespace spout{
        void SpoutExecutor::StopTask() {
            _needToStop=true;
            Executor::StopTask();
        }

        void SpoutExecutor::OnCreate() {
            std::cout<<"Start Spout Task"<<std::endl;
            _needToStop= false;

            if(_task->GetStrategy()==base::ITask::Strategy::Global){
                SpoutOutputCollector outputCollector(GetTaskName(),base::ITask::Strategy::Global,this);
                RandomDestination(&outputCollector);

                _task->Open(outputCollector);
            }

            while(!_needToStop){
                _task->Execute();
            }
            _task->Close();
        }

        void SpoutExecutor::OnStop() {
            std::cout << "Stop Spout Task" << std::endl;
        }

        void SpoutExecutor::SetCommander(message::SupervisorCommander *commander) {
            _commander=commander;
        }

        void SpoutExecutor::RandomDestination(SpoutOutputCollector *outputCollector) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->RandomDestination("spout",_executorIndex,&host,&port,&destIndex);
            outputCollector->SetCommander(new message::SupervisorCommander(base::NetAddress(host,port),_commander->GetSupervisorName()));
            outputCollector->SetTaskIndex(destIndex);
        }

        void SpoutExecutor::GroupDestination(SpoutOutputCollector *outputCollector, int fieldIndex) {
            std::string host;
            int32_t port;
            int32_t destIndex;

            _commander->GroupDestination("spout", _executorIndex,
                                         &host, &port, &destIndex, fieldIndex);
            outputCollector->SetCommander(new message::SupervisorCommander(
                    base::NetAddress(host, port), _commander->GetSupervisorName()));
            outputCollector->SetTaskIndex(destIndex);
        }
    }
}