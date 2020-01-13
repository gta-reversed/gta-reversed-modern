/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CEntity.h"
#include "CColPoint.h"
#include "CVector.h"
#include "CQuaternion.h"
#include "CRealTimeShadow.h"
#include "CRepeatSector.h"
#include "eWeaponType.h"

enum ePhysicalFlags
{
    PHYSICAL_b01 = 0x1,
    PHYSICAL_APPLY_GRAVITY = 0x2,
    PHYSICAL_DISABLE_COLLISION_FORCE = 0x4,
    PHYSICAL_COLLIDABLE = 0x8, 
    PHYSICAL_DISABLE_TURN_FORCE = 0x10,
    PHYSICAL_DISABLE_MOVE_FORCE = 0x20,
    PHYSICAL_INFINITE_MASS = 0x40,
    PHYSICAL_DISABLE_Z = 0x80,

    PHYSICAL_SUBMERGED_IN_WATER = 0x100,
    PHYSICAL_ON_SOLID_SURFACE = 0x200,
    PHYSICAL_BROKEN = 0x400,
    PHYSICAL_b12 = 0x800,
    PHYSICAL_b13 = 0x1000,
    PHYSICAL_DONT_APPLY_SPEED = 0x2000,
    PHYSICAL_b15 = 0x4000,
    PHYSICAL_b16 = 0x8000
};

class CPhysical : public CEntity {
protected:
    CPhysical(plugin::dummy_func_t) : CEntity(plugin::dummy) {}
public:
    int field_38;
    unsigned int m_nLastCollisionTime;
    union
    {
        struct 
        {
            unsigned int b01 : 1;
            unsigned int bApplyGravity : 1;
            unsigned int bDisableCollisionForce : 1;
            unsigned int bCollidable : 1;
            unsigned int bDisableTurnForce : 1;
            unsigned int bDisableMoveForce : 1;
            unsigned int bInfiniteMass : 1;
            unsigned int bDisableZ : 1;

            unsigned int bSubmergedInWater : 1;
            unsigned int bOnSolidSurface : 1;
            unsigned int bBroken : 1;
            unsigned int b12 : 1; // ref @ 0x6F5CF0
            unsigned int b13 : 1;
            unsigned int bDontApplySpeed : 1;
            unsigned int b15 : 1;
            unsigned int b16 : 1;

            unsigned int b17 : 1;
            unsigned int b18 : 1; // ref @ CPhysical::ProcessCollision
            unsigned int bBulletProof : 1;
            unsigned int bFireProof : 1;
            unsigned int bCollisionProof : 1;
            unsigned int bMeeleProof : 1;
            unsigned int bInvulnerable : 1;
            unsigned int bExplosionProof : 1;

            unsigned int b25 : 1;
            unsigned int bAttachedToEntity : 1;
            unsigned int b27 : 1;
            unsigned int bTouchingWater : 1;
            unsigned int bCanBeCollidedWith : 1;
            unsigned int bDestroyed : 1;
            unsigned int b31 : 1;
            unsigned int b32 : 1;
        } physicalFlags;
        unsigned int m_nPhysicalFlags;
    };
    CVector          m_vecMoveSpeed;
    CVector          m_vecTurnSpeed;
    CVector          m_vecFrictionMoveSpeed;
    CVector          m_vecFrictionTurnSpeed;
    CVector          m_vecForce;
    CVector          m_vecTorque;
    float            m_fMass;
    float            m_fTurnMass;
    float            m_fVelocityFrequency;
    float            m_fAirResistance;
    float            m_fElasticity;
    float            m_fBuoyancyConstant;
    CVector          m_vecCentreOfMass;
    void            *m_pCollisionList;
    void            *m_pMovingList;
    unsigned char    m_bFakePhysics;
    unsigned char    m_nNumEntitiesCollided;
    unsigned char    m_nContactSurface;
    char field_BB;
    CEntity         *m_apCollidedEntities[6];
    float            m_fMovingSpeed; // ref @ CTheScripts::IsVehicleStopped
    float            m_fDamageIntensity;
    CEntity         *m_pDamageEntity;
    CVector          m_vecLastCollisionImpactVelocity;
    CVector          m_vecLastCollisionPosn;
    unsigned short   m_nPieceType;
    short field_FA;
    class CPhysical *m_pAttachedTo;
    CVector          m_vecAttachOffset;
    CVector          m_vecAttachedEntityPosn;
    CQuaternion      m_qAttachedEntityRotation;
    CEntity         *m_pEntityIgnoredCollision;
    float            m_fContactSurfaceBrightness;
    float            m_fDynamicLighting;
    CRealTimeShadow *m_pShadowData;
    
    static float& PHYSICAL_SHIFT_SPEED_DAMP;
    static CVector& fxDirection;

    static void InjectHooks();

    // originally virtual functions
    CRect* GetBoundRect(CRect* pRect) override;
    void ProcessControl() override;
    void ProcessShift() override;
    virtual int ProcessEntityCollision(CEntity *entity, CColPoint *point);

    // reversed virtual functions
    void ProcessShift_Reversed();

    // functions
    void RemoveAndAdd();
    void AddToMovingList();
    void RemoveFromMovingList();
    void SetDamagedPieceRecord(float damageIntensity, CEntity* damagingEntity, CColPoint* colPoint, float distanceMult);
    void ApplyMoveForce(float x, float y, float z);
    void ApplyMoveForce(CVector force);
    void ApplyTurnForce(CVector dir, CVector velocity);
    void ApplyForce(CVector dir, CVector velocity, bool flag);
    CVector GetSpeed(CVector direction);
    void ApplyMoveSpeed();
    void ApplyTurnSpeed();
    void ApplyGravity();
    void ApplyFrictionMoveForce(CVector moveForce);
    void ApplyFrictionTurnForce(CVector posn, CVector velocity);
    void ApplyFrictionForce(CVector posn, CVector velocity);
    void SkipPhysics();
    void AddCollisionRecord(CEntity* collidedEntity);
    bool GetHasCollidedWith(CEntity* entity);
    bool GetHasCollidedWithAnyObject();
    bool ApplyCollision(CEntity* entity, CColPoint& colPoint, float& fDamageIntensity);
    bool ApplySoftCollision(CEntity* entity, CColPoint* colPoint, float* fDamageIntensity);
    bool ApplySpringCollision(float arg0, CVector& arg1, CVector& arg2, float arg3, float arg4, float& arg5);
    bool ApplySpringCollisionAlt(float arg0, CVector& arg1, CVector& arg2, float arg3, float arg4, CVector& arg5, float& arg6);
    bool ApplySpringDampening(float arg0, float arg1, CVector& arg2, CVector& arg3, CVector& arg4);
    bool ApplySpringDampeningOld(float arg0, float arg1, CVector& arg2, CVector& arg3, CVector& arg4);
    void RemoveRefsToEntity(CEntity* entity);
    void DettachEntityFromEntity(float x, float y, float z, bool useCollision);
    void DettachAutoAttachedEntity();
    float GetLightingFromCol(bool flag);
    float GetLightingTotal();
    bool CanPhysicalBeDamaged(eWeaponType weapon, unsigned char* arg1);
    void ApplyAirResistance();
    bool ApplyCollisionAlt(CEntity* entity, CColPoint& colPoint, float& fDamageIntensity, CVector& vecMoveSpeed, CVector& vecTurnSpeed);
    bool ApplyFriction(float fFriction, CColPoint* colPoint);
    bool ApplyFriction(CPhysical* physical, float fFriction, CColPoint* colPoint);
    bool ProcessShiftSectorList(int sectorX, int sectorY);
    static void PlacePhysicalRelativeToOtherPhysical(CPhysical* physical1, CPhysical* physical2, CVector offset);
    float ApplyScriptCollision(CVector arg0, float arg1, float arg2, CVector* arg3);
    void PositionAttachedEntity();
    void ApplySpeed();
    void UnsetIsInSafePosition();
    void ApplyFriction();
    bool ApplyCollision(CEntity* pEntity, CColPoint* pColPoint, float* pThisDamageIntensity, float* pEntityDamageIntensity);
    bool ApplySoftCollision(CPhysical* pEntity, CColPoint* pColPoint, float* pThisDamageIntensity, float* pEntityDamageIntensity);
    bool ProcessCollisionSectorList(int sectorX, int sectorY);
    bool ProcessCollisionSectorList_SimpleCar(CRepeatSector* pRepeatSector);
    void AttachEntityToEntity(CEntity* entity, CVector offset, CVector rotation);
    void AttachEntityToEntity(CEntity* entity, CVector* , RtQuat* rotation);
    bool CheckCollision();
    bool CheckCollision_SimpleCar();
};

VALIDATE_SIZE(CPhysical, 0x138);
