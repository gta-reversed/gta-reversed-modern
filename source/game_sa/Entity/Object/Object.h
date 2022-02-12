/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Physical.h"
#include "ObjectData.h"

enum eObjectType {
    OBJECT_UNKNOWN = 0,
    OBJECT_GAME = 1,
    OBJECT_MISSION = 2,
    OBJECT_TEMPORARY = 3,
    OBJECT_TYPE_CUTSCENE = 4,
    OBJECT_TYPE_DECORATION = 5, // Hand object, projectiles, escalator step, water creatures, no clue what this enum value should be called
    OBJECT_MISSION2 = 6
};

class CDummyObject;
class CFire;

class CObject : public CPhysical {
public:
    CObject();
    CObject(int32 modelId, bool bCreate);
    CObject(CDummyObject* pDummyObj);
    ~CObject() override;

    static void* operator new(uint32 size);
    static void* operator new(uint32 size, int32 iPoolRef);
    static void  operator delete(void* obj);

public:
    CPtrNodeDoubleLink* m_pControlCodeList;
    uint8               m_nObjectType; // see enum eObjectType
    uint8               m_nBonusValue;
    uint16              m_wCostValue;
    union {
        struct {
            uint32 bIsPickup : 1;               // 0x1
            uint32 b0x02 : 1;                   // 0x2
            uint32 bPickupPropertyForSale : 1;  // 0x4
            uint32 bPickupInShopOutOfStock : 1; // 0x8
            uint32 bGlassBroken : 1;            // 0x10
            uint32 b0x20 : 1;                   // 0x20
            uint32 bIsExploded : 1;             // 0x40
            uint32 bChangesVehColor : 1;        // 0x80

            uint32 bIsLampPost : 1;
            uint32 bIsTargatable : 1;
            uint32 bIsBroken : 1;
            uint32 bTrainCrossEnabled : 1;
            uint32 bIsPhotographed : 1;
            uint32 bIsLiftable : 1;
            uint32 bIsDoorMoving : 1;
            uint32 bIsDoorOpen : 1;

            uint32 bHasNoModel : 1;
            uint32 bIsScaled : 1;
            uint32 bCanBeAttachedToMagnet : 1;
            uint32 bDamaged : 1;
            uint32 b0x100000 : 1;
            uint32 b0x200000 : 1;
            uint32 bFadingIn : 1; // works only for objects with type 2 (OBJECT_MISSION)
            uint32 bAffectedByColBrightness : 1;

            uint32 b0x01000000 : 1;
            uint32 bDoNotRender : 1;
            uint32 bFadingIn2 : 1;
            uint32 b0x08000000 : 1;
            uint32 b0x10000000 : 1;
            uint32 b0x20000000 : 1;
            uint32 b0x40000000 : 1;
            uint32 b0x80000000 : 1;
        } objectFlags;
        uint32 m_nObjectFlags;
    };
    uint8         m_nColDamageEffect;        // see eObjectColDamageEffect
    uint8         m_nSpecialColResponseCase; // see eObjectSpecialColResponseCases
    char          field_146;
    char          m_nGarageDoorGarageIndex;
    uint8         m_nLastWeaponDamage;
    tColLighting  m_nColLighting;
    int16         m_nRefModelIndex;
    uint8         m_nCarColor[4];  // this is used for detached car parts
    int32         m_dwRemovalTime; // time when this object must be deleted
    float         m_fHealth;
    float         m_fDoorStartAngle; // this is used for door objects
    float         m_fScale;
    CObjectData*  m_pObjectInfo;
    CFire*        m_pFire; // CFire *
    int16         m_wScriptTriggerIndex;
    int16         m_wRemapTxd;     // this is used for detached car parts
    RwTexture*    m_pRemapTexture; // this is used for detached car parts
    CDummyObject* m_pDummyObject;  // used for dynamic objects like garage doors, train crossings etc.
    uint32        m_nBurnTime;     // time when particles must be stopped
    float         m_fBurnDamage;

    static uint16& nNoTempObjects;
    static float&  fDistToNearestTree;
    static bool&   bAircraftCarrierSamSiteDisabled;
    static bool&   bArea51SamSiteDisabled;

public:
    static void InjectHooks();

    // Virtual
    void  SetIsStatic(bool isStatic) override;
    void  CreateRwObject() override;
    void  ProcessControl() override;
    void  Teleport(CVector destination, bool resetRotation) override;
    void  SpecialEntityPreCollisionStuff(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled, bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck) override;
    uint8 SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2) override;
    void  PreRender() override;
    void  Render() override;
    bool  SetupLighting() override;
    void  RemoveLighting(bool bRemove) override;

private:
    // Virtual implementations
    void  SetIsStatic_Reversed(bool isStatic);
    void  CreateRwObject_Reversed();
    void  ProcessControl_Reversed();
    void  Teleport_Reversed(CVector destination, bool resetRotation);
    void  SpecialEntityPreCollisionStuff_Reversed(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled, bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck);
    uint8 SpecialEntityCalcCollisionSteps_Reversed(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2);
    void  PreRender_Reversed();
    void  Render_Reversed();
    bool  SetupLighting_Reversed();
    void  RemoveLighting_Reversed(bool bRemove);

public:
    bool Load();
    bool Save();

    void     ProcessGarageDoorBehaviour();
    bool     CanBeDeleted();
    void     SetRelatedDummy(CDummyObject* relatedDummy);
    bool     TryToExplode();
    void     SetObjectTargettable(bool targetable);
    bool     CanBeTargetted();
    void     RefModelInfo(int32 modelIndex);
    void     SetRemapTexture(RwTexture* remapTexture, int16 txdIndex);
    float    GetRopeHeight();
    void     SetRopeHeight(float height);
    CEntity* GetObjectCarriedWithRope();
    void     ReleaseObjectCarriedWithRope();
    void     AddToControlCodeList();
    void     RemoveFromControlCodeList();
    void     ResetDoorAngle();
    void     LockDoor();
    void     Init();
    void     DoBurnEffect();
    void     GetLightingFromCollisionBelow();
    void     ProcessSamSiteBehaviour();
    void     ProcessTrainCrossingBehaviour();
    void     ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType);
    void     Explode();
    void     ObjectFireDamage(float damage, CEntity* damager);

    void GrabObjectToCarryWithRope(CPhysical* attachTo);
    bool CanBeUsedToTakeCoverBehind();
    void ProcessControlLogic();

    // Static
public:
    static class CObject* Create(int32 modelIndex, bool bUnused);
    static class CObject* Create(CDummyObject* dummyObject);

    static void SetMatrixForTrainCrossing(CMatrix* matrix, float fAngle);
    static void TryToFreeUpTempObjects(int32 numObjects);
    static void DeleteAllTempObjects();
    static void DeleteAllMissionObjects();
    static void DeleteAllTempObjectsInArea(CVector point, float radius);

    // Helpers
    inline bool IsTemporary() const { return m_nObjectType == eObjectType::OBJECT_TEMPORARY; }
    inline bool IsMissionObject() const { return m_nObjectType == eObjectType::OBJECT_MISSION || m_nObjectType == eObjectType::OBJECT_MISSION2; }
    inline bool IsCraneMovingPart() const {
        return m_nModelIndex == ModelIndices::MI_CRANE_MAGNET
            || m_nModelIndex == ModelIndices::MI_CRANE_HARNESS
            || m_nModelIndex == ModelIndices::MI_MINI_MAGNET
            || m_nModelIndex == ModelIndices::MI_WRECKING_BALL;
    }
    inline bool IsFallenLampPost() const { return objectFlags.bIsLampPost && m_matrix->GetUp().z < 0.66F; }
    inline bool IsExploded() const { return objectFlags.bIsExploded; }
    inline bool CanBeSmashed() const { return m_nColDamageEffect >= COL_DAMAGE_EFFECT_SMASH_COMPLETELY; }
};
VALIDATE_SIZE(CObject, 0x17C);

bool IsObjectPointerValid_NotInWorld(CObject* object);
bool IsObjectPointerValid(CObject* object);
