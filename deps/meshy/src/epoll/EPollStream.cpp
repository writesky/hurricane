
#include "../../epoll/EpollStream.h"
#include "../../epoll/EPollLoop.h"
#include "../../utils/logger.h"
#include "../../bytearray.h"
#include <unistd.h>

namespace meshy{
    int32_t EPollStream::Receive(char *buffer, int32_t bufferSize, int32_t &readSize) {
        readSize=0;
        int32_t nread=0;
        NativeSocketEvent ev;

        while((nread=read(GetNativeSocket(),buffer+readSize,bufferSize-1))>0){
            readSize+=nread;
        }

        return nread;
    }

    int32_t EPollStream::Send(const ByteArray &byteArray) {
        TRACE_DEBUG("EPollConnection::Send");
        struct epoll_event ev;
        NativeSocketEvent clientSocket=GetNativeSocket();

        if(EPollLoop::Get()->ModifyEpollEvents(_event|EPOLLOUT,clientSocket)){
            TRACE_ERROR("FATAL epoll_ctl: mod failed!");
        }

        const char *buf=byteArray.data();
        int32_t size=byteArray.size();
        int32_t n=size;

        while(n>0){
            int32_t nwrite;
            nwrite= write(clientSocket,buf+size-n,n);
            if(nwrite<n){
                if (nwrite == -1 && errno != EAGAIN) {
                    TRACE_ERROR("FATAL write data to peer failed!");
                }
                break;
            }
            n -= nwrite;
        }
        return 0;
    }
}