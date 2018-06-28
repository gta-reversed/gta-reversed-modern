/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPhysical.h"
#include "CObjectInfo.h"

enum eObjectType {
    OBJECT_MISSION = 2,
    OBJECT_TEMPORARY = 3,
    OBJECT_MISSION2 = 6
};

class CDummyObject;

class CObject : public CPhysical {
public:
    void           *m_pControlCodeList;
    unsigned char   m_nObjectType; // see enum eObjectType
    unsigned char   m_nBonusValue;
    unsigned short  m_wCostValue;
    struct {
        unsigned int b01 : 1;
        unsigned int b02 : 1;
        unsigned int bPickupPropertyForSale : 1;
        unsigned int bPickupInShopOutOfStock : 1;
        unsigned int bGlassBroken : 1;
        unsigned int b06 : 1;
        unsigned int bIsExploded : 1;
        unsigned int b08 : 1;

        unsigned int bIsLampPost : 1;
        unsigned int bIsTargatable : 1;
        unsigned int bIsBroken : 1;
        unsigned int bTrainCrossEnabled : 1;
        unsigned int bIsPhotographed : 1;
        unsigned int bIsLiftable : 1;
        unsigned int bIsDoorMoving : 1;
        unsigned int bbIsDoorOpen : 1;

        unsigned int bHasNoModel : 1;
        unsigned int bIsScaled : 1;
        unsigned int bCanBeAttachedToMagnet : 1;
        unsigned int b20 : 1;
        unsigned int b21 : 1;
        unsigned int b22 : 1;
        unsigned int bFadingIn : 1; // works only for objects with type 2 (OBJECT_MISSION)
        unsigned int bAffectedByColBrightness : 1;

        unsigned int b25 : 1;
        unsigned int bDoNotRender : 1;
        unsigned int bFadingIn2 : 1;
        unsigned int b28 : 1;
        unsigned int b29 : 1;
        unsigned int b30 : 1;
        unsigned int b31 : 1;
        unsigned int b32 : 1;
    } m_nObjectFlags;
    unsigned char   m_nColDamageEffect;
    unsigned char   m_nStoredColDamageEffect;
    char field_146;
    char            m_nGarageDoorGarageIndex;
    unsigned char   m_nLastWeaponDamage;
    unsigned char   m_nDayBrightness : 4;
    unsigned char   m_nNightBrightness : 4;
    short           m_nRefModelIndex;
    unsigned char   m_nCarColor[4]; // this is used for detached car parts
    int             m_dwRemovalTime; // time when this object must be deleted
    float           m_fHealth;
    float           m_fDoorStartAngle; // this is used for door objects
    float           m_fScale;
    CObjectInfo    *m_pObjectInfo;
    class CFire     *m_pFire; // CFire *
    short           m_wScriptTriggerIndex;
    short           m_wRemapTxd; // this is used for detached car parts
    RwTexture      *m_pRemapTexture; // this is used for detached car parts
    CDummyObject   *m_pDummyObject; // used for dynamic objects like garage doors, train crossings etc.
    int             m_dwBurnTime; // time when particles must be stopped
    float           m_fBurnDamage;

    // class functions

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
    unsigned char GetLightingFromCollisionBelow();
    void ProcessSamSiteBehaviour();
    void ProcessTrainCrossingBehaviour();
    void ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType);
    void Explode();
    void ObjectFireDamage(float damage, CEntity* damager);

    void GrabObjectToCarryWithRope(CPhysical* attachTo);
    bool CanBeUsedToTakeCoverBehind();
    static class CObject* Create(int modelIndex);
    static class CObject* Create(CDummyObject* dummyObject);
    void ProcessControlLogic();

    // static functions

    static void SetMatrixForTrainCrossing(CMatrix* matrix, float arg1);
    static void TryToFreeUpTempObjects(int numObjects);
    static void DeleteAllTempObjects();
    static void DeleteAllMissionObjects();
    static void DeleteAllTempObjectsInArea(CVector point, float radius);
};

VALIDATE_SIZE(CObject, 0x17C);

bool IsObjectPointerValid_NotInWorld(CObject* object);
bool IsObjectPointerValid(CObject* object);