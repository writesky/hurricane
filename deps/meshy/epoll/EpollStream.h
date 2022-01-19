
#ifndef HURRICANE_EPOLLSTREAM_H
#define HURRICANE_EPOLLSTREAM_H
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "../linux/net_linux.h"
#include "../net.h"

namespace meshy{
    class  EPollLoop;

    class EPollStream:public BasicStream{
    public:
        EPollStream(NativeSocket nativeSocket):
        BasicStream(nativeSocket){}

        virtual ~EPollStream(){}

        EPollStream(const EPollStream &stream)=delete;

        virtual int32_t Receive(char *buffer, int32_t bufferSize, int32_t &readSize) override;
        virtual int32_t Receive(char *buffer, int32_t bufferSize);
        virtual int32_t Send(const ByteArray &byteArray) override;

        uint32_t GetEvent() const{
            return _event;
        }

        void SetEvents(uint32_t events){
            _event=events;
        }

        void OnDataIndication(DataIndicationHandler handler) override{
            _dataHandler=handler;
        }
        DataIndicationHandler GetDataIndication() override{
            return _dataHandler;
        }

    private:
        uint32_t  _event;
        DataIndicationHandler _dataHandler;
    };

    typedef std::shared_ptr<EPollStream> EPollStreamPtr;
}
#endif //HURRICANE_EPOLLSTREAM_H
