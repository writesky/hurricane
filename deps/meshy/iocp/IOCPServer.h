//
// Created by yankaixin on 2021/12/27.
//

#ifndef HURRICANE_IOCPSERVER_H
#define HURRICANE_IOCPSERVER_H

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/net.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/PackageDataSink.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/iocp/IOCPStream.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/iocp/IOCPConnection.h"
#include <vector>

namespace meshy{
    class IOCPServer:public BasicServer<WSAConnectionPtr>{
    public:
        IOCPServer();
        virtual ~IOCPServer();

        int32_t Bind(const std::string host,int32_t port);

        int32_t Listen(const std::string& host, int32_t port, int32_t backlog = 20);
        int32_t Listen(DataSink* dataSink, int32_t backlog = 20);

        WSAConnectionPtr Accept(int32_t listenfd) override;

        void SetDataSink(DataSink* dataSink);

        DataSink* GetDataSink() const;

        void SetCompletionPort(HANDLE completionPort);

        HANDLE GetCompletionPort() const;

        virtual void OnConnectIndication(ConnectIndicationHandler handler);
        virtual void OnDisconnectIndication(DisconnectIndicationHandler handler);
    private:
        HANDLE _completionPort;
        NativeSocket _socket;
        DataSink* _dataSink;
        std::vector<IOCP::OperationDataPtr> _ioOperationDataGroup;
        ConnectIndicationHandler _connectHandler;
        DisconnectIndicationHandler _disconnectHandler;
    };
}
#endif //HURRICANE_IOCPSERVER_H
