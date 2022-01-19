
#include "../../../../deps/meshy/utils/logger.h"
#include "../../../../include/hurricane/base/NetListener.h"
#include "../../../../deps/meshy/eventqueue.h"
#include "../../../../deps/meshy/eventqueueloop.h"
#include "../../../../deps/meshy/IoLoop.h"
#include "../../../../include/hurricane/Hurricane.h"

#include <iostream>
#include <thread>
#include <chrono>

const int32_t DATA_BUFFER_SIZE = 65535;

void NetListener::StartListen()
{
    _server = std::make_shared<meshy::TcpServer>();

    _server.Listen(_host.GetHost(), _host.GetPort());

    while(1){
        std::shared_ptr<meshy::TcpConnection> connection=
                std::shared_ptr<meshy::TcpConnection>(_server.Accept(100));

        std::cerr<<"A client is connected"<<std::endl;

        std::thread dataThread(std::bind(&NetListener::DataThreadMain,this,std::placeholders::_1),connection);
        dataThread.detach();  //剥离线程
    }
}

void NetListener::DataThreadMain(std::shared_ptr<meshy::TcpConnection> connection)
{
    std::cerr<<connection<<std::endl;
    int32_t _lostTime = 0;

    try {
        char buffer[DATA_BUFFER_SIZE];
        while ( true ) {
            bool successful = connection->Receive(buffer, DATA_BUFFER_SIZE);

            if ( !successful ) {
                break;
            }
        }
    }
    catch ( const std::exception& e ) {
        std::cerr<<e.what()<<std::endl;
    }
}
