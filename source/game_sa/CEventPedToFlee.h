#pragma once
#include "CEvent.h"

class CEventPedToFlee : public CEvent
{
public:
    unsigned char padding[64];

    CEventPedToFlee* Constructor(CPed* pPed);
    CEventPedToFlee* Destructor();
};

VALIDATE_SIZE(CEventPedToFlee, 0x44);