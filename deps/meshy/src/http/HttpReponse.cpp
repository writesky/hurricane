//
// Created by yankaixin on 2022/1/3.
//

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpResponse.h"
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/String.h"

namespace meshy{
    std::string HttpResponse::ToStdString() const {
        return GetResponseLine() +
               HttpContext::ToString();
    }
    std::string HttpResponse::GetResponseLine() const {
        return GetVersion() + ' ' + itos(GetStatusCode()) + ' ' + GetStatusMessage() + "\r\n";
    }
}
