/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CBox* CClumpModelInfo::GetBoundingBox()
{
    return ((CBox * (__thiscall*)(CClumpModelInfo*))plugin::GetVMT(this, 15))(this);
}

void CClumpModelInfo::SetClump(RpClump* clump)
{
    ((void(__thiscall*)(CClumpModelInfo*, RpClump*))0x4C4F70)(this, clump);
}

void CClumpModelInfo::SetAtomicRendererCB(RpAtomic* atomic, void* renderFunc)
{
    ((void(__cdecl*)(RpAtomic*, void*))0x4C5280)(atomic, renderFunc);
}

RwFrame* CClumpModelInfo::FindFrameFromNameCB(RwFrame* frame, void* searchData)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x4C52A0)(frame, searchData);
}

RwFrame* CClumpModelInfo::FindFrameFromNameWithoutIdCB(RwFrame* frame, void* searchData)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x4C52F0)(frame, searchData);
}

RwFrame* CClumpModelInfo::FindFrameFromIdCB(RwFrame* frame, void* searchData)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x4C5350)(frame, searchData);
}

RwFrame* CClumpModelInfo::FillFrameArrayCB(RwFrame* frame, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x4C5390)(frame, data);
}

RwFrame* CClumpModelInfo::GetFrameFromId(RpClump* clump, int id)
{
    return ((RwFrame * (__cdecl*)(RpClump*, int))0x4C53C0)(clump, id);
}

RwFrame* CClumpModelInfo::GetFrameFromName(RpClump* clump, char* name)
{
    return ((RwFrame * (__cdecl*)(RpClump*, char*))0x4C5400)(clump, name);
}

void CClumpModelInfo::FillFrameArray(RpClump* clump, RwFrame** frames)
{
    ((void(__cdecl*)(RpClump*, RwFrame * *))0x4C5440)(clump, frames);
}

// Converted from thiscall void CClumpModelInfo::SetFrameIds(RwObjectNameIdAssocation *data) 0x4C5460
void CClumpModelInfo::SetFrameIds(RwObjectNameIdAssocation* data) {
    plugin::CallMethod<0x4C5460, CClumpModelInfo*, RwObjectNameIdAssocation*>(this, data);
}