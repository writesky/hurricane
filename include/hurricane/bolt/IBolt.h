
#ifndef HURRICANE_IBOLT_H
#define HURRICANE_IBOLT_H
#include "../task/ITask.h"

namespace hurricane{
    namespace base{

        class OutputCollector;
        class Values;
    }

    namespace bolt{
        class IBolt:public base::ITask{
        public:
            virtual void Prepare(base::OutputCollector& outputCollector)=0;  //在对象启动前对任务对象进行初始化
            virtual void Cleanup()=0;  //在拓扑结构停止时对任务的资源进行清理
            virtual void Execute(const base::Values& values)=0;  //无数据到来时处于阻塞状态

            virtual IBolt* Clone() const =0;
        };
    }
}
#endif //HURRICANE_IBOLT_H
