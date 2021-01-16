#include "StdInc.h"

CEscalator(&CEscalators::aEscalators)[NUM_ESCALATORS] = *(CEscalator(*)[NUM_ESCALATORS])0xC6E9A8;

void CEscalators::Init()
{
    plugin::Call<0x717C50>();
}

void CEscalators::Shutdown()
{
    plugin::Call<0x717940>();
}

void CEscalators::Update()
{
    plugin::Call<0x718580>();
}

void CEscalators::AddOne(CVector const& vecStart, CVector const& vecBottom, CVector const& vecEnd, CVector const& vecTop, bool bMoveDown, CEntity* pEntity)
{
    plugin::Call<0x717C90, CVector const&, CVector const&, CVector const&, CVector const&, bool, CEntity*>
        (vecStart, vecBottom, vecEnd, vecTop, bMoveDown, pEntity);
}
