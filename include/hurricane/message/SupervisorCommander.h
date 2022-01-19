

#ifndef HURRICANE_SUPERVISORCOMMANDER_H
#define HURRICANE_SUPERVISORCOMMANDER_H

#pragma once
#include "../base/NetAddress.h"
#include "../base/NetConnector.h"
#include "../base/Values.h"
#include <string>

namespace hurricane{
    namespace message{
        class SupervisorCommander{
        public:
            SupervisorCommander(const hurricane::base::NetAddress& nimbusAddress,
                                const std::string& superVisorName):
                    _nimbusAddress(nimbusAddress),_supervisorName(superVisorName){
            }

            void Connect(){
                if(!_connector.get()){
                    _connector=std::make_shared<NetConnector>(_nimbusAddress);
                    _connector->Connect();
                }
            }

            void Join();
            void Alive();
            void SendTuple(int taskIndex, const base::Values& values);
            void RandomDestination(const std::string srcType, int32_t srcIndex,
                                   std::string * host, int * port, int* destIndex);
            void GroupDestination(const std::string srcType, int srcIndex,
                                  std::string * host, int * port, int* destIndex,
                                  int fieldIndex);
            const std::string GetSupervisorName() const {
                return _supervisorName;
            }
        private:
            hurricane::base::NetAddress _nimbusAddress;
            std::string _supervisorName;
            std::shared_ptr<NetConnector> _connector;
            int32_t _taskIndex;
        };
    }
}
#endif //HURRICANE_SUPERVISORCOMMANDER_H
