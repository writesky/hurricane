
#ifndef HURRICANE_IOCPCLIENT_H
#define HURRICANE_IOCPCLIENT_H
#pragma once

#include "IOCPStream.h"
#include "../net.h"
#include "../DataSink.h"
#include "IOCPConnection.h"
#include <memory>

namespace meshy{
    class IOCPClient;

    typedef std::shared_ptr<IOCPClient> IOCPClientPtr;

    class IOCPClient:public IOCPStream,public IConnectable{
    public:
        IOCPClient(const IOCPClient& client)=delete;
        virtual ~IOCPClient(){}

        virtual int32_t Receive(char* buffer, int32_t bufferSize, int32_t& readSize) override;
        virtual int32_t Send(const ByteArray& byteArray) override;

        uint32_t GetEvents() const {
            return _events;
        }

        void SetEvents(uint32_t events) {
            _events = events;
        }

        void Connect(const std::string& host, int32_t port) override {}
        static IOCPClientPtr Connect(const std::string& ip, int32_t port, DataSink* dataSink) {
            return IOCPClientPtr();
        }
    private:
        IOCPClient(NativeSocket clientSocket,NativeSocketAddress clientAddress): IOCPStream(clientSocket,clientAddress){
            this->SetNativeSocket(clientSocket);
        }
    private:
        uint32_t _events;
    };
}
#endif //HURRICANE_IOCPCLIENT_H
