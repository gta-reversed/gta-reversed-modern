#pragma once
#include "CEventEditableResponse.h"
#include "CVector.h"

class CEventSoundQuiet : public CEventEditableResponse
{
public:
    class CEntity* m_pEntity;
    float someFloat;
    unsigned int m_dwStartTime;
    CVector m_vPosition;
    unsigned char padding[36];

    CEventSoundQuiet* Constructor(CEntity* pEntity, float a3, int startTime, CVector* position);
    CEventSoundQuiet* Destructor();

    // temporary solution to make the compiler shutup
    eEventType GetEventType() override { assert(0); return (eEventType)0; }
    int GetEventPriority() override { assert(0); return 0; }
    int GetLifeTime() override { assert(0); return 0; }
    CEvent* Clone() override { assert(0); return nullptr; }
    CEventEditableResponse* CloneEditable() override { assert(0); return nullptr; }
};