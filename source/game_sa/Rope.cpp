#include "StdInc.h"

/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

void CRope::CreateHookObjectForRope()
{
    ((void(__thiscall*)(CRope*))0x556070)(this);
}

void CRope::PickUpObject(CEntity* object)
{
    ((void(__thiscall*)(CRope*, CEntity*))0x5569C0)(this, object);
}

void CRope::ReleasePickedUpObject()
{
    ((void(__thiscall*)(CRope*))0x556030)(this);
}

void CRope::Remove()
{
    ((void(__thiscall*)(CRope*))0x556780)(this);
}

void CRope::Render()
{
    ((void(__thiscall*)(CRope*))0x556800)(this);
}

void CRope::Update()
{
    ((void(__thiscall*)(CRope*))0x557530)(this);
}

void CRope::UpdateWeightInRope(CVector a1, float a2, CVector* a3)
{
    ((void(__thiscall*)(CRope*, CVector, float, CVector*))0x5561B0)(this, a1, a2, a3);
}
