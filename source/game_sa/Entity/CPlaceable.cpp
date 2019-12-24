/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

unsigned int CPlaceable::DeletingDestructor(uint8_t deletingFlags)
{
    return((unsigned int (__thiscall*)(CPlaceable*, uint8_t))plugin::GetVMT(this, 0))(this, deletingFlags);
}

CVector* CPlaceable::GetRightDirection(CVector* pOut)
{
    return ((CVector*(__thiscall*)(CPlaceable*, CVector*))0x41CC70)(this, pOut);
}

CVector* CPlaceable::GetTopDirection(CVector* pOut)
{
    return ((CVector*(__thiscall*)(CPlaceable*, CVector*))0x41CCB0)(this, pOut);
}

CVector* CPlaceable::GetAtDirection(CVector* pOut)
{
    return ((CVector*(__thiscall*)(CPlaceable*, CVector*))0x50E420)(this, pOut);
}

void CPlaceable::SetPosn(float x, float y, float z)
{
    ((void(__thiscall*)(CPlaceable*, float, float, float))0x420B80)(this, x, y, z);
}

void CPlaceable::SetPosn(CVector const& posn)
{
    ((void(__thiscall*)(CPlaceable*, CVector const&))0x4241C0)(this, posn);
}

void CPlaceable::SetOrientation(float x, float y, float z)
{
    ((void(__thiscall*)(CPlaceable*, float, float, float))0x439A80)(this, x, y, z);
}

void CPlaceable::SetHeading(float heading)
{
    ((void(__thiscall*)(CPlaceable*, float))0x43E0C0)(this, heading);
}

float CPlaceable::GetHeading()
{
    return ((float(__thiscall*)(CPlaceable*))0x441DB0)(this);
}

bool CPlaceable::IsWithinArea(float x1, float y1, float x2, float y2)
{
    return ((bool(__thiscall*)(CPlaceable*, float, float, float, float))0x54F200)(this, x1, y1, x2, y2);
}

bool CPlaceable::IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return ((bool(__thiscall*)(CPlaceable*, float, float, float, float, float, float))0x54F2B0)(this, x1, y1, z1, x2, y2, z2);
}

void CPlaceable::RemoveMatrix()
{
    ((void(__thiscall*)(CPlaceable*))0x54F3B0)(this);
}

void CPlaceable::AllocateStaticMatrix()
{
    ((void(__thiscall*)(CPlaceable*))0x54F4C0)(this);
}

void CPlaceable::AllocateMatrix()
{
    ((void(__thiscall*)(CPlaceable*))0x54F560)(this);
}

void CPlaceable::SetMatrix(CMatrix  const& matrix)
{
    ((void(__thiscall*)(CPlaceable*, CMatrix  const&))0x54F610)(this, matrix);
}

CMatrixLink* CPlaceable::GetMatrix() {
    return ((CMatrixLink * (__thiscall*)(CPlaceable*))0x411990)(this);
}

void CPlaceable::ShutdownMatrixArray() {
    ((void(__cdecl*)())0x54EFD0)();
}

void CPlaceable::InitMatrixArray() {
    ((void(__cdecl*)())0x54F3A0)();
}

void CPlaceable::FreeStaticMatrix() {
    ((void(__thiscall*)(CPlaceable*))0x54F010)(this);
}

void CPlaceable::GetOrientation(float& x, float& y, float& z)
{
    if (this->m_matrix)
    {
        x = asinf(this->m_matrix->up.z);

        float cosx = cosf(x);
        float cosy = this->m_matrix->at.z / cosx;
        y = acosf(cosy);
        float cosz = this->m_matrix->up.y / cosx;
        z = acosf(cosz);
    }
    else
    {
        z = this->m_placement.m_fHeading;
    }
}