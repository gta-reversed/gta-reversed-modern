#include "StdInc.h"

int CEventSource::ComputeEventSourceType(const CEvent& event, const CPed& ped) {
    return plugin::CallAndReturn<int, 0x4ABAC0, const CEvent&, const CPed&>(event, ped);
}