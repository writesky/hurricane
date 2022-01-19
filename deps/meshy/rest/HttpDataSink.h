
#ifndef HURRICANE_HTTPDATASINK_H
#define HURRICANE_HTTPDATASINK_H

#include "../net.h"
#include "../Meshy.h"
#include "HttpRequest.h"

namespace meshy{
    class HttpDataSink{
        virtual OnDataIndication(TcpStream* stream, const HttpRequest& request) = 0;
    };
}
#endif //HURRICANE_HTTPDATASINK_H
