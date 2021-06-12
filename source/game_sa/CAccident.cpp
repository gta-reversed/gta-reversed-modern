#include "StdInc.h"

CAccident::CAccident()
{
    m_pPed = nullptr;
    m_bIsTreated = false;
    m_bIsRevived = false;
}

bool CAccident::IsFree()
{
    return m_pPed && !m_bIsTreated && !m_bIsRevived && !m_pPed->physicalFlags.bSubmergedInWater;
}
