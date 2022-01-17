//
// Created by yankaixin on 2021/12/16.
//

#ifndef HURRICANE_MESSAGELOOP_H
#define HURRICANE_MESSAGELOOP_H
#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace hurricane{
    namespace message{
        class Message;

        class MessageLoop{  //消息队列接口
        public:
            typedef std::function<void(Message*)> MessageHandler;

            MessageLoop();
            MessageLoop(const MessageLoop&) = delete;
            const MessageLoop& operator=(const MessageLoop&) = delete;

            template <class ObjectType, class MethodType>   //实现某个消息类型和消息处理函数之间的映射关系
            void MessageMap(int messageType, ObjectType* self, MethodType method) {
                MessageMap(messageType, std::bind(method, self, std::placeholders::_1));
            }

            void MessageMap(int messageType, MessageHandler handler) {
                _messageHandlers.insert({ messageType, handler });
            }

            void Run();
            void Stop();
            void PostMessage(Message* message);

            static int OnData;
        private:
            std::map<int, MessageHandler> _messageHandlers;
            uint64_t _threadId;
        };

        class MessageLoopManager{  //统一管理消息循环
        public:
            static MessageLoopManager& GetInstance(){
                static MessageLoopManager manager;

                return manager;
            }

            MessageLoopManager(const MessageLoopManager&)= delete;

            const MessageLoopManager& operator=(const MessageLoopManager&)= delete;

            void Register(const std::string &name,MessageLoop* loop){
                _messageLoops.insert({name,std::shared_ptr<MessageLoop>(loop)});
            }

            void PostMessage(const std::string& name,Message* message){
                auto messageLoopPair=_messageLoops.find(name);
                if(messageLoopPair!=_messageLoops.end()){
                    messageLoopPair->second->PostMessage(message);
                }
            }

        private:
            MessageLoopManager();

            std::map<std::string,std::shared_ptr<MessageLoop>> _messageLoops;
        };
    }
}
#endif //HURRICANE_MESSAGELOOP_H
