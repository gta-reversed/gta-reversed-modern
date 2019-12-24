/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CRect::CRect(float x1, float y1, float x2, float y2)
{
    ((void(__thiscall*)(CRect*, float, float, float, float))0x4041C0)(this, x1, y1, x2, y2);
}

CRect::CRect()
{
    ((void(__thiscall*)(CRect*))0x4041E0)(this);
}

bool CRect::IsFlipped()
{
    return ((bool(__thiscall*)(CRect*))0x404190)(this);
}

void CRect::Restrict(CRect const& restriction)
{
    ((void(__thiscall*)(CRect*, CRect const&))0x404200)(this, restriction);
}

void CRect::Resize(float resizeX, float resizeY)
{
    ((void(__thiscall*)(CRect*, float, float))0x404260)(this, resizeX, resizeY);
}

bool CRect::IsPointInside(CVector2D const& point)
{
    return ((bool(__thiscall*)(CRect*, CVector2D const&))0x404290)(this, point);
}

bool CRect::IsCircleInside(CVector2D const& circleCenter, float circleRadius)
{
    return ((bool(__thiscall*)(CRect*, CVector2D const&, float))0x4042D0)(this, circleCenter, circleRadius);
}

void CRect::SetFromCenter(float x, float y, float size)
{
    ((void(__thiscall*)(CRect*, float, float, float))0x43E020)(this, x, y, size);
}

void CRect::GetCenter(float* x, float* y)
{
    ((void(__thiscall*)(CRect*, float*, float*))0x43E050)(this, x, y);
}

void CRect::StretchToPoint(float x, float y)
{
    ((void(__thiscall*)(CRect*, float, float))0x5327F0)(this, x, y);
}