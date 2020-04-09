#pragma once
#include "PluginBase.h"
#include "CEvent.h"

class CTask;

class CEventScriptCommand : public CEvent
{
public:
    unsigned char padding[56];
    CEventScriptCommand* Constructor(int command, CTask* pTask, char a3);
    void Destructor();

    // temporary solution to make the compiler shutup
    eEventType GetEventType() override { assert(0); return (eEventType)0; }
    int GetEventPriority() override { assert(0); return 0; }
    int GetLifeTime() override { assert(0); return 0; }
    CEvent* Clone() override { assert(0); return nullptr; }
};

VALIDATE_SIZE(CEventScriptCommand, 0x44);