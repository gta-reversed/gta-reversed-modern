/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Entity.h"
#include "ClumpModelInfo.h"
#include "AtomicModelInfo.h"
#include "LinkList.h"

enum eAtomicComponentFlag {
    ATOMIC_IS_OK_STATE = 0x1,
    ATOMIC_IS_DAM_STATE = 0x2,
    ATOMIC_IS_LEFT = 0x4,
    ATOMIC_IS_RIGHT = 0x8,
    ATOMIC_IS_FRONT = 0x10,
    ATOMIC_IS_REAR = 0x20,
    ATOMIC_HAS_ALPHA = 0x40,
    ATOMIC_CULL = 0x80,
    ATOMIC_IS_REAR_DOOR = 0x100,
    ATOMIC_IS_FRONT_DOOR = 0x200,
    ATOMIC_RENDER_ALWAYS = 0x400, // enabled for opened components (doors)
    ATOMIC_IS_REPLACEMENT_UPGRADE = 0x800,
    ATOMIC_IS_DOOR_WINDOW_OPENED = 0x1000,
    ATOMIC_DISABLE_REFLECTIONS = 0x2000,
    // ATOMIC_HAS_DYNAMIC_TEXTURES  = 0x2000, // TODO: WTF is this?
    ATOMIC_IS_BLOWN_UP = 0x4000,
    ATOMIC_VEHCOMP_15 = 0x8000
};

struct tAtomicVisibilityPlugin {
    int16 m_modelId;
    union {
        uint16 m_flags; // eAtomicComponentFlag
        int16 m_userValue;
    };
};
VALIDATE_SIZE(tAtomicVisibilityPlugin, 0x4);

struct tClumpVisibilityPlugin {
    void* m_visibilityCallBack;
    int32 m_alpha;
};
VALIDATE_SIZE(tClumpVisibilityPlugin, 0x8);

struct tFrameVisibilityPlugin {
    union {
        int32 m_hierarchyId;
        CClumpModelInfo* m_modelInfo;
    };
};
VALIDATE_SIZE(tFrameVisibilityPlugin, 0x4);

class CVisibilityPlugins {
public:
    static const int32 TOTAL_ALPHA_LISTS = 20;
    static const int32 TOTAL_ALPHA_BOAT_ATOMIC_LISTS = 20;
    static const int32 TOTAL_ALPHA_ENTITY_LISTS = 200;
    static const int32 TOTAL_ALPHA_UNDERWATER_ENTITY_LISTS = 100;
    static const int32 TOTAL_ALPHA_DRAW_LAST_LISTS = 50;
    static const int32 TOTAL_WEAPON_PEDS_FOR_PC = 100;
    using tAlphaRenderOrderedListCB = void(__cdecl*)(CEntity* entity, float distance);
    struct AlphaObjectInfo {
        union {
            RpAtomic* m_atomic;
            CEntity* m_entity;
        };
        void* m_pCallback;
        float m_distance; // alpha
    };

    static int32& ms_atomicPluginOffset;
    static int32& ms_clumpPluginOffset;
    static int32& ms_framePluginOffset;
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
    static float& gVehicleDistanceFromCamera;
    static float& gVehicleAngleToCamera;

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
    static RpAtomic* DefaultAtomicRenderCallback(RpAtomic* atomic);
    static void* AtomicConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* AtomicCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* AtomicDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static int32 CalculateFadingAtomicAlpha(CBaseModelInfo* modelInfo, CEntity* entity, float distance);
    static void ClearAtomicFlag(RpAtomic* pRpAtomic, uint16 flag);
    static RpAtomic* ClearAtomicFlagCB(RpAtomic* atomic, void* data);
    static void ClearClumpForAllAtomicsFlag(RpClump* pRpClump, uint16 flag);
    static void* ClumpConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* ClumpCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* ClumpDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static int32 DefaultVisibilityCB(); // return 1;
    static void* FrameConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* FrameCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static void* FrameDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
    static bool FrustumSphereCB(RpClump* pRpClump);
    static uint16 GetAtomicId(RpAtomic* pRpAtomic);
    static CAtomicModelInfo* GetAtomicModelInfo(RpAtomic* pRpAtomic);
    static int32 GetClumpAlpha(RpClump* pRpClump);
    static CClumpModelInfo* GetClumpModelInfo(RpClump* pRpClump);
    static float GetDistanceSquaredFromCamera(RwFrame* pRwFrame);
    static float GetDistanceSquaredFromCamera(CVector* pPos);
    static float GetDotProductWithCameraVector(RwMatrixTag* atomicMatrix, RwMatrixTag* clumpMatrix, uint16 flags);
    static int32 GetFrameHierarchyId(RwFrame* pRwFrame);
    static int16 GetModelInfoIndex(RpAtomic* pRpAtomic);
    static int16 GetUserValue(RpAtomic* pRpAtomic);
    static bool IsAtomicVisible(RpAtomic* pRpAtomic);
    static bool IsClumpVisible(RpClump* pRpClump);
    static void RenderAlphaAtomic(RpAtomic* atomic, int32 alpha);
    static void RenderAlphaAtomics();
    static RpAtomic* RenderAtomicWithAlphaCB(RpAtomic* pRpAtomic, void* pData);
    static void RenderBoatAlphaAtomics();
    static void RenderEntity(CEntity* entity, int32 unused, float distance);
    static void RenderFadingAtomic(CBaseModelInfo* modelInfo, RpAtomic* atomic, int32 alpha);
    static void RenderFadingClump(CBaseModelInfo* modelInfo, RpClump* clump, int32 alpha);
    static RpAtomic* RenderFadingClumpCB(RpAtomic* pRpAtomic);
    static void RenderFadingEntities();
    static void RenderFadingUnderwaterEntities();
    static RpAtomic* RenderHeliRotorAlphaCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderHeliTailRotorAlphaCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderObjNormalAtomic(RpAtomic* pRpAtomic);
    static void RenderOrderedList(CLinkList<CVisibilityPlugins::AlphaObjectInfo>& AlphaObjectInfoList);
    static RpAtomic* RenderPedCB(RpAtomic* pRpAtomic);
    static RpMaterial* SetTextureCB(RpMaterial* material, void* texture);
    static RpAtomic* RenderPlayerCB(RpAtomic* pRpAtomic);
    static void RenderReallyDrawLastObjects();
    static RpAtomic* RenderTrainHiDetailAlphaCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderTrainHiDetailCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleHiDetailAlphaCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleHiDetailAlphaCB_Boat(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleHiDetailCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleHiDetailCB_BigVehicle(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleHiDetailCB_Boat(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleLoDetailCB_Boat(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleReallyLowDetailCB(RpAtomic* pRpAtomic);
    static RpAtomic* RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic* pRpAtomic);
    static RpAtomic* RenderWeaponCB(RpAtomic* pRpAtomic);
    static void RenderWeaponPedsForPC();
    static RpAtomic* SetAtomicFlagCB(RpAtomic* pRpAtomic, void* data);
    static void SetAtomicFlag(RpAtomic* pRpAtomic, uint16 flag);
    static void SetClumpForAllAtomicsFlag(RpClump* pRpClump, uint16 flag);
    static void SetAtomicId(void* pRpAtomic, int16 id);
    static void SetAtomicRenderCallback(RpAtomic* pRpAtomic, RpAtomicCallBackRender renderCB);
    static void SetClumpAlpha(RpClump* pRpClump, int32 dwAlpha);
    static void SetClumpModelInfo(RpClump* pRpClump, CClumpModelInfo* pClumpModelInfo);
    static void SetFrameHierarchyId(RwFrame* pRwFrame, int32 id);
    static void SetRenderWareCamera(RwCamera* pRwCamera);
    static void SetUserValue(RpAtomic* pRpAtomic, uint16 value);
    static void SetupVehicleVariables(RpClump* pRpClump);
    static bool VehicleVisibilityCB(RpClump* pRpClump);
    static bool VehicleVisibilityCB_BigVehicle(RpClump* pRpClump);
};

#define RpAtomicGetVisibilityPlugin(atomic) ((tAtomicVisibilityPlugin*)((uint32)atomic + CVisibilityPlugins::ms_atomicPluginOffset))
