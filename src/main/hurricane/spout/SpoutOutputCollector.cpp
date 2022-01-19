
#include "../../../../include/hurricane/spout/SpoutOutputCollector.h"
#include "../../../../include/hurricane/spout/SpoutExector.h"

namespace hurricane{
    namespace spout{
        void SpoutOutputCollector::RandomDestination()
        {
            _executor->RandomDestination(this);
        }

        void SpoutOutputCollector::GroupDestination()
        {
            _executor->GroupDestination(this, GetGroupField());
        }

        void SpoutOutputCollector::Emit(const base::Values & values, int msgId)
        {
        }
    }
}