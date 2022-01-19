

#ifndef HURRICANE_BOLTMESSAGE_H
#define HURRICANE_BOLTMESSAGE_H
#pragma once

#include "../message/Message.h"
#include "../base/Values.h"

namespace hurricane{
    namespace bolt{
    class BoltMessage:public hurricane::message::Message{
    public:
        struct MessageType{
            enum {
                Data=0x1000;
            };
        };

        BoltMessage(const base::Values& values): hurricane::message::Message(MessageType::Data),_values(values){
        }

        const base::Values& GetValues() const {
            return _values;
        }

        void SetValues(const base::Values& values){
            _values=values;
        }

    private:
        base::Values _values;
    };
    }
}
#endif //HURRICANE_BOLTMESSAGE_H
