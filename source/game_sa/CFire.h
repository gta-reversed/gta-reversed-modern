/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CEntity.h"
#include "FxSystem_c.h"

class CFire {
public:
    struct {
        uint8 bActive : 1;
        uint8 bCreatedByScript : 1;
        uint8 bMakesNoise : 1;
        uint8 bBeingExtinguished : 1;
        uint8 bFirstGeneration : 1;
    } m_nFlags;
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
    FxSystem_c *m_pFxSystem;

    CFire();
    ~CFire();

    void Initialise();
    void Start(CEntity* pCreator, CVector pos, uint32_t nTimeToBurn, uint8_t nGens);
    void Start(CEntity* pCreator, CEntity* pTarget, uint32_t nTimeToBurn, uint8_t nGens);
    void Start(CVector pos, float fStrength, CEntity* pTarget, uint8_t nGens); /* For script */
    void CreateFxSysForStrength(const CVector&* point, RwMatrixTag* matrix);
    void Extinguish();
    void ExtinguishWithWater(float fWaterStrength);
    void ProcessFire();
    bool IsActive() const { return m_nFlags.bActive; }
    bool IsScript() const { return m_nFlags.bCreatedByScript; }
    bool IsFirstGen() const { return m_nFlags.bFirstGeneration; }
    bool IsBeingExtinguished() const { return m_nFlags.bBeingExtinguished; }

    // NOTSA funcs
    void DestroyFx();
    void SetTarget(CEntity* pTarget);
    void SetCreator(CEntity* pCreator);
};

VALIDATE_SIZE(CFire, 0x28);
