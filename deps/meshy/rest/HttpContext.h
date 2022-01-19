
#ifndef HURRICANE_HTTPCONTEXT_H
#define HURRICANE_HTTPCONTEXT_H

#include "../bytearray.h"
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> StdStringList;

class HttpContext{
public:
    virtual ~HttpContext(){
    }

    const std::string& GetHeader(const std::string& name) const{  //从指定映射表中找出属性名对应的属性值
        return _headers.at(name);   //给定的键值访问map中的元素
    }

    void SetHeader(const std::string& name, const std::string& value) {  //设置http头部属性
        _headers[name] = value;
    }

    bool HashHeader(const std::string& name) const{  //检测头部是否包含某些属性
        return _headers.find(name)!=_headers.end();
    }

    StdStringList GetHeaderNames() const;  //获取所有的头部属性名

    const std::string& GetContent() const{  //获取HTTP消息中的数据
        return _content;
    }

    void SetContent(const std::string& content);  //设置HTPP消息的数据

    const std::string& GetVersion() const {
        return _version;
    }

    void SetVersion(const std::string& version) {
        _version = version;
    }

    virtual void ParseStdStringList(const StdStringList& stringList);  //解析字符串列表，生成HTTP消息
    virtual std::string ToString() const;   //将HTTP消息转为字符串

    static HttpContext FromStdStringList(const StdStringList& stringList);  //直接根据字符串列表创建HTTP消息对象
private:
    std::string _version;
    std::map<std::string,std::string> _headers;
    std::string _content;
};
#endif //HURRICANE_HTTPCONTEXT_H
