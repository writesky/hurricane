//
// Created by yankaixin on 2021/12/28.
//

#ifndef HURRICANE_HTTPREQUEST_H
#define HURRICANE_HTTPREQUEST_H

#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/rest/HttpContext.h"

namespace meshy{
    class HttpRequest:public HttpContext{
    public:
        HttpRequest(){}
        void ParseStdString(const std::string& text);  //解析字符串，初始化HttpRequest对象
        virtual void ParseStdStringList(const StdStringList& stringList) override;  //解析字符串列表，初始化HttpRequest对象

        static HttpRequest FromStdString(const std::string& text);
        static HttpRequest FromStdStringList(const StdStringList& stringList);

        const std::string& GetMethod() const{
            return _method;
        }

        const std::string& GetPath() const{
            return _path;
        }

        void SetMethod(const std::string& method) {
            _method = method;
        }

        void SetPath(const std::string& path) {
            _path = path;
        }

    private:
        void ParseRequestLine(const std::string& requestLine);  //负责解析请求头的第一行
    private:
        std::string _method;
        std::string _path;
    };
}
#endif //HURRICANE_HTTPREQUEST_H
