//
// Created by yankaixin on 2021/12/22.
//

#ifndef HURRICANE_NETADDRESS_H
#define HURRICANE_NETADDRESS_H
#pragma once
#include <string>

namespace hurricane{
    namespace base{
        class NetAddress{
        public:
            NetAddress(std::string& host,int port):_host(host),_port(port){
            }

            const std::string &GetHost() const{
                return _host;
            }

            void SetHost(const std::string& host){
                _host=host;
            }

            int GetPort() const{
                return _port;
            }

            void SetPort(int port){
                _port=port;
            }
        private:
            std::string _host;
            int _port;
        };
    }
}
#endif //HURRICANE_NETADDRESS_H
