/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CRGBA.h"
#include "CVector.h"
#include "CMatrix.h"

enum e3dMarkerType {
    MARKER3D_ARROW = 0,
    MARKER3D_CYLINDER = 1,
    MARKER3D_TUBE = 2,
    MARKER3D_ARROW2 = 3,
    MARKER3D_TORUS = 4,
    MARKER3D_CONE = 5,
    MARKER3D_CONE_NO_COLLISION = 6,

    MARKER3D_NUM,

    MARKER3D_NA = 257
};

class  C3dMarker {
public:
    CMatrix         m_mat;
    RpAtomic       *m_pAtomic;
    RpMaterial     *m_pMaterial;
    unsigned short  m_nType; // see e3dMarkerType
    bool            m_bIsUsed;
    bool            m_bMustBeRenderedThisFrame;
    int             m_nIdentifier;
    CRGBA           m_colour;
    short           m_nPulsePeriod;
    short           m_nRotateRate;
    int             m_nStartTime;
    float           m_fPulseFraction;
    float           m_fStdSize;
    float           m_fSize;
    float           m_fBrightness;
    float           m_fCameraRange;
    CVector         m_vecNormal;
    short           m_nLastMapReadX; // float casted to short
    short           m_nLastMapReadY; // float casted to short
    float           m_fLastMapReadResultZ;
    float           m_fRoofHeight;
    CVector         m_vecLastPosition;
    int             m_nOnScreenTestTime;

    bool AddMarker(unsigned int id, unsigned short type, float size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned short pulsePeriod, float pulseFraction, short rotateRate);
    void DeleteMarkerObject();
    bool IsZCoordinateUpToDate();
    void Render();
    void SetZCoordinateIfNotUpToDate(float coordinate);
    void UpdateZCoordinate(CVector arg0, float arg1);
};

VALIDATE_SIZE(C3dMarker, 0xA0);
