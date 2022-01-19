
#ifndef HURRICANE_HTTPRESPONSE_H
#define HURRICANE_HTTPRESPONSE_H

#include "HttpContext.h"

namespace meshy{
    class HttpResponse:public HttpContext{
    public:
        HttpResponse() {}
        virtual std::string ToStdString() const;

        int GetStatusCode() const {
            return _statusCode;
        }

        void SetStatusCode(int statusCode) {
            _statusCode = statusCode;
        }

        const std::string& GetStatusMessage() const {
            return _statusMessage;
        }

        void SetStatusMessage(const std::string& message) {
            _statusMessage = message;
        }

    private:
        std::string GetResponseLine() const;  //将相应信息转换成字符串

        int _statusCode;
        std::string _statusMessage;
    };
}
#endif //HURRICANE_HTTPRESPONSE_H
