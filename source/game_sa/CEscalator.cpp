#include "StdInc.h"

void CEscalator::SwitchOff()
{
    plugin::CallMethod<0x717860, CEscalator*>(this);
}

void CEscalator::AddThisOne(CVector const& vecStart, CVector const& vecBottom, CVector const& vecEnd, CVector const& vecTop, bool bMoveDown, CEntity* pEntity)
{
    plugin::CallMethod<0x717970, CEscalator*, CVector const&, CVector const&, CVector const&, CVector const&, bool, CEntity*>
        (this, vecStart, vecBottom, vecEnd, vecTop, bMoveDown, pEntity);
}

void CEscalator::Update()
{
    plugin::CallMethod<0x717D30, CEscalator*>(this);
}
