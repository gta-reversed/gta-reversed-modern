/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPhysical.h"
#include "CObjectData.h"

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

class CObject : public CPhysical {
public:
    CObject();
    CObject(int modelId, bool bCreate);
    CObject(CDummyObject* pDummyObj);
    ~CObject();
    static void* operator new(unsigned int size);
    static void* operator new(unsigned int size, int iPoolRef);
    static void operator delete(void* pObj);
public:
    CPtrNodeDoubleLink *m_pControlCodeList;
    unsigned char       m_nObjectType; // see enum eObjectType
    unsigned char       m_nBonusValue;
    unsigned short      m_wCostValue;
    union {
        struct 
        {
            unsigned int bIsPickup : 1;
            unsigned int b0x02 : 1;
            unsigned int bPickupPropertyForSale : 1;
            unsigned int bPickupInShopOutOfStock : 1;
            unsigned int bGlassBroken : 1;
            unsigned int b0x20 : 1;
            unsigned int bIsExploded : 1;
            unsigned int bChangesVehColor : 1;

            unsigned int bIsLampPost : 1;
            unsigned int bIsTargatable : 1;
            unsigned int bIsBroken : 1;
            unsigned int bTrainCrossEnabled : 1;
            unsigned int bIsPhotographed : 1;
            unsigned int bIsLiftable : 1;
            unsigned int bIsDoorMoving : 1;
            unsigned int bIsDoorOpen : 1;

            unsigned int bHasNoModel : 1;
            unsigned int bIsScaled : 1;
            unsigned int bCanBeAttachedToMagnet : 1;
            unsigned int bDamaged : 1;
            unsigned int b0x100000 : 1;
            unsigned int b0x200000 : 1;
            unsigned int bFadingIn : 1; // works only for objects with type 2 (OBJECT_MISSION)
            unsigned int bAffectedByColBrightness : 1;

            unsigned int b0x01000000 : 1;
            unsigned int bDoNotRender : 1;
            unsigned int bFadingIn2 : 1;
            unsigned int b0x08000000 : 1;
            unsigned int b0x10000000 : 1;
            unsigned int b0x20000000 : 1;
            unsigned int b0x40000000 : 1;
            unsigned int b0x80000000 : 1;
        } objectFlags;
        unsigned int m_nObjectFlags;
    };
    unsigned char   m_nColDamageEffect; // see eObjectColDamageEffect
    unsigned char   m_nSpecialColResponseCase; // see eObjectSpecialColResponseCases
    char field_146;
    char            m_nGarageDoorGarageIndex;
    unsigned char   m_nLastWeaponDamage;
    tColLighting    m_nColLighting;
    short           m_nRefModelIndex;
    unsigned char   m_nCarColor[4]; // this is used for detached car parts
    int             m_dwRemovalTime; // time when this object must be deleted
    float           m_fHealth;
    float           m_fDoorStartAngle; // this is used for door objects
    float           m_fScale;
    CObjectData    *m_pObjectInfo;
    class CFire     *m_pFire; // CFire *
    short           m_wScriptTriggerIndex;
    short           m_wRemapTxd; // this is used for detached car parts
    RwTexture      *m_pRemapTexture; // this is used for detached car parts
    CDummyObject   *m_pDummyObject; // used for dynamic objects like garage doors, train crossings etc.
    int             m_dwBurnTime; // time when particles must be stopped
    float           m_fBurnDamage;


    static unsigned short& nNoTempObjects;
    static float& fDistToNearestTree;
    static bool& bAircraftCarrierSamSiteDisabled;
    static bool& bArea51SamSiteDisabled;

public:
    static void InjectHooks();

    //Virtual
    void SetIsStatic(bool isStatic) override;
    void CreateRwObject() override;
    void ProcessControl() override;
    void Teleport(CVector destination, bool resetRotation) override;
    void SpecialEntityPreCollisionStuff(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled, bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck) override;
    unsigned char SpecialEntityCalcCollisionSteps(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2) override;
    void PreRender() override;
    void Render() override;
    bool SetupLighting() override;
    void RemoveLighting(bool bRemove) override;

private:
    // Virtual implementations
    void SetIsStatic_Reversed(bool isStatic);
    void CreateRwObject_Reversed();
    void ProcessControl_Reversed();
    void Teleport_Reversed(CVector destination, bool resetRotation);
    void SpecialEntityPreCollisionStuff_Reversed(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled, bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck);
    unsigned char SpecialEntityCalcCollisionSteps_Reversed(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2);
    void PreRender_Reversed();
    void Render_Reversed();
    bool SetupLighting_Reversed();
    void RemoveLighting_Reversed(bool bRemove);

public:
    bool Load();
    bool Save();

    void ProcessGarageDoorBehaviour();
    bool CanBeDeleted();
    void SetRelatedDummy(CDummyObject* relatedDummy);
    bool TryToExplode();
    void SetObjectTargettable(unsigned char targetable);
    bool CanBeTargetted();
    void RefModelInfo(int modelIndex);
    void SetRemapTexture(RwTexture* remapTexture, short txdIndex);
    float GetRopeHeight();
    void SetRopeHeight(float height);
    CEntity* GetObjectCarriedWithRope();
    void ReleaseObjectCarriedWithRope();
    void AddToControlCodeList();
    void RemoveFromControlCodeList();
    void ResetDoorAngle();
    void LockDoor();
    void Init();
    void DoBurnEffect();
    void GetLightingFromCollisionBelow();
    void ProcessSamSiteBehaviour();
    void ProcessTrainCrossingBehaviour();
    void ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType);
    void Explode();
    void ObjectFireDamage(float damage, CEntity* damager);

    void GrabObjectToCarryWithRope(CPhysical* attachTo);
    bool CanBeUsedToTakeCoverBehind();
    void ProcessControlLogic();    

// Static
public:
    static class CObject* Create(int modelIndex, bool bUnused);
    static class CObject* Create(CDummyObject* dummyObject);

    static void SetMatrixForTrainCrossing(CMatrix* matrix, float fAngle);
    static void TryToFreeUpTempObjects(int numObjects);
    static void DeleteAllTempObjects();
    static void DeleteAllMissionObjects();
    static void DeleteAllTempObjectsInArea(CVector point, float radius);

    //Helpers
    inline bool IsTemporary() const { return m_nObjectType == eObjectType::OBJECT_TEMPORARY; }
    inline bool IsMissionObject() const { return m_nObjectType == eObjectType::OBJECT_MISSION || m_nObjectType == eObjectType::OBJECT_MISSION2; }
    inline bool IsCraneMovingPart() const
    {
        return m_nModelIndex == ModelIndices::MI_CRANE_MAGNET
            || m_nModelIndex == ModelIndices::MI_CRANE_HARNESS
            || m_nModelIndex == ModelIndices::MI_MINI_MAGNET
            || m_nModelIndex == ModelIndices::MI_WRECKING_BALL;
    }
    inline bool IsFallenLampPost() const { return objectFlags.bIsLampPost && m_matrix->GetUp().z < 0.66F; }
    inline bool IsExploded() const { return objectFlags.bIsExploded; }
    inline bool CanBeSmashed() const { return m_nColDamageEffect >= eObjectColDamageEffect::COL_DAMAGE_EFFECT_SMASH_COMPLETELY; }
};
VALIDATE_SIZE(CObject, 0x17C);

bool IsObjectPointerValid_NotInWorld(CObject* object);
bool IsObjectPointerValid(CObject* object);
