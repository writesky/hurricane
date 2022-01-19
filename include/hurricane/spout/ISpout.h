

#ifndef HURRICANE_ISPOUT_H
#define HURRICANE_ISPOUT_H
#pragma once
#include "../task/ITask.h"
#include "SpoutOutputCollector.h"


namespace hurricane{
    namespace base{

        class OutputCollector;
    }

    namespace spout{
        class ISpot:public base::ITask{
        public:
            virtual void Open(SpoutOutputCollector outputCollector)=0;  //打开并初始化一个新的消息源
            virtual void Close()=0;  //关闭消息源
            virtual void Execute()=0;  //任务执行器，向拓扑结构中输入数据

            virtual ISpot* Clone() const =0;  //在堆上产生对象自身的一份副本并将复制对象通过指针返回
        };
    }
}
#endif //HURRICANE_ISPOUT_H
