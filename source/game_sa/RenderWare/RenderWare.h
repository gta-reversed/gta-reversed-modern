/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "rw/rwcore.h"
#include "rw/rphanim.h"
#include "rw/rpuvanim.h"
#include "rw/rpskin.h"
#include "rw/rpmatfx.h"
#include "rw/skeleton.h"

#ifdef _DX9_SDK_INSTALLED
#include "d3d9.h"
#endif

extern RwGlobals *&RwEngineInstance;

/* macro used to access global data structure (the root type is RwGlobals) */
#define RWSRCGLOBAL(variable) (RwEngineInstance->variable)

extern RsGlobalType &RsGlobal;

extern RwPluginRegistry &geometryTKList;

extern RtDictSchema &RpUVAnimDictSchema;

struct IDirect3DDevice9 *GetD3DDevice();

#ifndef D3DMATRIX_DEFINED
struct _D3DMATRIX;
#endif

_D3DMATRIX *GetD3DViewTransform();
_D3DMATRIX *GetD3DProjTransform();

#define RWRSTATE(a) (reinterpret_cast<void *>(a))

#define PLUGINOFFSET(type, base, offset) ((type*)((char*)(base) + (offset)))
