#include "StdInc.h"

void CEventGunShotWhizzedBy::InjectHooks()
{
    ReversibleHooks::Install(0x4B1FD0, &CEventGunShotWhizzedBy::Constructor);
    ReversibleHooks::Install(0x4B5120, &CEventGunShotWhizzedBy::AffectsPed_Reversed);
}

CEventGunShotWhizzedBy::CEventGunShotWhizzedBy(CEntity* entity, CVector const& startPoint, CVector const& endPoint, bool bHasNoSound) :
    CEventGunShot(entity, startPoint, endPoint, bHasNoSound)
{
}

CEventGunShotWhizzedBy* CEventGunShotWhizzedBy::Constructor(CEntity* entity, CVector const& startPoint, CVector const& endPoint, bool bHasNoSound)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventGunShotWhizzedBy*, 0x4B1FD0, CEvent*, CEntity*, CVector const&, CVector const&, bool>(this, entity, startPoint, endPoint, bHasNoSound);
#else
    this->CEventGunShotWhizzedBy::CEventGunShotWhizzedBy(entity, startPoint, endPoint, bHasNoSound);
    return this;
#endif
}

bool CEventGunShotWhizzedBy::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B5120, CEvent*, CPed*>(this, ped);
#else
    return CEventGunShotWhizzedBy::AffectsPed_Reversed(ped);
#endif
}

bool CEventGunShotWhizzedBy::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsPlayer() && ped->IsAlive()) {
        CVector direction = m_endPoint - m_startPoint;
        direction.Normalise();
        CVector distance = ped->GetPosition() - m_startPoint;
        float squaredMagnitude = (distance * direction).SquaredMagnitude();
        if (squaredMagnitude > 0.0f) {
            CVector2D point = (direction * squaredMagnitude) + m_startPoint;
            CVector2D distance = ped->GetPosition() - point;
            return 2.0f * 2.0f > distance.SquaredMagnitude();
        }
    }
    return false;
}

