
#include "../../rest/HttpContext.h"
#include "../../Meshy.h"
#include "../../bytearray.h"
#include <iostream>
#include "../../utils/String.h"

StdStringList HttpContext::GetHeaderNames() const {  //获取属性名
    StdStringList headerNames;

    for(const auto& pair:_headers){  //直接遍历header即可
        headerNames.push_back(pair.first);
    }

    return headerNames;
}

HttpContext HttpContext::FromStdStringList(const StdStringList &stringList) {
    HttpContext context;
    context.ParseStdStringList(stringList);

    return context;
}

void HttpContext::ParseStdStringList(const StdStringList &stringList) {
    for(const std::string& line:stringList){  //遍历
        StdStringList words= SplitString(line,':');  //分割

        if(!words.size()){
            return;
        }

        std::string headerName = words[0];  //属性
        std::string headerValue = words[1];

        if ( words.size() > 2 ) {  //2个及之后的作为属性值用冒号连接
            for ( int wordIndex = 2; wordIndex < words.size(); ++ wordIndex ) {
                headerValue += ':';
                headerValue += words[wordIndex];
            }
        }

        headerValue.erase(headerValue.begin());  //删除属性值第一个空格

        SetHeader(headerName,headerValue);
    }
}

std::string HttpContext::ToString() const {  //将消息体转换成字符串
    std::string headersString;

    for ( const auto& headerPair : _headers ) {
        std::string headersString = headerPair.first + ':' + headerPair.second + "\r\n";
        headersString += headersString;
    }

    if ( _content.length() > 0 ) {
        headersString += "\r\n";
        headersString += _content;
    }

    return headersString;
}

void HttpContext::SetContent(const std::string &content) {
    _content=content;

    int contentLength=_content.size();
    if(contentLength>0){
        SetHeader("Content-Length", itos(contentLength));
    }
}