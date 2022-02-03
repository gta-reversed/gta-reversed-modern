/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "SimpleTransform.h"

void CSimpleTransform::UpdateRwMatrix(RwMatrix* out)
{
    ((void(__thiscall*)(CSimpleTransform*, RwMatrix*))0x54EF40)(this, out);
}

void CSimpleTransform::Invert(const CSimpleTransform& base)
{
    ((void(__thiscall*)(CSimpleTransform*, const CSimpleTransform&))0x54EF90)(this, base);
}

void CSimpleTransform::UpdateMatrix(CMatrix* out)
{
    ((void(__thiscall*)(CSimpleTransform*, class CMatrix*))0x54F1B0)(this, out);
}
