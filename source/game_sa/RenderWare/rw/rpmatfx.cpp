#include "StdInc.h"

#include "rpmatfx.h"

void RpMatFXMaterialDataSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    ((void(__cdecl *)(RwInt32, RwInt32))0x810700)(blockSize, numBlocksToPrealloc);
}

RwBool RpMatFXPluginAttach() {
    return ((RwBool(__cdecl *)(void))0x810AA0)();
}

RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic) {
    return ((RpAtomic*(__cdecl *)(RpAtomic*))0x811C00)(atomic);
}

RwBool RpMatFXAtomicQueryEffects(RpAtomic* atomic) {
    return ((RwBool(__cdecl *)(RpAtomic*))0x811C30)(atomic);
}

RpWorldSector* RpMatFXWorldSectorEnableEffects(RpWorldSector* worldSector) {
    return ((RpWorldSector*(__cdecl *)(RpWorldSector*))0x811C40)(worldSector);
}

RwBool RpMatFXWorldSectorQueryEffects(RpWorldSector* worldSector) {
    return ((RwBool(__cdecl *)(RpWorldSector*))0x811C70)(worldSector);
}

RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, RpMatFXMaterialFlags flags) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RpMatFXMaterialFlags))0x811C80)(material, flags);
}

RpMaterial* RpMatFXMaterialSetupBumpMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwFrame*, RwReal))0x811E00)(material, texture, frame, coef);
}

RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwBool useFrameBufferAlpha, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwFrame*, RwBool, RwReal))0x811ED0)(material, texture, frame, useFrameBufferAlpha, coef);
}

RpMaterial* RpMatFXMaterialSetupDualTexture(RpMaterial* material, RwTexture* texture, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*, RwBlendFunction, RwBlendFunction))0x812040)(material, texture, srcBlendMode, dstBlendMode);
}

RpMatFXMaterialFlags RpMatFXMaterialGetEffects(const RpMaterial* material) {
    return ((RpMatFXMaterialFlags(__cdecl *)(const RpMaterial*))0x812140)(material);
}

RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812160)(material, texture);
}

RpMaterial* RpMatFXMaterialSetBumpMapFrame(RpMaterial* material, RwFrame* frame) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwFrame*))0x812320)(material, frame);
}

RpMaterial* RpMatFXMaterialSetBumpMapCoefficient(RpMaterial* material, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x812380)(material, coef);
}

RwTexture* RpMatFXMaterialGetBumpMapTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x812430)(material);
}

RwTexture* RpMatFXMaterialGetBumpMapBumpedTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x8123E0)(material);
}

RwFrame* RpMatFXMaterialGetBumpMapFrame(const RpMaterial* material) {
    return ((RwFrame*(__cdecl *)(const RpMaterial*))0x812480)(material);
}

RwReal RpMatFXMaterialGetBumpMapCoefficient(const RpMaterial* material) {
    return ((RwReal(__cdecl *)(const RpMaterial*))0x8124D0)(material);
}

RpMaterial* RpMatFXMaterialSetEnvMapTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812530)(material, texture);
}

RpMaterial* RpMatFXMaterialSetEnvMapFrame(RpMaterial* material, RwFrame* frame) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwFrame*))0x8125B0)(material, frame);
}

RpMaterial* RpMatFXMaterialSetEnvMapFrameBufferAlpha(RpMaterial* material, RwBool useFrameBufferAlpha) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwBool))0x812610)(material, useFrameBufferAlpha);
}

RpMaterial* RpMatFXMaterialSetEnvMapCoefficient(RpMaterial* material, RwReal coef) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwReal))0x812680)(material, coef);
}

RwTexture* RpMatFXMaterialGetEnvMapTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x8126F0)(material);
}

RwFrame* RpMatFXMaterialGetEnvMapFrame(const RpMaterial* material) {
    return ((RwFrame*(__cdecl *)(const RpMaterial*))0x812740)(material);
}

RwBool RpMatFXMaterialGetEnvMapFrameBufferAlpha(const RpMaterial* material) {
    return ((RwBool(__cdecl *)(const RpMaterial*))0x812790)(material);
}

RwReal RpMatFXMaterialGetEnvMapCoefficient(const RpMaterial* material) {
    return ((RwReal(__cdecl *)(const RpMaterial*))0x8127E0)(material);
}

RpMaterial* RpMatFXMaterialSetDualTexture(RpMaterial* material, RwTexture* texture) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwTexture*))0x812830)(material, texture);
}

RpMaterial* RpMatFXMaterialSetDualBlendModes(RpMaterial* material, RwBlendFunction srcBlendMode, RwBlendFunction dstBlendMode) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwBlendFunction, RwBlendFunction))0x8128C0)(material, srcBlendMode, dstBlendMode);
}

RwTexture* RpMatFXMaterialGetDualTexture(const RpMaterial* material) {
    return ((RwTexture*(__cdecl *)(const RpMaterial*))0x812930)(material);
}

const RpMaterial* RpMatFXMaterialGetDualBlendModes(const RpMaterial* material, RwBlendFunction* srcBlendMode, RwBlendFunction* dstBlendMode) {
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwBlendFunction*, RwBlendFunction*))0x812980)(material, srcBlendMode, dstBlendMode);
}

RpMaterial* RpMatFXMaterialSetUVTransformMatrices(RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
    return ((RpMaterial*(__cdecl *)(RpMaterial*, RwMatrix*, RwMatrix*))0x8129E0)(material, baseTransform, dualTransform);
}

const RpMaterial* RpMatFXMaterialGetUVTransformMatrices(const RpMaterial* material, RwMatrix* baseTransform, RwMatrix* dualTransform) {
    return ((const RpMaterial*(__cdecl *)(const RpMaterial*, RwMatrix*, RwMatrix*))0x812A50)(material, baseTransform, dualTransform);
}

RxPipeline* RpMatFXGetD3D9Pipeline(RpMatFXD3D9Pipeline d3d9Pipeline) {
    return ((RxPipeline*(__cdecl *)(RpMatFXD3D9Pipeline))0x8162F0)(d3d9Pipeline);
}
