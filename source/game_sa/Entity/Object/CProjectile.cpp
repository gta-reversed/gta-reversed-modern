#include "StdInc.h"

CProjectile::CProjectile(int dwModelId) : CObject()
{
    m_bTunnelTransition = true;
    m_fMass = 1.0F;
    m_fTurnMass = 1.0F;
    m_fAirResistance = 0.99999F;
    m_fElasticity = 0.75F;
    m_fBuoyancyConstant = 0.0008F; // 1.0 / 1250.0
    CObject::SetIsStatic(false);
    physicalFlags.bExplosionProof = true;
    CEntity::SetModelIndex(dwModelId);
    m_nObjectType = eObjectType::OBJECT_TYPE_DECORATION;
}
