
#include "../../rest/HttpResponse.h"
#include "../../utils/String.h"

namespace meshy{
    std::string HttpResponse::ToStdString() const {
        return GetResponseLine() +
               HttpContext::ToString();
    }
    std::string HttpResponse::GetResponseLine() const {
        return GetVersion() + ' ' + itos(GetStatusCode()) + ' ' + GetStatusMessage() + "\r\n";
    }
}
