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
    const float sinHeading = std::sin(m_fHeading);
    const float cosHeading = std::cos(m_fHeading);

    out->right = { cosHeading, sinHeading, 0.0 };
    out->up = { -sinHeading, cosHeading, 0.0 };
    out->at = { 0.0, 0.0, 1.0 };
    out->pos = this->m_vPosn;

    RwMatrixUpdate(out);

  //  ((void(__thiscall*)(CSimpleTransform*, RwMatrix*))0x54EF40)(this, out);
}

void CSimpleTransform::Invert(const CSimpleTransform& base)
{
    const float cosHeading = cosf(base.m_fHeading);
    const float sinHeading = sinf(base.m_fHeading);

    this->m_vPosn.x = -(cosHeading * base.m_vPosn.x) - (sinHeading * base.m_vPosn.y);
    this->m_vPosn.y = (sinHeading * base.m_vPosn.x) - (cosHeading * base.m_vPosn.y);
    this->m_vPosn.z = -base.m_vPosn.z;
    this->m_fHeading = -base.m_fHeading;

  //  ((void(__thiscall*)(CSimpleTransform*, const CSimpleTransform&))0x54EF90)(this, base);
}

void CSimpleTransform::UpdateMatrix(CMatrix* out)
{
    out->SetTranslate(m_vPosn);
    out->SetRotateZOnly(m_fHeading);

   // ((void(__thiscall*)(CSimpleTransform*, class CMatrix*))0x54F1B0)(this, out);
}
