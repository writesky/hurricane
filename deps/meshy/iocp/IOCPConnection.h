
#ifndef HURRICANE_IOCPCONNECTION_H
#define HURRICANE_IOCPCONNECTION_H
#pragma once

#include "../net.h"
#include "IOCPStream.h"
#include <Windows.h>
#include <thread>

namespace meshy{

    class WSAConnection:public IOCPStream{
    public:
        WSAConnection(NativeSocket clientSocket,NativeSocketAddress clientAddress):IOCPStream(clientSocket,clientAddress){
        }

        WSAConnection(const IOCPStream& stream) =delete;

        virtual void OnDataIndication(DataIndicationHandler handler){
            _dataHandler=handler;
        }

        virtual DataIndicationHandler GetDataIndication(){
            return _dataHandler;
        }
    private:
        DataIndicationHandler _dataHandler;
    };
    typedef std::shared_ptr<WSAConnection> WSAConnectionPtr;
}
#endif //HURRICANE_IOCPCONNECTION_H
