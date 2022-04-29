/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Pool.h"
#include "Object.h"

struct CustomEnvMapPipeMaterialData {
public:
    char  scaleX;
    char  scaleY;
    char  transSclX;
    char  transSclY;
    char  shininess;
    int16 renderFrameCounter;
    void* texture;
};
VALIDATE_SIZE(CustomEnvMapPipeMaterialData, 0xC);

struct CustomEnvMapPipeAtomicData {
    float lastTrans;
    float posx;
    float posy;
};
VALIDATE_SIZE(CustomEnvMapPipeAtomicData, 0xC);

struct CustomSpecMapPipeMaterialData {
    float specularity;
    void* texture;
};
VALIDATE_SIZE(CustomSpecMapPipeMaterialData, 0x8);

typedef CPool<CustomEnvMapPipeMaterialData>  CustomEnvMapPipeMaterialDataPool;
typedef CPool<CustomEnvMapPipeAtomicData>    CustomEnvMapPipeAtomicDataPool;
typedef CPool<CustomSpecMapPipeMaterialData> CustomSpecMapPipeMaterialDataPool;

class CCustomCarEnvMapPipeline {
public:
    static inline uint32& ms_envMapPluginOffset = *(uint32*)0x8D12C4;      // -1
    static inline uint32& ms_envMapAtmPluginOffset = *(uint32*)0x8D12C8;   // -1
    static inline uint32& ms_specularMapPluginOffset = *(uint32*)0x8D12CC; // -1
    static inline CustomEnvMapPipeMaterialData& fakeEnvMapPipeMatData = *(CustomEnvMapPipeMaterialData*)0xC02D18;
    static inline RxPipeline*& ObjPipeline = *(RxPipeline**)0xC02D24;
    static inline CustomEnvMapPipeMaterialDataPool*& m_gEnvMapPipeMatDataPool = *(CustomEnvMapPipeMaterialDataPool**)0xC02D28;
    static inline CustomEnvMapPipeAtomicDataPool*& m_gEnvMapPipeAtmDataPool = *(CustomEnvMapPipeAtomicDataPool**)0xC02D2C;
    static inline CustomSpecMapPipeMaterialDataPool*& m_gSpecMapPipeMatDataPool = *(CustomSpecMapPipeMaterialDataPool**)0xC02D30;

public:
    static int32 CustomPipeInstanceCB(int32 arg1, int32 arg2, int32(__cdecl* callback)(int32, int32, int32));
    static void PreRenderUpdate();
    static void* pluginEnvMatConstructorCB(void* object, int32 offset);
    static RwStream* pluginEnvMatStreamWriteCB(RwStream* stream, int32 length, const void* arg3, int32 arg4);
    static int32 pluginEnvMatStreamGetSizeCB(const void* arg0);
    static void* pluginEnvAtmConstructorCB(void* object, int32 offset);
    static void* pluginSpecMatConstructorCB(void* object);
    static RwStream* pluginSpecMatStreamWriteCB(RwStream* stream, int32 length, const void* object);
    static int32 pluginSpecMatStreamGetSizeCB();
    static CustomEnvMapPipeMaterialData* DuplicateCustomEnvMapPipeMaterialData(CustomEnvMapPipeMaterialData** arg0);
    static void* pluginEnvMatDestructorCB(void* object, int32 offset);
    static void* pluginEnvMatCopyConstructorCB(void* object_dst, const void* object_src, int32 offset, int32 size);
    static RwStream* pluginEnvMatStreamReadCB(RwStream* stream, int32 length, void* object, int32 offset);
    static void* pluginEnvAtmDestructorCB(void* object, int32 offset);
    static void* pluginEnvAtmCopyConstructorCB(void* object_dst, const void* object_src, int32 offset, int32 size);
    static void* pluginSpecMatDestructorCB(void* object);
    static void* pluginSpecMatCopyConstructorCB(void* object_dst, const void* object_src);
    static RwStream* pluginSpecMatStreamReadCB(RwStream* stream, int32 length, void* object);

    static int32 CustomPipeRenderCB(RwResEntry* atomic, void* object, uint8 flags1, uint32 flags2);
    static RxPipeline* CreateCustomOpenGLObjPipe();
    static bool CreatePipe();
    static void DestroyPipe();
    static void SetFxEnvTexture(RpMaterial* material, RwTexture* texture);
    static bool RegisterPlugin();
    static RpMaterial* CustomPipeMaterialSetup(RpMaterial* arg0, void* arg1);
    static RpAtomic* CustomPipeAtomicSetup(RpAtomic* atomic);
    static RpAtomic* CustomCarPipeAtomicSetupCB(RpAtomic* atomic, void* data);
};
