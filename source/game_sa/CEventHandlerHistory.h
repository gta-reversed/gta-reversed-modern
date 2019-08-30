#pragma once
#include "PluginBase.h"
#include "CTaskTimer.h"

class CEvent;
class CEventHandlerHistory
{
public:
    int field_0;
    CEvent* m_pNonTempEvent;
    CEvent* m_pTempEvent;
    CEvent* m_pStoredActiveEvent;
    CTaskTimer m_storedActiveEventTimer;

    void ClearAllEvents();
};

VALIDATE_SIZE(CEventHandlerHistory, 0x1C);