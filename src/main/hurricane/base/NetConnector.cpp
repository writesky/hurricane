//
// Created by yankaixin on 2021/12/23.
//
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/Hurricane.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/base/NetConnector.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"

#include <thread>
#include <chrono>

void NetConnector::Connect() {
    _client=meshy::TcpClient::Connect(_host.GetHost(),_host.GetPort(), nullptr);
}

int32_t NetConnector::SendAndReceive(const char *buffer, int32_t size, char *resultBuffer, int32_t resultSize) {
    _client->Send(meshy::ByteArray(buffer, size));

    bool receiveData=true;
    _client->OnDataIndication([&receiveData,&resultSize,&resultBuffer](const char* buf,int64_t size){
        if(resultSize>size){
            resultSize=size;
        }

        memcpy(resultBuffer,buf,resultSize);
        receiveData=true;
    });

    while(!receiveData){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return resultSize;
}
