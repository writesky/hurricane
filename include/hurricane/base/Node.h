//
// Created by yankaixin on 2022/1/2.
//

#ifndef HURRICANE_NODE_H
#define HURRICANE_NODE_H

#pragma once

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/NetAddress.h"
#include <string>
#include <ctime>

namespace hurricane{
    namespace base{
        class Node{
        public:
            enum class Status{
                Dead,
                Alived
            };
            Node(): _address("",0),_status(Status::Dead){
            };

            Node(std::string name,const NetAddress &address):
            _name(name), _address(address),_status(Status::Dead){}

            const std::string& GetName() const {
                return _name;
            }

            void SetName(const std::string& name) {
                _name = name;
            }

            const NetAddress& GetAddress() const {
                return _address;
            }

            void SetAddress(const NetAddress& address) {
                _address = address;
            }

            Status GetStatus() const {
                return _status;
            }

            void SetStatus(Status status) {
                _status = status;
            }

            void Alive() {
                _lastLiveTime = time_t(0);
            }
        private:
            std::string _name;
            NetAddress _address;
            Status _status;
            time_t _lastLiveTime;
        };
    }
}
#endif //HURRICANE_NODE_H
