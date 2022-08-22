/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"

#include "RGBA.h"
#include "Vector.h"
#include "Matrix.h"

struct RpAtomic;
struct RpMaterial;

enum e3dMarkerType {
    MARKER3D_ARROW = 0,
    MARKER3D_CYLINDER = 1,
    MARKER3D_TUBE = 2,
    MARKER3D_ARROW2 = 3,
    MARKER3D_TORUS = 4,
    MARKER3D_CONE = 5,
    MARKER3D_CONE_NO_COLLISION = 6,
    MARKER3D_NA = 257
};

class C3dMarker {
public:
    CMatrix     m_mat;
    RpAtomic*   m_pAtomic;
    RpMaterial* m_pMaterial;
    uint16      m_nType; // see e3dMarkerType
    bool        m_bIsUsed;
    bool        m_bMustBeRenderedThisFrame;
    int32       m_nIdentifier;
    CRGBA       m_colour;
    int16       m_nPulsePeriod;
    int16       m_nRotateRate;
    int32       m_nStartTime;
    float       m_fPulseFraction;
    float       m_fStdSize;
    float       m_fSize;
    float       m_fBrightness;
    float       m_fCameraRange;
    CVector     m_vecNormal;
    int16       m_nLastMapReadX; // float casted to int16
    int16       m_nLastMapReadY; // float casted to int16
    float       m_fLastMapReadResultZ;
    float       m_fRoofHeight;
    CVector     m_vecLastPosition;
    int32       m_nOnScreenTestTime;

public:
    bool AddMarker(uint32 id, uint16 type, float size, uint8 red, uint8 green, uint8 blue, uint8 alpha, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
    void DeleteMarkerObject();
    bool IsZCoordinateUpToDate();
    void Render();
    void SetZCoordinateIfNotUpToDate(float coordinate);
    void UpdateZCoordinate(CVector arg0, float arg1);
};

VALIDATE_SIZE(C3dMarker, 0xA0);
