/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RGBA.h"
#include "Vector.h"

/*!
 * @brief Checkpoint types. Original enum had prefix of `CHECKPOINT_`
*/
enum class eCheckpointType : uint32 {
    TUBE         = 0x0,
    ENDTUBE      = 0x1,
    EMPTYTUBE    = 0x2,
    TORUS        = 0x3,
    TORUS_NOFADE = 0x4,
    TORUSROT     = 0x5,
    TORUSTHROUGH = 0x6,
    TORUS_UPDOWN = 0x7,
    TORUS_DOWN   = 0x8,

    //
    // Add above this
    //
    NUM = 0x9,   ///< Count of different checkpoint types
    NA  = 0x101, ///< Sentinel value (Used for markers not in use)
};

class CCheckpoint {
public:
    uint16  m_nType;
    bool    m_bIsUsed;
    bool    m_bMustBeRenderedThisFrame;
    int32   m_nIdentifier;
    CRGBA   m_Colour;
    int16   m_nPulsePeriod;
    int16   m_nRotateRate;
    CVector m_vecPosition;
    CVector m_vecDirection;
    float   m_fPulseFraction;
    float   m_fSize;
    float   m_fDistanceToPlayer; // or CameraRange
    float   m_fMultiSize;

public:
    static void InjectHooks() {
        RH_ScopedClass(CCheckpoint);
        RH_ScopedCategoryGlobal();
        RH_ScopedInstall(Render, 0x725C00, { .reversed = false });
    }

    void Init() {
        m_nType                    = 257; // MARKER3D_NA?
        m_bIsUsed                  = false;
        m_nIdentifier              = 0;
        m_Colour                   = CRGBA(255, 255, 255, 255);
        m_nPulsePeriod             = 1024;
        m_nRotateRate              = 5;
        m_vecPosition              = CVector();
        m_vecDirection             = CVector();
        m_fPulseFraction           = 0.25f;
        m_fSize                    = 1.0f;
        m_fDistanceToPlayer        = 0.0f;
        m_fMultiSize               = 0.0f;
        m_bMustBeRenderedThisFrame = true;
    }

    void Render();
};

VALIDATE_SIZE(CCheckpoint, 0x38);
