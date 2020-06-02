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
   std::uint16_t m_id; // `m_id` is actually used for flags..
   std::uint16_t m_flags;
};
VALIDATE_SIZE(tAtomicVisibilityPlugin, 0x4);

struct tClumpVisibilityPlugin
{
    void* m_visibilityCallBack;
    std::int32_t m_alpha;
};
VALIDATE_SIZE(tClumpVisibilityPlugin, 0x8);

struct tFrameVisibilityPlugin
{
    union {
        std::int32_t m_hierarchyId;
        CClumpModelInfo* m_modelInfo;
    };
};
VALIDATE_SIZE(tFrameVisibilityPlugin, 0x4);

class CVisibilityPlugins
{
public:
    static const std::int32_t TOTAL_ALPHA_LISTS = 20;
    static const std::int32_t TOTAL_ALPHA_BOAT_ATOMIC_LISTS = 20;
    static const std::int32_t TOTAL_ALPHA_ENTITY_LISTS = 200;
    static const std::int32_t TOTAL_ALPHA_UNDERWATER_ENTITY_LISTS = 100;
    static const std::int32_t TOTAL_ALPHA_DRAW_LAST_LISTS = 50;
    static const std::int32_t TOTAL_WEAPON_PEDS_FOR_PC = 100;
    struct AlphaObjectInfo
    {
        union {
            RpAtomic* m_atomic;
            CEntity* m_entity;
        };
        void* m_pCallback;
        float m_distance; // alpha   
    };

    static std::int32_t& ms_atomicPluginOffset;
    static std::int32_t& ms_clumpPluginOffset;
    static std::int32_t& ms_framePluginOffset;
    static CLinkList<AlphaObjectInfo>& m_alphaEntityList;
    static CLinkList<AlphaObjectInfo>& m_alphaList;
    static CLinkList<AlphaObjectInfo>& m_alphaBoatAtomicList;
    static CLinkList<AlphaObjectInfo>& m_alphaUnderwaterEntityList;
    static CLinkList<AlphaObjectInfo>& m_alphaReallyDrawLastList;
    static CLinkList<CPed*>& ms_weaponPedsForPC;
    static RwCamera*& ms_pCamera;
    static RwV3d*& ms_pCameraPosn;
    static float& ms_cullCompsDist;
    static float& ms_cullBigCompsDist;
    static float& ms_vehicleLod0RenderMultiPassDist;
    static float& ms_vehicleLod0Dist;
    static float& ms_vehicleLod1Dist;
    static float& ms_bigVehicleLod0Dist;
    static float& ms_pedLodDist;
    static float& ms_pedFadeDist;

    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void InitAlphaAtomicList();
    static void InitAlphaEntityList();
    static bool InsertEntityIntoEntityList(CEntity* entity, float distance, void* callback);
    static bool InsertEntityIntoUnderwaterEntities(CEntity* entity, float distance);
    static bool InsertAtomicIntoReallyDrawLastList(RpAtomic* pRpAtomic, float distance);
    static bool InsertEntityIntoReallyDrawLastList(CEntity* pEntity, float distance);
    static bool InsertEntityIntoSortedList(CEntity* pEntity, float distance);
    static bool PluginAttach();
    static void* AtomicConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* AtomicCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* AtomicDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static int CalculateFadingAtomicAlpha(CBaseModelInfo* modelInfo, CEntity* entity, float distance);
    static void ClearAtomicFlag(RpAtomic* pRpAtomic, std::uint16_t flag);
    static RpAtomic* ClearAtomicFlag(RpAtomic* atomic, void* data);
    static void ClearClumpForAllAtomicsFlag(RpClump* pRpClump, std::uint16_t flag);
    static void* ClumpConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* ClumpCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* ClumpDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static int DefaultVisibilityCB(); // return 1;
    static void* FrameConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* FrameCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* FrameDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static bool FrustumSphereCB(RpClump* pRpClump);
    static std::uint16_t GetAtomicId(RpAtomic* pRpAtomic);
    static CAtomicModelInfo* GetAtomicModelInfo(RpAtomic* pRpAtomic);
    static int GetClumpAlpha(RpClump* pRpClump);
    static CClumpModelInfo* GetClumpModelInfo(RpClump* pRpClump);
    static float GetDistanceSquaredFromCamera(RwFrame* pRwFrame);
    static float GetDistanceSquaredFromCamera(RwV3d* pRwV3d);
    static float GetDotProductWithCameraVector(RwMatrixTag* atomicMat, RwMatrixTag* rootMat, unsigned int flags);
    static int GetFrameHierarchyId(RwFrame* pRwFrame);
    static short GetModelInfoIndex(RpAtomic* pRpAtomic);
    static short GetUserValue(RpAtomic* pRpAtomic);
    static bool IsAtomicVisible(RpAtomic* pRpAtomic);
    static bool IsClumpVisible(RpClump* pRpClump);
    static void RenderAlphaAtomic(RpAtomic* pRpAtomic, int dwAlpha);
    static void RenderAlphaAtomics();
    static void RenderAtomicWithAlphaCB(RpAtomic* pRpAtomic, void* pData);
    static void RenderBoatAlphaAtomics();
    static void RenderEntity(CEntity* entity, int unused, float distance);
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
    static void SetAtomicFlag(void* pRpAtomic, std::uint16_t flag);
    static void SetAtomicFlag(void* pRpAtomic, std::uint16_t flag);
    static void SetAtomicId(void* pRpAtomic, std::uint16_t id);
    static void SetAtomicRenderCallback(RpAtomic *pRpAtomic, RpAtomic * (*renderCB)(RpAtomic *));
    static void SetClumpAlpha(RpClump* pRpClump, int dwAlpha);
    static void SetClumpModelInfo(RpClump* pRpClump, CClumpModelInfo* pClumpModelInfo);
    static void SetFrameHierarchyId(RwFrame* pRwFrame, std::int32_t id);
    static void SetRenderWareCamera(RwCamera* pRwCamera);
    static void SetUserValue(RpAtomic* pRpAtomic, unsigned short value);
    static void SetupVehicleVariables(RpClump* pRpClump);
    static bool VehicleVisibilityCB(RpClump* pRpClump);
    static bool VehicleVisibilityCB_BigVehicle(RpClump* pRpClump);
};

#define RpAtomicGetVisibilityPlugin(atomic) ((tAtomicVisibilityPlugin *)((unsigned int)atomic + CVisibilityPlugins::ms_atomicPluginOffset))
