#include "StdInc.h"

cBuoyancy& mod_Buoyancy = *(cBuoyancy*)0xC1C890;

void cBuoyancy::InjectHooks()
{
    HookInstall(0x6C2750, &cBuoyancy::CalcBuoyancyForce, 7);
}

bool cBuoyancy::ProcessBuoyancy(CEntity* pEntity, float fBuoyancy, CVector* pOutVecMoveForce, CVector* pOutVecTurnForce)
{
    return plugin::CallMethodAndReturn<bool, 0x6C3EF0, cBuoyancy*, CEntity*, float, CVector*, CVector*> 
        (this, pEntity, fBuoyancy, pOutVecMoveForce, pOutVecTurnForce);
}


bool cBuoyancy::CalcBuoyancyForce(CPhysical* pEntity, CVector* pVecTurnSpeed, CVector* pBuoyancy)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x6C2750, cBuoyancy*, CPhysical* , CVector*, CVector*>(this, pEntity, pVecTurnSpeed, pBuoyancy);
#else
    if (!field_98)
    {
        return false;
    }

    CVector vecOut;
    *pVecTurnSpeed = *Multiply3x3(&vecOut, &m_EntityMatrix, &m_vecMoveForce);
    const float fCurrentBuoyancy = fTurnForceZ * m_fBuoyancy * CTimer::ms_fTimeStep;
    *pBuoyancy = CVector(0.0f, 0.0f, fCurrentBuoyancy);

    float fSubmerge = pEntity->m_fMass * pEntity->m_vecMoveSpeed.z;
    if (fSubmerge <= fCurrentBuoyancy * 4.0f)
    {
        return true;
    }

    float fBuoyancy = fCurrentBuoyancy - fSubmerge;
    if (fBuoyancy < 0.0f)
    {
        fBuoyancy = 0.0f;
    }
    pBuoyancy->z = fBuoyancy;
    return true;
#endif
}