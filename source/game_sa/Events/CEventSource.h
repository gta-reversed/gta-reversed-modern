#pragma once

class CEvent;
class CPed;

class CEventSource {
public:
    static int ComputeEventSourceType(CEvent* event, CPed* ped);
};