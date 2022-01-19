

#ifndef HURRICANE_MESSAGE_H
#define HURRICANE_MESSAGE_H
#pragma once
#include <cstdint>

namespace hurricane{
    namespace message{
        class Message{  //定义消息
        public:
            struct Type{
                enum {
                    Stop=0
                };
            };

            Message(int32_t type):_type(type){
            }

            virtual ~Message(){
            }

            int32_t GetType() const{
                return _type;
            }

            void SetType(int32_t type){
                _type=type;
            }

        private:
            int32_t _type;
        };
    }
}
#endif //HURRICANE_MESSAGE_H
