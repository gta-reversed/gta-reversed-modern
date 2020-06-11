#include "StdInc.h"

cBuoyancy& mod_Buoyancy = *(cBuoyancy*)0xC1C890;

void cBuoyancy::InjectHooks()
{
    HookInstall(0x6C2750, &cBuoyancy::CalcBuoyancyForce);
    HookInstall(0x6C3EF0, &cBuoyancy::ProcessBuoyancy);
}

bool cBuoyancy::ProcessBuoyancy(CPhysical* pEntity, float fBuoyancy, CVector* pVecTurnSpeed, CVector* pBuoyancy)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x6C3EF0, cBuoyancy*, CEntity*, float, CVector*, CVector*> 
        (this, pEntity, fBuoyancy, pVecTurnSpeed, pBuoyancy);
#else
    CVector& entityPosition = pEntity->GetPosition();
    if (CWaterLevel::GetWaterLevel(entityPosition.x, entityPosition.y, entityPosition.z,
        &m_fWaterLevel, pEntity->physicalFlags.bTouchingWater, false))
    {
        m_EntityMatrix = *pEntity->m_matrix;
        PreCalcSetup(pEntity, fBuoyancy);
        if (pEntity->m_nType == ENTITY_TYPE_PED)
        {
            pEntity->GetColModel(); // for some reason, this is here?

            field_98 = 1;
            m_fDistanceToWaterSurfaceZ = ((m_fWaterLevel - entityPosition.z) + 1.0f) / 1.9f;
            if (m_fDistanceToWaterSurfaceZ > 1.0f)
            {
                m_fDistanceToWaterSurfaceZ = 1.0f;
            }
            else {
                if (m_fDistanceToWaterSurfaceZ < 0.0f) 
                {
                    m_fDistanceToWaterSurfaceZ = 0.0f;
                    field_98 = 0;
                }
            }

            m_vecMoveForce = CVector(0.0f, 0.0f, 0.0f);
            if (m_fDistanceToWaterSurfaceZ > 0.0f && m_fDistanceToWaterSurfaceZ < 1.0f)
            {
                float fDistanceZ = m_fWaterLevel - entityPosition.z;
                CVector forward = pEntity->GetForwardVector();
                cBuoyancy::AddSplashParticles
                    (pEntity, CVector(0.0f, 0.0f, fDistanceZ), 
                        CVector(0.0f, 0.0f, fDistanceZ), 
                        CVector(-forward.x, -forward.y,-forward.z), true);
            }
        }
        else 
        {
            SimpleCalcBuoyancy(pEntity);
        }

        bool bCalcBuoyancyForce = CalcBuoyancyForce(pEntity, pVecTurnSpeed, pBuoyancy);
        if (m_bProcessingBoat || bCalcBuoyancyForce)
        {
            return true;
        }
    }
    return false;
#endif
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
    const float fCurrentBuoyancy = m_fDistanceToWaterSurfaceZ * m_fBuoyancy * CTimer::ms_fTimeStep;
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

float cBuoyancy::PreCalcSetup(CPhysical* pEntity, float fBuoyancy)
{
    return plugin::CallMethodAndReturn<float, 0x6C2B90, cBuoyancy*, CPhysical*, float>(this, pEntity, fBuoyancy);
}

void cBuoyancy::AddSplashParticles(CPhysical* pEntity, CVector a3, CVector a4, CVector a5, bool bUnknown)
{
    plugin::CallMethod<0x6C34E0, cBuoyancy*, CPhysical*, CVector, CVector, CVector, bool>(this, pEntity, a3, a4, a5, bUnknown);
}

void cBuoyancy::SimpleCalcBuoyancy(CPhysical* pEntity)
{
    plugin::CallMethod<0x6C3B00, cBuoyancy*, CPhysical*>(this, pEntity);
}
