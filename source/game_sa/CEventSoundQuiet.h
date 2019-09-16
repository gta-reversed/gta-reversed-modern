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
};