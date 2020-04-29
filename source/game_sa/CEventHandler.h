/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CEventHandlerHistory.h"

class CTask;
class CEvent;

class CEventHandler {
public:
    class CPed *m_pPed;
    CEventHandlerHistory m_history;
    int field_20;
    CTask* m_pResponseTask;
    int field_28;
    int field_2C;
    int field_30;

    void HandleEvents();
    void FlushImmediately();
    static bool IsTemporaryEvent(CEvent* _event);
};

VALIDATE_SIZE(CEventHandler, 0x34);