
#include "../../../../include/hurricane/bolt/BoltOutputCollector.h"
#include "../../../../include/hurricane/bolt/BoltExector.h"

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

