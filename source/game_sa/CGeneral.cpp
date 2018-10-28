/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "CGeneral.h"

// Converted from cdecl float CGeneral::LimitAngle(float angle) 0x53CB00
float CGeneral::LimitAngle(float angle) {
    return ((float(__cdecl *)(float))0x53CB00)(angle);
}

// Converted from cdecl float CGeneral::LimitRadianAngle(float angle) 0x53CB50
float CGeneral::LimitRadianAngle(float angle) {
    return ((float(__cdecl *)(float))0x53CB50)(angle);
}

// Converted from cdecl float CGeneral::GetRadianAngleBetweenPoints(float x1,float y1,float x2,float y2) 0x53CBE0
float CGeneral::GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2) {
    return ((float(__cdecl *)(float, float, float, float))0x53CBE0)(x1, y1, x2, y2);
}

// Converted from cdecl float CGeneral::GetATanOfXY(float x,float y) 0x53CC70
float CGeneral::GetATanOfXY(float x, float y) {
    return ((float(__cdecl *)(float, float))0x53CC70)(x, y);
}

// Converted from cdecl uchar CGeneral::GetNodeHeadingFromVector(float x,float y) 0x53CDC0
unsigned char CGeneral::GetNodeHeadingFromVector(float x, float y) {
    return ((unsigned char(__cdecl *)(float, float))0x53CDC0)(x, y);
}

// Converted from cdecl bool CGeneral::SolveQuadratic(float a,float b,float c,float &x1,float &x2) 0x53CE30
bool CGeneral::SolveQuadratic(float a, float b, float c, float& x1, float& x2) {
    return ((bool(__cdecl *)(float, float, float, float&, float&))0x53CE30)(a, b, c, x1, x2);
}

// Converted from cdecl float CGeneral::GetAngleBetweenPoints(float x1,float y1,float x2,float y2) 0x53CEA0
float CGeneral::GetAngleBetweenPoints(float x1, float y1, float x2, float y2) {
    return ((float(__cdecl *)(float, float, float, float))0x53CEA0)(x1, y1, x2, y2);
}

// Converted from cdecl uint CGeneral::GetRandomNumberInRange(int min, int max) 0x407180
unsigned int CGeneral::GetRandomNumberInRange(int min, int max) {
    return ((unsigned int(__cdecl *)(int, int))0x407180)(min, max);
}

// Converted from cdecl float CGeneral::GetRandomNumberInRange(float min,float max) 0x41BD90
float CGeneral::GetRandomNumberInRange(float min, float max) {
    return ((float(__cdecl *)(float, float))0x41BD90)(min, max);
}

void CGeneral::CamShakeNoPos(CCamera *camera, float strength)
{
    ((void(__cdecl *)(CCamera*, float))0x50A970)(camera, strength);
}