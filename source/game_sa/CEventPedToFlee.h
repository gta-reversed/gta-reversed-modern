#pragma once
#include "CEvent.h"

class CEventPedToFlee : public CEvent
{
public:
    unsigned char padding[56];

    CEventPedToFlee* Constructor(CPed* pPed);
    CEventPedToFlee* Destructor();

    // temporary solution to make the compiler shutup
    eEventType GetEventType() override { assert(0); return (eEventType)0; }
    int GetEventPriority() override { assert(0); return 0; }
    int GetLifeTime() override { assert(0); return 0; }
    CEvent* Clone() override { assert(0); return nullptr; }
};

VALIDATE_SIZE(CEventPedToFlee, 0x44);