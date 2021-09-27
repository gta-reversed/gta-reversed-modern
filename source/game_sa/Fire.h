/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Entity.h"
#include "FxSystem_c.h"

class CFire {
public:
    union {
        struct {
            bool active : 1;
            bool createdByScript : 1;
            bool makesNoise : 1;
            bool beingExtinguished : 1;
            bool firstGeneration : 1;
        };
        uint8 m_nFlags;
    };
    char        _pad0;
    int16       m_nScriptReferenceIndex;
    CVector     m_vecPosition;
    CEntity*    m_pEntityTarget;
    CEntity*    m_pEntityCreator;
    uint32      m_nTimeToBurn;
    float       m_fStrength;
    uint8       m_nNumGenerationsAllowed;
    uint8       m_nRemovalDist;
    FxSystem_c* m_pFxSystem;

public:
    CFire() = default;
    ~CFire() = default;

    void Initialise();
    void Start(CEntity* creator, CVector pos, uint32_t nTimeToBurn, uint8_t nGens);
    void Start(CEntity* creator, CEntity* target, uint32_t nTimeToBurn, uint8_t nGens);
    void Start(CVector pos, float fStrength, CEntity* target, uint8_t nGens); /* For script */
    void CreateFxSysForStrength(const CVector& point, RwMatrixTag* matrix);
    void Extinguish();
    void ExtinguishWithWater(float fWaterStrength);
    void ProcessFire();

    bool IsActive() const { return active; }
    bool IsScript() const { return createdByScript; }
    bool IsFirstGen() const { return firstGeneration; }
    bool IsBeingExtinguished() const { return beingExtinguished; }

    // NOTSA funcs
    void DestroyFx();
    void SetTarget(CEntity* target);
    void SetCreator(CEntity* creator);
};

VALIDATE_SIZE(CFire, 0x28);
