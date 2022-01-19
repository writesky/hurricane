
#ifndef HURRICANE_EXECUTOR_H
#define HURRICANE_EXECUTOR_H
#pragma once

#include "../task/ITask.h"
#include "../message/MessageLoop.h"

#include <thread>
#include <memory>
#include<vector>
#include <iostream>
#include <mutex>
#include <functional>
#include "../bolt/BoltMessage.h"

namespace hurricane{
    namespace base{
        template<class TaskType>
        class Executor{
        public:
            enum class Status{
                Stopping,
                Running
            };

            void StartTask(const std::string& taskName,TaskType* task){
                _messageLoop.MessageMap(bolt::BoltMessage::MessageType::Data,this,&message::MessageLoop::OnData);
                _taskName=taskName;
                _task=std::shared_ptr<TaskType>(task);

                _thread=std::thread(std::bind(&Executor::StartThread,this));
            }

            virtual void StopTask(){
                _messageLoop.Stop();
            }

            Status GetStatus() const {
                return _status;
            }

            const std::string & GetTaskName() const {
                return _taskName;
            }

        protected:
            virtual void OnCreate()=0;
            virtual void OnStop()=0;
            std::shared_ptr<TaskType> _task;
            hurricane::message::MessageLoop _messageLoop;

            Executor():_status(Status::Stopping){
            }

            virtual ~Executor(){}

        private:
            void StartThread(){
                _status=Status::Running;

                OnCreate();
                _messageLoop.Run();
                OnStop();

                _status=Status::Stopping;
            }

            std::thread _thread;
            Status _status;
            std::string _taskName;
        };
    }
}
#endif //HURRICANE_EXECUTOR_H
