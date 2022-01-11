#pragma once
//////////////////////////////////////////////////////////////////////////////////////
// This file contains "inline" functions which were either macros or simply inline
// functions originally in GTA:SA source code. If inline functions can do what macros
// can then why not inline functions? ;)
//////////////////////////////////////////////////////////////////////////////////////

#include "RenderWare.h"
#include "Animation\AnimBlendClumpData.h"

inline CAnimBlendClumpData * GetAnimClumpData(RpClump * pClump)
{
    const DWORD clumpOffset = (*(DWORD*)0xB5F878);
    //return reinterpret_cast <CAnimBlendClumpData *> (*(&pClump->object.type + clumpOffset));
    return reinterpret_cast <CAnimBlendClumpData *> (*(DWORD *)(clumpOffset + ((int32)pClump)  ));
}
