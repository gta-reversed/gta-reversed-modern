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
    struct {
        uint8 bActive : 1;
        uint8 bCreatedByScript : 1;
        uint8 bMakesNoise : 1;
        uint8 bBeingExtinguished : 1;
        uint8 bFirstGeneration : 1;
    } m_nFlags;
    char     _pad0;
    int16    m_nScriptReferenceIndex;
    CVector  m_vecPosition;
    CEntity* m_pEntityTarget;
    CEntity* m_pEntityCreator;
    uint32   m_nTimeToBurn;
    float    m_fStrength;
    char     m_nNumGenerationsAllowed;
    uint8    m_nRemovalDist;
    char     _pad1[2];

public:
    FxSystem_c *m_pFxSystem;

    CFire();
    ~CFire();

    void Initialise();
    void CreateFxSysForStrength(RwV3d* point, RwMatrixTag* matrix);
    void Extinguish();
    void ProcessFire();
};

VALIDATE_SIZE(CFire, 0x28);
