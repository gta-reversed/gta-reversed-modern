/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CPool.h"
#include "CObject.h"

struct CustomEnvMapPipeMaterialData
{
public:
	char scaleX;
	char scaleY;
	char transSclX;
	char transSclY;
	char shininess;
	short renderFrameCounter;
	void *texture;
};
VALIDATE_SIZE(CustomEnvMapPipeMaterialData, 0xC);

struct CustomEnvMapPipeAtomicData
{
	float lastTrans;
	float posx;
	float posy;
};
VALIDATE_SIZE(CustomEnvMapPipeAtomicData, 0xC);

struct CustomSpecMapPipeMaterialData
{
	float specularity;
	void *texture;
};
VALIDATE_SIZE(CustomSpecMapPipeMaterialData, 0x8);

class  CCustomCarEnvMapPipeline {
public:

	static int CustomPipeInstanceCB(int arg1, int arg2, int(__cdecl *callback)(int, int, int));
	static void PreRenderUpdate();
	static void* pluginEnvMatConstructorCB(void* object, int offset);
	static RwStream* pluginEnvMatStreamWriteCB(RwStream* stream, int length, void const* arg3, int arg4);
	static int pluginEnvMatStreamGetSizeCB(void const* arg0);
	static void* pluginEnvAtmConstructorCB(void* object, int offset);
	static void* pluginSpecMatConstructorCB(void* object);
	static RwStream* pluginSpecMatStreamWriteCB(RwStream* stream, int length, void const* object);
	static signed int pluginSpecMatStreamGetSizeCB();
	static CustomEnvMapPipeMaterialData* DuplicateCustomEnvMapPipeMaterialData(CustomEnvMapPipeMaterialData** arg0);
	static void* pluginEnvMatDestructorCB(void* object, int offset);
	static void* pluginEnvMatCopyConstructorCB(void* object_dst, void const* object_src, int offset, int size);
	static RwStream* pluginEnvMatStreamReadCB(RwStream* stream, int length, void* object, int offset);
	static void* pluginEnvAtmDestructorCB(void* object, int offset);
	static void* pluginEnvAtmCopyConstructorCB(void* object_dst, void const* object_src, int offset, int size);
	static void* pluginSpecMatDestructorCB(void* object);
	static void* pluginSpecMatCopyConstructorCB(void* object_dst, void const* object_src);
	static RwStream* pluginSpecMatStreamReadCB(RwStream* stream, int length, void* object);
	static int CustomPipeRenderCB(RwResEntry* atomic, void* object, unsigned char flags1, unsigned int flags2);
	static RxPipeline* CreateCustomOpenGLObjPipe();
	static char CreatePipe();
	static void DestroyPipe();
	static void SetFxEnvTexture(RpMaterial* material, RwTexture* texture);
	static char RegisterPlugin();
	static RpMaterial* CustomPipeMaterialSetup(RpMaterial* arg0, void* arg1);
	static RpAtomic* CustomPipeAtomicSetup(RpAtomic* arg0);


	static int& ms_envMapPluginOffset;
	static int& ms_envMapAtmPluginOffset;
	static int& ms_specularMapPluginOffset;
	static CustomEnvMapPipeMaterialData& fakeEnvMapPipeMatData;
	static RxPipeline*& ObjPipeline;
	static CPool<CustomEnvMapPipeMaterialData> *&m_gEnvMapPipeMatDataPool;
	static CPool<CustomEnvMapPipeAtomicData> *&m_gEnvMapPipeAtmDataPool;
	static CPool<CustomSpecMapPipeMaterialData> *&m_gSpecMapPipeMatDataPool;
    

};