#pragma once
#include "PluginBase.h"
#include "CEvent.h"

class CPed;
class CEventGroupEvent : CEvent
{
public:
    unsigned char padding [64];

    CEventGroupEvent* Constructor(CPed* pPed, CEvent* damageEvent);
    void Destructor();
};

VALIDATE_SIZE(CEventGroupEvent, 0x44);