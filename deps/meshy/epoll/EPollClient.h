
#ifndef HURRICANE_EPOLLCLIENT_H
#define HURRICANE_EPOLLCLIENT_H
#include <memory>
#include "EpollStream.h"
#include "../net.h"
#include "../DataSink.h"
namespace meshy{
    class EPollclient;

    typedef std::shared_ptr<EPollclient> EPollclientPtr;

    class EPollclient:public EPollStream,public IConnectable{  //可以主动发起链接的数据流
    public:
        EPollclient(const EPollclient& client)=delete;
        virtual ~EPollclient(){}

        virtual int32_t Receive(char* buffer, int32_t bufferSize, int32_t& readSize) override;

        uint32_t GetEvent() const{
            return _events;
        }

        void SetEvents(uint32_t events){
            _events=events;
        }

        void Connect(const std::string& host, int32_t port) override;  //向服务器发起链接
        static EPollclientPtr Connect(const std::string& ip,int32_t port,DataSink* dataSink);

    public:
        virtual int32_t Send(const ByteArray& byteArray) override;

    private:
        EPollclient(NativeSocket clientSocket):
                EPollStream(clientSocket){
            this->SetNativeSocket(clientSocket);
        }
    private:
        uint32_t _events;
    };
}
#endif //HURRICANE_EPOLLCLIENT_H
