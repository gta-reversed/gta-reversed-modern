#pragma once
#include "CEvent.h"

class CPed;

class CEventPedToChase : public CEvent
{
public:
    unsigned char padding[64];

    CEventPedToChase* Constructor(CPed* pPed);
    CEventPedToChase* Destructor();
};

VALIDATE_SIZE(CEventPedToChase, 0x44);