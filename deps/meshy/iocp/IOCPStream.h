//
// Created by yankaixin on 2021/12/27.
//

#ifndef HURRICANE_IOCPSTREAM_H
#define HURRICANE_IOCPSTREAM_H
#pragma once
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/net.h"

namespace meshy{
    class IOCPStream;
    typedef std::shared_ptr<IOCPStream> IOCPStreamPtr;

    class IOCP{
    public:
        enum{
            DataBuffSize=BUFSIZ
        };

        class OperationType{
        public:
            enum {
                Read,
                Write
            };
        };

        struct OperationData{
            OVERLAPPED overlapped;
            WSABUF databuff;
            char buffer[DataBuffSize];
            int32_t operationType;
            IOCPStream* stream;
        };

        typedef std::shared_ptr<OperationData>  OperationDataPtr;

        static HANDLE GetCompletionPort();   //获取端口
        static OperationDataPtr CreatOperationData(IOCPStreamPtr stream,HANDLE completionPort);  //用户出航见操作数据对象
        static void ResetOperationData(OperationData* perIOData);   //重设操作数据对象
    };

    class IOCPStream:public BasicStream{
    public:
        IOCPStream(NativeSocket clientSocket, NativeSocketAddress clientAddress) :
        BasicStream(clientSocket), _clientAddress(clientAddress) {
        }

        IOCPStream(const IOCPStream& iocpStream)= delete;

        virtual int32_t Receive(char* buffer, int32_t bufferSize, int32_t& readSize) override;
        virtual int32_t Send(const ByteArray& byteArray) override;

        void SetOperationData(IOCP::OperationDataPtr operationData) {
            _operationData = operationData;
        }

        IOCP::OperationDataPtr GetOperationData() {
            return _operationData;
        }

        IOCP::OperationDataPtr GetOperationData() const {
            return _operationData;
        }

    private:
        IOCP::OperationDataPtr _operationData;
        NativeSocketAddress _clientAddress;
    };
}
#endif //HURRICANE_IOCPSTREAM_H
