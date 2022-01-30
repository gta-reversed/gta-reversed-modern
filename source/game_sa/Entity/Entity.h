/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Placeable.h"
#include "Reference.h"
#include "Rect.h"
#include "ColModel.h"
#include "Plugins\TwoDEffectPlugin\2dEffect.h"

#include "eEntityType.h"
#include "eEntityStatus.h"
#include "eModelID.h"
#include "eAreaCodes.h"

class CObject;
class CVehicle;
class CTrain;
class CBike;
class CBmx;
class CBoat;
class CAutomobile;
class CBike;
class CTrain;
class CPed;
class CObject;
class CBuilding;
class CDummy;
class CBuilding;
class CDummy;
class CPhysical;
class CBaseModelInfo;

class NOTSA_EXPORT_VTABLE CEntity : public CPlaceable {
public:
    union {
        struct RwObject* m_pRwObject;
        struct RpClump*  m_pRwClump;
        struct RpAtomic* m_pRwAtomic;
    };
    union {
        struct {
            /* https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CEntitySA.h */
            uint32 m_bUsesCollision : 1;               // does entity use collision
            uint32 m_bCollisionProcessed : 1;          // has object been processed by a ProcessEntityCollision function
            uint32 m_bIsStatic : 1;                    // is entity static
            uint32 m_bHasContacted : 1;                // has entity processed some contact forces
            uint32 m_bIsStuck : 1;                     // is entity stuck
            uint32 m_bIsInSafePosition : 1;            // is entity in a collision free safe position
            uint32 m_bWasPostponed : 1;                // was entity control processing postponed
            uint32 m_bIsVisible : 1;                   // is the entity visible

            uint32 m_bIsBIGBuilding : 1;               // Set if this entity is a big building
            uint32 m_bRenderDamaged : 1;               // use damaged LOD models for objects with applicable damage
            uint32 m_bStreamingDontDelete : 1;         // Don't let the streaming remove this
            uint32 m_bRemoveFromWorld : 1;             // remove this entity next time it should be processed
            uint32 m_bHasHitWall : 1;                  // has collided with a building (changes subsequent collisions)
            uint32 m_bImBeingRendered : 1;             // don't delete me because I'm being rendered
            uint32 m_bDrawLast : 1;                    // draw object last
            uint32 m_bDistanceFade : 1;                // Fade entity because it is far away

            uint32 m_bDontCastShadowsOn : 1;           // Don't cast shadows on this object
            uint32 m_bOffscreen : 1;                   // offscreen flag. This can only be trusted when it is set to true
            uint32 m_bIsStaticWaitingForCollision : 1; // this is used by script created entities - they are static until the collision is loaded below them
            uint32 m_bDontStream : 1;                  // tell the streaming not to stream me
            uint32 m_bUnderwater : 1;                  // this object is underwater change drawing order
            uint32 m_bHasPreRenderEffects : 1;         // Object has a prerender effects attached to it
            uint32 m_bIsTempBuilding : 1;              // whether the building is temporary (i.e. can be created and deleted more than once)
            uint32 m_bDontUpdateHierarchy : 1;         // Don't update the animation hierarchy this frame

            uint32 m_bHasRoadsignText : 1;             // entity is roadsign and has some 2dEffect text stuff to be rendered
            uint32 m_bDisplayedSuperLowLOD : 1;
            uint32 m_bIsProcObject : 1;                // set object has been generated by procedural object generator
            uint32 m_bBackfaceCulled : 1;              // has backface culling on
            uint32 m_bLightObject : 1;                 // light object with directional lights
            uint32 m_bUnimportantStream : 1;           // set that this object is unimportant, if streaming is having problems
            uint32 m_bTunnel : 1;                      // Is this model part of a tunnel
            uint32 m_bTunnelTransition : 1;            // This model should be rendered from within and outside the tunnel
        };
        uint32 m_nFlags;
    };
    /* */
    union {
        struct {
            uint16 m_nRandomSeedUpperByte : 8;
            uint16 m_nRandomSeedSecondByte : 8;
        };
        uint16 m_nRandomSeed;
    };
    uint16           m_nModelIndex;
    CReference*      m_pReferences;
    CLink<CEntity*>* m_pStreamingLink;
    uint16           m_nScanCode;
    uint8            m_nIplIndex;
    eAreaCodes       m_nAreaCode;
    union {
        int32    m_nLodIndex; // -1 - without LOD model
        CEntity* m_pLod;
    };
    int8          m_nNumLodChildren;
    uint8         m_nNumLodChildrenRendered;
    eEntityType   m_nType : 3;          // Mask: & 0x7  = 7
    eEntityStatus m_nStatus : 5;        // Mask: & 0xF8 = 248 (Remember: In the original code unless this was left shifted the value it's compared to has to be left shifted by 3!)

public:
    CEntity();
    ~CEntity() override;

    virtual void Add();                                             // VTab: 2, similar to previous, but with entity bound rect
    virtual void Add(const CRect& rect);                            // VTab: 1
    virtual void Remove();                                          // VTab: 3
    virtual void SetIsStatic(bool isStatic);                        // VTab: 4
    virtual void SetModelIndex(uint32 index);                       // VTab: 5
    virtual void SetModelIndexNoCreate(uint32 index);               // VTab: 6
    virtual void CreateRwObject();                                  // VTab: 7
    virtual void DeleteRwObject();                                  // VTab: 8
    virtual CRect* GetBoundRect(CRect* pRect);                      // VTab: 9 - TODO: Most likely RVO'd. Should probably return a `CRect`, and take no args.
    virtual void ProcessControl();                                  // VTab: 10
    virtual void ProcessCollision();                                // VTab: 11
    virtual void ProcessShift();                                    // VTab: 12
    virtual bool TestCollision(bool bApplySpeed);                   // VTab: 13
    virtual void Teleport(CVector destination, bool resetRotation); // VTab: 14
    virtual void SpecialEntityPreCollisionStuff(CPhysical* colPhysical,
                                                bool bIgnoreStuckCheck,
                                                bool& bCollisionDisabled,
                                                bool& bCollidedEntityCollisionIgnored,
                                                bool& bCollidedEntityUnableToMove,
                                                bool& bThisOrCollidedEntityStuck);                                    // VTab: 15
    virtual uint8 SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2);          // VTab: 16
    virtual void PreRender();                                                                                         // VTab: 17
    virtual void Render();                                                                                            // VTab: 18
    virtual bool SetupLighting();                                                                                     // VTab: 19
    virtual void RemoveLighting(bool bRemove);                                                                        // VTab: 20
    virtual void FlagToDestroyWhenNextProcessed();                                                                    // VTab: 21

    void UpdateRwFrame();
    void UpdateRpHAnim();
    bool HasPreRenderEffects();
    bool DoesNotCollideWithFlyers();
    void ModifyMatrixForPoleInWind();
    bool LivesInThisNonOverlapSector(int32 sectorX, int32 sectorY);
    void SetupBigBuilding();
    void ModifyMatrixForCrane();
    void PreRenderForGlassWindow();
    void SetRwObjectAlpha(int32 alpha);
    CVector* FindTriggerPointCoors(CVector* pOutVec, int32 triggerIndex);
    C2dEffect* GetRandom2dEffect(int32 effectType, bool bCheckForEmptySlot);
    CVector TransformFromObjectSpace(const CVector& offset);
    CVector* TransformFromObjectSpace(CVector& outPos, const CVector& offset);
    void CreateEffects();
    void DestroyEffects();
    void AttachToRwObject(RwObject* object, bool updateEntityMatrix);
    void DetachFromRwObject();
    CVector* GetBoundCentre(CVector* pOutCentre);
    void GetBoundCentre(CVector& outCentre);
    CVector GetBoundCentre();
    void RenderEffects();
    // is entity touching entity
    bool GetIsTouching(CEntity* entity);
    // is entity touching sphere
    bool GetIsTouching(const CVector& centre, float radius);
    bool GetIsOnScreen();
    bool GetIsBoundingBoxOnScreen();
    void ModifyMatrixForTreeInWind();
    void ModifyMatrixForBannerInWind();
    RwMatrix* GetModellingMatrix();
    CColModel* GetColModel() const;
    void CalculateBBProjection(CVector* corner1, CVector* corner2, CVector* corner3, CVector* corner4);
    void UpdateAnim();
    bool IsVisible();
    float GetDistanceFromCentreOfMassToBaseOfModel();
    void CleanUpOldReference(CEntity** entity); // See helper SafeCleanUpOldReference
    void ResolveReferences();
    void PruneReferences();
    void RegisterReference(CEntity** entity);
    void ProcessLightsForEntity();
    void RemoveEscalatorsForEntity();
    bool IsEntityOccluded();
    bool IsInCurrentAreaOrBarberShopInterior();
    void UpdateRW();
    // Always returns a non-null value. In case there's no LOD object `this` is returned. NOTSA
    CEntity* FindLastLOD() noexcept;

    // NOTSA
    CBaseModelInfo* GetModelInfo() const;
    CCollisionData* GetColData() { return GetColModel()->m_pColData; }

    // Wrapper around the mess called `CleanUpOldReference`
    // Takes in `ref` (which is usually a member variable),
    // calls `CleanUpOldReference` on it, then sets it to `nullptr`
    // Used often in the code.
    template<typename T>
    static void ClearReference(T*& ref) requires std::is_base_of_v<CEntity, T> {
        if (ref) {
            ref->CleanUpOldReference(reinterpret_cast<CEntity**>(&ref));
            ref = nullptr;
        }
    }

    // Wrapper around the mess called "entity references"
    // This one sets the given `inOutRef` member variable to `entity`
    // + clears the old entity (if any)
    // + set the new entity (if any)
    template<typename T, typename Y>
    static void ChangeEntityReference(T*& inOutRef, Y* entity) requires std::is_base_of_v<CEntity, T> && std::is_base_of_v<CEntity, Y> {
        ClearReference(inOutRef); // Clear old
        if (entity) { // Set new (if any)
            inOutRef = entity;
            inOutRef->RegisterReference(reinterpret_cast<CEntity**>(&inOutRef));
        }
    }

    template<typename T>
    static void RegisterReference(T*& ref) requires std::is_base_of_v<CEntity, T> {
        ref->RegisterReference(reinterpret_cast<CEntity**>(&ref));
    }

    template<typename T>
    static void CleanUpOldReference(T*& ref) requires std::is_base_of_v<CEntity, T> {
        ref->CleanUpOldReference(reinterpret_cast<CEntity**>(&ref));
    }

    template<typename T>
    static void SafeRegisterRef(T*& e) requires std::is_base_of_v<CEntity, T> {
        if (e) {
            e->RegisterReference(reinterpret_cast<CEntity**>(&e));
        }
    }

    template<typename T>
    static void SafeCleanUpRef(T*& e) requires std::is_base_of_v<CEntity, T> {
        if (e) {
            e->CleanUpOldReference(reinterpret_cast<CEntity**>(&e));
        }
    }

public:
    // Rw callbacks
    static RpAtomic* SetAtomicAlphaCB(RpAtomic* atomic, void* data);
    static RpMaterial* SetMaterialAlphaCB(RpMaterial* material, void* data);

    [[nodiscard]] bool IsPhysical() const { return m_nType > ENTITY_TYPE_BUILDING && m_nType < ENTITY_TYPE_DUMMY; }
    [[nodiscard]] bool IsNothing()  const { return m_nType == ENTITY_TYPE_NOTHING; }
    [[nodiscard]] bool IsVehicle()  const { return m_nType == ENTITY_TYPE_VEHICLE; }
    [[nodiscard]] bool IsPed()      const { return m_nType == ENTITY_TYPE_PED; }
    [[nodiscard]] bool IsObject()   const { return m_nType == ENTITY_TYPE_OBJECT; }
    [[nodiscard]] bool IsBuilding() const { return m_nType == ENTITY_TYPE_BUILDING; }
    [[nodiscard]] bool IsDummy()    const { return m_nType == ENTITY_TYPE_DUMMY; }

    [[nodiscard]] bool IsModelTempCollision() const { return m_nModelIndex >= MODEL_TEMPCOL_DOOR1 && m_nModelIndex <= MODEL_TEMPCOL_BODYPART2; }
    [[nodiscard]] bool IsStatic() const { return m_bIsStatic || m_bIsStaticWaitingForCollision; } // 0x4633E0
    [[nodiscard]] bool IsRCCar()  const { return m_nModelIndex == MODEL_RCBANDIT || m_nModelIndex == MODEL_RCTIGER || m_nModelIndex == MODEL_RCCAM; }

    auto AsPhysical()         { return reinterpret_cast<CPhysical*>(this); }
    auto AsVehicle()          { return reinterpret_cast<CVehicle*>(this); }
    auto AsAutomobile()       { return reinterpret_cast<CAutomobile*>(this); }
    auto AsAutomobile() const { return reinterpret_cast<const CAutomobile*>(this); }
    auto AsBike()             { return reinterpret_cast<CBike*>(this); }
    auto AsBike()       const { return reinterpret_cast<const CBike*>(this); }
    auto AsBmx()              { return reinterpret_cast<CBmx*>(this); }
    auto AsBmx()        const { return reinterpret_cast<const CBmx*>(this); }
    auto AsBoat()             { return reinterpret_cast<CBoat*>(this); }
    auto AsBoat()       const { return reinterpret_cast<const CBoat*>(this); }
    auto AsTrain()            { return reinterpret_cast<CTrain*>(this); }
    auto AsTrain()      const { return reinterpret_cast<const CTrain*>(this); }
    auto AsPed()              { return reinterpret_cast<CPed*>(this); }
    auto AsObject()           { return reinterpret_cast<CObject*>(this); }
    auto AsBuilding()         { return reinterpret_cast<CBuilding*>(this); }
    auto AsDummy()            { return reinterpret_cast<CDummy*>(this); }

    [[nodiscard]] auto GetType() const noexcept { return m_nType; }
    void SetType(eEntityType type) { m_nType = type; }

    [[nodiscard]] auto GetStatus() const noexcept { return m_nStatus; }
    void SetStatus(eEntityStatus status) { m_nStatus = status; }

    bool IsScanCodeCurrent() const;
    void SetCurrentScanCode();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void Add_Reversed();
    void Add_Reversed(const CRect& rect);
    void Remove_Reversed();
    void SetIsStatic_Reversed(bool isStatic);
    void SetModelIndex_Reversed(uint32 index);
    void SetModelIndexNoCreate_Reversed(uint32 index);
    void CreateRwObject_Reversed();
    void DeleteRwObject_Reversed();
    CRect* GetBoundRect_Reversed(CRect* pRect);
    void ProcessControl_Reversed();
    void ProcessCollision_Reversed();
    void ProcessShift_Reversed();
    bool TestCollision_Reversed(bool bApplySpeed);
    void Teleport_Reversed(CVector destination, bool resetRotation);
    void SpecialEntityPreCollisionStuff_Reversed(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled, bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck);
    uint8 SpecialEntityCalcCollisionSteps_Reversed(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2);
    void PreRender_Reversed();
    void Render_Reversed();
    bool SetupLighting_Reversed();
    void RemoveLighting_Reversed(bool bRemove);
    void FlagToDestroyWhenNextProcessed_Reversed();
};

VALIDATE_SIZE(CEntity, 0x38);

bool IsEntityPointerValid(CEntity* entity);
RpMaterial* MaterialUpdateUVAnimCB(RpMaterial* material, void* data);

bool IsGlassModel(CEntity* entity);

static inline float& GAME_GRAVITY = *(float*)0x863984; // default 0.008f
