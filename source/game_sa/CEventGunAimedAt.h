#pragma once
#include "CEvent.h"

class CPed;

class CEventGunAimedAt : CEvent
{
public:
    unsigned char padding [64];

   CEventGunAimedAt* Constructor (CPed* pPed);
   void Destructor();
};

VALIDATE_SIZE(CEventGunAimedAt, 0x44);