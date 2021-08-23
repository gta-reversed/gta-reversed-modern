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

    NUM_MARKER_TYPES,

    MARKER3D_NA = 257
};

class C3dMarker {
public:
    CMatrix m_mat;
    RpAtomic* m_pAtomic;
    RpMaterial* m_pMaterial;
    uint16_t m_nType;
    bool m_bIsUsed;
    bool m_bMustBeRenderedThisFrame;
    int32_t m_nIdentifier;
    CRGBA m_colour;
    int16_t m_nPulsePeriod;
    int16_t m_nRotateRate;
    int32_t m_nStartTime;
    float m_fPulseFraction;
    float m_fStdSize;
    float m_fSize;
    float m_fBrightness;
    float m_fCameraRange;
    CVector m_vecNormal;
    int16_t m_nLastMapReadX;
    int16_t m_nLastMapReadY;
    float m_fLastMapReadResultZ;
    float m_fRoofHeight;
    CVector m_vecLastPosition;
    int32_t m_nOnScreenTestTime;

public:
    static void InjectHooks();

    ~C3dMarker();
    C3dMarker();

    bool AddMarker(uint32_t id, e3dMarkerType type, float size, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint16_t pulsePeriod, float pulseFraction, int16_t rotateRate);
    void DeleteMarkerObject();
    void Render();
    bool IsZCoordinateUpToDate();
    void UpdateZCoordinate(CVector newPos, float zDistance);
    void SetZCoordinateIfNotUpToDate(float zCoord);

private:
    C3dMarker* Constructor();
    C3dMarker* Destructor();
};
VALIDATE_SIZE(C3dMarker, 0xA0);

