#pragma once
#include "PluginBase.h"
#include "CEvent.h"

class CTask;

class CEventScriptCommand : public CEvent
{
public:
    unsigned char padding[64];
    CEventScriptCommand* Constructor(int command, CTask* pTask, char a3);
    void Destructor();
};

VALIDATE_SIZE(CEventScriptCommand, 0x44);