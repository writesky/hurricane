//
// Created by yankaixin on 2022/1/2.
//

#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/bolt/BoltOutputCollector.h"
#include "/Users/yankaixin/Desktop/hurricane/include/hurricane/bolt/BoltExector.h"

namespace hurricane {
    namespace bolt {
        void BoltOutputCollector::RandomDestination()
        {
            _executor->RandomDestination(this);
        }

        void BoltOutputCollector::GroupDestination()
        {
            _executor->GroupDestination(this, GetGroupField());
        }

        void BoltOutputCollector::Ack(const base::Values & values)
        {
        }

        void BoltOutputCollector::Fail(const base::Values & values)
        {
        }
    }
}

