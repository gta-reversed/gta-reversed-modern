/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CEntity.h"
#include "CClumpModelInfo.h"
#include "CAtomicModelInfo.h"
#include "CLinkList.h"


struct tAtomicVisibilityPlugin
{
public:
	short          m_wModelId;
	unsigned short m_wFlags;
};

class  CVisibilityPlugins
{
public:
	static int& ms_atomicPluginOffset;

    struct AlphaObjectInfo
    {
        void *m_pAtomic;
        void *m_pCallback;
        float m_distance; // alpha   
    };

    static void AtomicConstructor(void* object);
    static void AtomicCopyConstructor(void* object, void const* originalObject);
    static void* AtomicDestructor(void* object);
    static int CalculateFadingAtomicAlpha(CBaseModelInfo* pBaseModelInfo, CEntity* pEntity, float arg3);
    static void ClearAtomicFlag(RpAtomic* pRpAtomic, int flag);
    static void ClearAtomicFlag(RpAtomic* pRpAtomic, unsigned short flag);
    static void ClearClumpForAllAtomicsFlag(RpClump* pRpClump, int flag);
    static void ClumpConstructor(void* object);
    static void ClumpCopyConstructor(void* object, void const* originalObject);
    static void* ClumpDestructor(void* object);
    static int DefaultVisibilityCB(); // return 1;
    static void FrameConstructor(void* object);
    static void FrameCopyConstructor(void* object, void const* originalObject);
    static void* FrameDestructor(void* arg0, int arg1, int arg2);
    static bool FrustumSphereCB(RpClump* pRpClump);
    static short GetAtomicId(RpAtomic* pRpAtomic);
    static CAtomicModelInfo* GetAtomicModelInfo(RpAtomic* pRpAtomic);
    static int GetClumpAlpha(RpClump* pRpClump);
    static CClumpModelInfo* GetClumpModelInfo(RpClump* pRpClump);
    static float GetDistanceSquaredFromCamera(RwFrame* pRwFrame);
    static float GetDistanceSquaredFromCamera(RwV3d* pRwV3d);
    static float GetDotProductWithCameraVector(RwMatrixTag* atomicMat, RwMatrixTag* rootMat, unsigned int flags);
    static int GetFrameHierarchyId(RwFrame* pRwFrame);
    static short GetModelInfoIndex(RpAtomic* pRpAtomic);
    static short GetUserValue(RpAtomic* pRpAtomic);
    static void InitAlphaAtomicList();
    static void InitAlphaEntityList();
    static void Initialise();
    static bool InsertAtomicIntoReallyDrawLastList(RpAtomic* pRpAtomic, float arg2);
    static bool InsertEntityIntoReallyDrawLastList(CEntity* pEntity, float arg2);
    static bool InsertEntityIntoSortedList(CEntity* pEntity, float distance);
    static bool IsAtomicVisible(RpAtomic* pRpAtomic);
    static bool IsClumpVisible(RpClump* pRpClump);
    static bool PluginAttach();
    static void RenderAlphaAtomic(RpAtomic* pRpAtomic, int dwAlpha);
    static void RenderAlphaAtomics();
    static void RenderAtomicWithAlphaCB(RpAtomic* pRpAtomic, void* pData);
    static void RenderBoatAlphaAtomics();
    static void RenderEntity(void* entity, bool unused, float arg3);
    static void RenderFadingAtomic(CBaseModelInfo* pBaseModelInfo, RpAtomic* pRpAtomic, int dwAlpha);
    static void RenderFadingClump(CBaseModelInfo* pBaseModelInfo, RpClump* pRpClump, int dwAlpha);
    static void RenderFadingClumpCB(RpAtomic* pRpAtomic);
    static void RenderFadingEntities();
    static void RenderFadingUnderwaterEntities();
    static void RenderHeliRotorAlphaCB(RpAtomic* pRpAtomic);
    static void RenderHeliTailRotorAlphaCB(RpAtomic* pRpAtomic);
    static void RenderObjNormalAtomic(RpAtomic* pRpAtomic);
    static void RenderOrderedList(CLinkList<CVisibilityPlugins::AlphaObjectInfo>& AlphaObjectInfoList);
    static void RenderPedCB(RpAtomic* pRpAtomic);
    static void RenderPlayerCB(RpAtomic* pRpAtomic);
    static void RenderReallyDrawLastObjects();
    static void RenderTrainHiDetailAlphaCB(RpAtomic* pRpAtomic);
    static void RenderTrainHiDetailCB(RpAtomic* pRpAtomic);
    static void RenderVehicleHiDetailAlphaCB(RpAtomic* pRpAtomic);
    static void RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic* pRpAtomic);
    static void RenderVehicleHiDetailAlphaCB_Boat(RpAtomic* pRpAtomic);
    static void RenderVehicleHiDetailCB(RpAtomic* pRpAtomic);
    static void RenderVehicleHiDetailCB_BigVehicle(RpAtomic* pRpAtomic);
    static void RenderVehicleHiDetailCB_Boat(RpAtomic* pRpAtomic);
    static void RenderVehicleLoDetailCB_Boat(RpAtomic* pRpAtomic);
    static void RenderVehicleReallyLowDetailCB(RpAtomic* pRpAtomic);
    static void RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic* pRpAtomic);
    static void RenderWeaponCB(RpAtomic* pRpAtomic);
    static void RenderWeaponPedsForPC();
    static void SetAtomicFlag(RpAtomic* pRpAtomic, int flag);
    static void SetAtomicFlag(RpAtomic* pRpAtomic, unsigned short flag);
    static void SetAtomicId(RpAtomic* pRpAtomic, int id);
    static void SetAtomicRenderCallback(RpAtomic *pRpAtomic, RpAtomic * (*renderCB)(RpAtomic *));
    static void SetClumpAlpha(RpClump* pRpClump, int dwAlpha);
    static void SetClumpModelInfo(RpClump* pRpClump, CClumpModelInfo* pClumpModelInfo);
    static void SetFrameHierarchyId(RwFrame* pRwFrame, int id);
    static void SetRenderWareCamera(RwCamera* pRwCamera);
    static void SetUserValue(RpAtomic* pRpAtomic, unsigned short value);
    static void SetupVehicleVariables(RpClump* pRpClump);
    static void Shutdown();
    static bool VehicleVisibilityCB(RpClump* pRpClump);
    static bool VehicleVisibilityCB_BigVehicle(RpClump* pRpClump);
};

#define RpAtomicGetVisibilityPlugin(atomic) ((tAtomicVisibilityPlugin *)((unsigned int)atomic + CVisibilityPlugins::ms_atomicPluginOffset))