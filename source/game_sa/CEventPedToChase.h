#pragma once
#include "CEvent.h"

class CPed;

class CEventPedToChase : public CEvent
{
public:
    unsigned char padding[56];

    CEventPedToChase* Constructor(CPed* pPed);
    CEventPedToChase* Destructor();

    // temporary solution to make the compiler shutup
    eEventType GetEventType() override { assert(0); return (eEventType)0; }
    int GetEventPriority() override { assert(0); return 0; }
    int GetLifeTime() override { assert(0); return 0; }
    CEvent* Clone() override { assert(0); return nullptr; }
};

VALIDATE_SIZE(CEventPedToChase, 0x44);