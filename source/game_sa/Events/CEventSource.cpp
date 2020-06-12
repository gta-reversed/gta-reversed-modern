#include "StdInc.h"

int CEventSource::ComputeEventSourceType(CEvent* event, CPed* ped) {
    return plugin::CallAndReturn<int, 0x4ABAC0, CEvent*, CPed*>(event, ped);
}