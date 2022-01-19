
#include "../../rest/HttpRequest.h"
#include "../../utils/String.h"

namespace meshy{
    void HttpRequest::ParseStdString(const std::string &text) {
        StdStringList stringList= SplitString(text,'\n');

        for(std::string& line:stringList){
            line.pop_back();
        }

        ParseStdStringList(stringList);
    }

    void HttpRequest::ParseStdStringList(const StdStringList &stringList) {
        std::string requestLine=stringList.front();
        ParseRequestLine(requestLine);  //第一行弄去版本方法等管理

        StdStringList contextLines = stringList;
        contextLines.erase(contextLines.begin());  //去掉第一行
        HttpContext::ParseStdStringList(contextLines);  //上一个方法，解析字符串列表
    }

    void HttpRequest::ParseRequestLine(const std::string &requestLine) {
        StdStringList words= SplitString(requestLine,' ');  //根据空格分割

        SetMethod(words[0]); //请求方法
        SetPath(words[1]);  //路径
        SetVersion(words[2]);  //版本
    }

    HttpRequest HttpRequest::FromStdString(const std::string &text) {  //全部调用第一个方法
        HttpRequest request;
        request.ParseStdString(text);

        return request;
    }

    HttpRequest HttpRequest::FromStdStringList(const StdStringList &stringList) {
        HttpRequest request;
        request.ParseStdStringList(stringList);

        return request;
    }
}