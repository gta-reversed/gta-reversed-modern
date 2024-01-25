#pragma once


#include "EventSource.h"


class CEventSource {
public:
    static int32 ComputeEventSourceType(const CEvent& event, const CPed& ped);
};

