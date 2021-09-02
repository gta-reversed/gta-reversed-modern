#include "StdInc.h"

int32 CEventSource::ComputeEventSourceType(const CEvent& event, const CPed& ped) {
    return plugin::CallAndReturn<int32, 0x4ABAC0, const CEvent&, const CPed&>(event, ped);
}