#pragma once
#include "CEvent.h"

class CPed;

class CEventGunAimedAt : public CEvent
{
public:
    unsigned char padding [56];

   CEventGunAimedAt* Constructor (CPed* pPed);
   void Destructor();

   // temporary solution to make the compiler shutup
   eEventType GetEventType() override { assert(0); return (eEventType)0; }
   int GetEventPriority() override { assert(0); return 0; }
   int GetLifeTime() override { assert(0); return 0; }
   CEvent* Clone() override { assert(0); return nullptr; }
};

VALIDATE_SIZE(CEventGunAimedAt, 0x44);