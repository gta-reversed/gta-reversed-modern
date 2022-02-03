#include "StdInc.h"

/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

CRope(&CRopes::aRopes)[MAX_NUM_ROPES] = *(CRope(*)[MAX_NUM_ROPES])0xB768B8;
int32& CRopes::PlayerControlsCrane = *(int32*)0xB76898;


void CRopes::CreateRopeForSwatPed(const CVector& startPos)
{
    ((void(__cdecl*)(const CVector&))0x558D10)(startPos);
}
float CRopes::FindPickupHeight(CEntity* entity)
{
    return plugin::CallAndReturn<float, 0x556760, CEntity*>(entity);
}
int32 CRopes::FindRope(uint32 id)
{
    return ((int32(__cdecl*)(uint32))0x556000)(id);
}
void CRopes::Init()
{
    ((void(__cdecl*)())0x555DC0)();
}
bool CRopes::IsCarriedByRope(CEntity* entity)
{
    return ((bool(__cdecl*)(CEntity*))0x555F80)(entity);
}
bool CRopes::RegisterRope(CEntity* ropeId, uint32 ropeType, CVector startPos, bool bExpires, uint8 segmentCount, uint8 flags, CEntity* holder, uint32 timeExpire)
{
    return ((bool(__cdecl*)(CEntity*, uint32, CVector, bool, uint8, uint8, CEntity*, uint32))0x556B40)(ropeId, ropeType, startPos, bExpires, segmentCount, flags, holder, timeExpire);
}
void CRopes::Render()
{
    ((void(__cdecl*)())0x556AE0)();
}
void CRopes::SetSpeedOfTopNode(uint32 ropeId, CVector dirSpeed)
{
    ((void(__cdecl*)(uint32, CVector))0x555DF0)(ropeId, dirSpeed);
}
void CRopes::Shutdown()
{
    ((void(__cdecl*)())0x556B10)();
}
void CRopes::Update()
{
    ((void(__cdecl*)())0x558D70)();
}

bool CRopes::FindCoorsAlongRope(uint32 ropeId, float fCoorAlongRope, CVector* pVecPosition, CVector* arg4)
{
    return plugin::CallAndReturn<bool, 0x555E40, uint32, float, CVector*, CVector*>(ropeId, fCoorAlongRope, pVecPosition, arg4);
}
