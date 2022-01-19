
#ifndef HURRICANE_LOGGER_H
#define HURRICANE_LOGGER_H

#include "concurrent_queue.h"
#include <memory>
#include <thread>
#include <queue>
#include <string>
#include <fstream>

namespace meshy{

    enum Priority{
        DEBUG,
        STATE,
        INFO,
        WARNING,
        FAULT
    };

    class Logger{
        Logger &operator=(const Logger &)=delete;

        Logger(const Logger &other)=delete;

    public:
        static Logger *Get();
        //获取并设置优先级
        void SetPriority(Priority priority);

        Priority GetPriority();

        void WriteLog(Priority priority,const std::string &log);   //按优先级输出日志

    private:
        Logger(Priority priority);  //单例模式

        virtual ~Logger();

        void _InitializeFileStream();  //初始化日志文件流

        void _WriteThread();  //输出的线程函数

    private:
        ConcurrentQueue<std::string> _queue;
        std::ofstream *_fileStream;
        Priority _priority;
        bool _shutdown;
    };
#define TRACE_DEBUG(LOG_CONTENT) Logger::Get()->WriteLog(DEBUG, LOG_CONTENT);
#define TRACE_STATE(LOG_CONTENT) Logger::Get()->WriteLog(STATE, LOG_CONTENT);
#define TRACE_INFO(LOG_CONTENT) Logger::Get()->WriteLog(INFO, LOG_CONTENT);
#define TRACE_WARNING(LOG_CONTENT) Logger::Get()->WriteLog(WARNING, LOG_CONTENT);
#define TRACE_ERROR(LOG_CONTENT) Logger::Get()->WriteLog(FAULT, LOG_CONTENT);
}
#endif //HURRICANE_LOGGER_H
