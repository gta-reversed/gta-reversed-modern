#include "StdInc.h"

#include "Projectile.h"

CProjectile::CProjectile(int32 modelId) : CObject() {
    m_bTunnelTransition = true;
    m_fMass = 1.0F;
    m_fTurnMass = 1.0F;
    m_fAirResistance = 0.99999F;
    m_fElasticity = 0.75F;
    m_fBuoyancyConstant = 1.0F / 1250.0F; // 0.0008F
    CObject::SetIsStatic(false);
    physicalFlags.bExplosionProof = true;
    CEntity::SetModelIndex(modelId);
    m_nObjectType = eObjectType::OBJECT_TYPE_DECORATION;
}
