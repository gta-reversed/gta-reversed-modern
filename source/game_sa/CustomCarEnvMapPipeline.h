/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
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

class CCustomCarEnvMapPipeline {
public:
    static int32 CustomPipeInstanceCB(int32 arg1, int32 arg2, int32(__cdecl* callback)(int32, int32, int32));
    static void PreRenderUpdate();
    static void* pluginEnvMatConstructorCB(void* object, int32 offset);
    static RwStream* pluginEnvMatStreamWriteCB(RwStream* stream, int32 length, void const* arg3, int32 arg4);
    static int32 pluginEnvMatStreamGetSizeCB(void const* arg0);
    static void* pluginEnvAtmConstructorCB(void* object, int32 offset);
    static void* pluginSpecMatConstructorCB(void* object);
    static RwStream* pluginSpecMatStreamWriteCB(RwStream* stream, int32 length, void const* object);
    static signed int pluginSpecMatStreamGetSizeCB();
    static CustomEnvMapPipeMaterialData* DuplicateCustomEnvMapPipeMaterialData(CustomEnvMapPipeMaterialData** arg0);
    static void* pluginEnvMatDestructorCB(void* object, int32 offset);
    static void* pluginEnvMatCopyConstructorCB(void* object_dst, void const* object_src, int32 offset, int32 size);
    static RwStream* pluginEnvMatStreamReadCB(RwStream* stream, int32 length, void* object, int32 offset);
    static void* pluginEnvAtmDestructorCB(void* object, int32 offset);
    static void* pluginEnvAtmCopyConstructorCB(void* object_dst, void const* object_src, int32 offset, int32 size);
    static void* pluginSpecMatDestructorCB(void* object);
    static void* pluginSpecMatCopyConstructorCB(void* object_dst, void const* object_src);
    static RwStream* pluginSpecMatStreamReadCB(RwStream* stream, int32 length, void* object);
    static int32 CustomPipeRenderCB(RwResEntry* atomic, void* object, uint8 flags1, uint32 flags2);
    static RxPipeline* CreateCustomOpenGLObjPipe();
    static char CreatePipe();
    static void DestroyPipe();
    static void SetFxEnvTexture(RpMaterial* material, RwTexture* texture);
    static char RegisterPlugin();
    static RpMaterial* CustomPipeMaterialSetup(RpMaterial* arg0, void* arg1);
    static RpAtomic* CustomPipeAtomicSetup(RpAtomic* arg0);
    static RpAtomic* CustomCarPipeAtomicSetupCB(RpAtomic* pAtomic, void* data);

    static int32& ms_envMapPluginOffset;
    static int32& ms_envMapAtmPluginOffset;
    static int32& ms_specularMapPluginOffset;
    static CustomEnvMapPipeMaterialData& fakeEnvMapPipeMatData;
    static RxPipeline*& ObjPipeline;
    static CPool<CustomEnvMapPipeMaterialData>*& m_gEnvMapPipeMatDataPool;
    static CPool<CustomEnvMapPipeAtomicData>*& m_gEnvMapPipeAtmDataPool;
    static CPool<CustomSpecMapPipeMaterialData>*& m_gSpecMapPipeMatDataPool;
};
