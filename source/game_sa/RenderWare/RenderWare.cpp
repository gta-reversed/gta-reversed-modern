/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

RwGlobals *&RwEngineInstance = *(RwGlobals **)0xC97B24;

RsGlobalType &RsGlobal = *(RsGlobalType *)0xC17040;

RwPluginRegistry &geometryTKList = *(RwPluginRegistry *)0x8D628C;

RtDictSchema &RpUVAnimDictSchema = *(RtDictSchema *)0x8DED50;

IDirect3DDevice9 *GetD3DDevice() {
    return *reinterpret_cast<IDirect3DDevice9 **>(0xC97C28);
}

_D3DMATRIX *GetD3DViewTransform() {
    return reinterpret_cast<_D3DMATRIX *>(0xC9BC80);
}

_D3DMATRIX *GetD3DProjTransform() {
    return reinterpret_cast<_D3DMATRIX *>(0x8E2458);
}

void _rpMaterialSetDefaultSurfaceProperties(RwSurfaceProperties *surfProps);

void _rpMaterialSetDefaultSurfaceProperties(RwSurfaceProperties *surfProps) {
    ((void(__cdecl *)(RwSurfaceProperties*))0x74D870)(surfProps);
}

