//
// Created by yankaixin on 2021/12/28.
//

#ifndef HURRICANE_HTTPDATASINK_H
#define HURRICANE_HTTPDATASINK_H

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/net.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/Meshy.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpRequest.h"

namespace meshy{
    class HttpDataSink{
        virtual OnDataIndication(TcpStream* stream, const HttpRequest& request) = 0;
    };
}
#endif //HURRICANE_HTTPDATASINK_H
