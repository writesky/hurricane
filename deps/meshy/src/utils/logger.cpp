
#include "/Users/yankaixin/Desktop/hurricane/deps/meshy/utils/logger.h"
#include <ctime>
#include <iostream>
#include <sstream>

namespace meshy{
    const std::string PRIORITY_STRING[]={
            "DEBUG",
            "CONFIG",
            "INFO",
            "WARNING",
            "ERROR"
    };

    Logger *Logger::Get() {  //获取日志工具的单例
        static Logger logger(DEBUG);
        return &logger;
    }

    Logger::Logger(Priority priority):_queue(),_fileStream(nullptr),_shutdown(false){
        _priority=priority;
        _InitializeFileStream();  //初始化文件系统
        auto func=std::bind(&Logger::_WriteThread,this);  //将输出线程与对象的this指针绑定
        std::thread writeThread(func);
        writeThread.detach();  //detach 主线程和子线程的同步，两者并行同步运行
    }

    Logger::~Logger() {
        _shutdown=true;

        if(nullptr!=_fileStream){
            _fileStream->close();
            delete _fileStream;
            _fileStream= nullptr;
        }
    }

    void Logger::SetPriority(Priority priority) {
        _priority=priority;
    }

    Priority Logger::GetPriority() {
        return _priority;
    }

    void Logger::_InitializeFileStream() {
        //prepare filename
        std::string fileName="logs/Hurricane_log.log";

        //Initialize file stream
        _fileStream=new std::ofstream();
        std::ios_base::open_mode mode=std::ios_base::out;
        mode |=std::ios_base::trunc;
        _fileStream->open(fileName,mode);

        //Error handling
        if (!_fileStream->is_open()) {
            // Print error information
            std::ostringstream ss_error;
            ss_error << "FATAL ERROR:  could not Open log file: [" << fileName << "]";
            ss_error << "\n\t\t std::ios_base state = " << _fileStream->rdstate();
            std::cerr << ss_error.str().c_str() << std::endl << std::flush;

            // Cleanup
            _fileStream->close();
            delete _fileStream;
            _fileStream = nullptr;
        }
    }

    void Logger::WriteLog(Priority priority, const std::string &log) {
        if(priority<_priority)  //小于预先优先级
            return;

        std::stringstream stream;
        stream<<HurricaneUtils::GetCurrentTimeStamp<<"["<<PRIORITY_STRING<<"]"<<log;

        _queue.Push(stream.str());
    }

    void Logger::_WriteThread() {  //独立线程，从队列中取数据并写入日志文件
        while(!_shutdown){
            std::string log;
            _queue.Pop(log, true);

            std::cout<<log<<std::endl;

            if(_fileStream)
                *_fileStream<<log<<std::endl;
        }
    }
}