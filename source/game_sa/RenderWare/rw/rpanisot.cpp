#include "StdInc.h"

#include "rpanisot.h"

RwInt8 RpAnisotGetMaxSupportedMaxAnisotropy() {
    return ((RwInt8(__cdecl *)())0x748F20)();
}

RwTexture* RpAnisotTextureSetMaxAnisotropy(RwTexture* tex, RwInt8 val) {
    return ((RwTexture*(__cdecl *)(RwTexture*, RwInt8))0x748F30)(tex, val);
}

RwInt8 RpAnisotTextureGetMaxAnisotropy(RwTexture* tex) {
    return ((RwInt8(__cdecl *)(RwTexture*))0x748F50)(tex);
}

RwBool RpAnisotPluginAttach() {
    return ((RwBool(__cdecl *)())0x748F70)();
}
