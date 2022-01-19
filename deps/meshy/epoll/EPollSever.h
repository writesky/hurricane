
#ifndef HURRICANE_EPOLLSEVER_H
#define HURRICANE_EPOLLSEVER_H

#include <memory>
#include <barrier>
#include "EpollConnection.h"
#include "../PackageDataSink.h"
#include "../net.h"

namespace meshy{
    class Socket;
    class EPollServer:public BasicServer<EPollConnectionPtr>{
    public:
        EPollServer(){}

        virtual ~EPollServer(){}

        int32_t Listen(const std::string& host,int32_t port,int32_t backlog=20) override;

        void OnConnectIndication(ConnectIndicationHandler handler) {
            _connectHandler = handler;
        }
        void OnDisconnectIndication(DisconnectIndicationHandler handler) {
            _disconnectIndication = handler;
        }

        EPollConnectionPtr Accept(int32_t sockfd);
    private:
        int32_t _Bind(const std::string& host,int32_t port);
        DataSink* _dataSink;
        ConnectIndicationHandler _connectHandler;
        DisconnectIndicationHandler _disconnectIndication;
    };
}
#endif //HURRICANE_EPOLLSEVER_H
