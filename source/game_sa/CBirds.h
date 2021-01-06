/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "eBirdsBiome.h"

/*
    researched by LINK/2012
    for 'The Birds Update' mod
*/

#pragma pack(push, 1)
struct CBirdColor {
public:
    RwUInt8 cRed;
    RwUInt8 cGreen;
    RwUInt8 cBlue;

    inline void Set(RwUInt8 cColor) {
        cRed = cColor;
        cGreen = cColor;
        cBlue = cColor;
    }

    inline void Set(RwUInt8 cR, RwUInt8 cG, RwUInt8 cB) {
        cRed = cR;
        cGreen = cG;
        cBlue = cB;
    }

    inline void Scale(RwReal fScale) {
        cRed = static_cast<RwUInt8>(static_cast<RwReal>(cRed) * fScale);
        cGreen = static_cast<RwUInt8>(static_cast<RwReal>(cGreen) * fScale);
        cBlue = static_cast<RwUInt8>(static_cast<RwReal>(cBlue) * fScale);
    }

};
#pragma pack(pop)
VALIDATE_SIZE(CBirdColor, 0x3);

enum class eBirdMode : unsigned char
{
    BIRD_DRAW_UPDATE = 0x1, // Bird is drawn, but doesn't update position
    BIRD_DRAW_NOUPDATE = 0x2, // Bird is drawn and updates position
};

#pragma pack(push, 1)
class  CBird {
public:
    CVector         m_vecPosn;            // Bird position
    CVector         m_vecCurrentVelocity; // Velocity in the current frame
    CVector         m_vecTargetVelocity;  // Velocity (constant if the bird is not flying in circles)
    float           m_fAngle;             // Bird angle
    unsigned int    m_nUpdateAfterMS;     // Always 0, if a value is written here, bird position isn't updated till CTimer::m_snTimeInMilliseconds is bigger than this value
    unsigned int    m_nWingStillness;     // How still are the wings
    float           m_fSize;              // Bird size
    float           m_fMaxBirdDistance;   // When the bird is in this distance from the camera, it will disappear.
                                          // Used also in rendering process to determine the alpha level of the bird.
    eBirdMode       m_eBirdMode;          // Always 1, if set to 2 then bird is drawn but doesn't update it's position, if it's set to anything else then bird isn't updated nor drawn
    CBirdColor      m_BodyColor;          // Body color
    CBirdColor      m_WingsColor;         // Wing tips color
    bool            m_bCreated;           // This flags indicates if in this index there's a bird created
    bool            m_bMustDoCurves;      // If this flag is true the bird will fly in circles
private:
    char _pad41[3];
public:
};
#pragma pack(pop)

VALIDATE_SIZE(CBird, 0x44);

class  CBirds {
public:
    static bool &bHasBirdBeenShot;
    static unsigned int &uiNumberOfBirds;
    static CBird *aBirds;
    static CVector &vecBirdShotAt;

    static float* faCreationCoorsX; // { 0.0f, -1.0f, 2.0f, -3.0f, 1.0f, -2.0f }                     These spawn in a formation like this:
    static float* faCreationCoorsY; // { 0.0f, -1.0f, -2.0f, 1.0f, 1.0f, -2.0f }                                                      4           5
    static float* faCreationCoorsZ; // { 0.0f, 0.5f, 1.0f, 0.7f, 2.0f, 1.2f }                                                                  1
                                    //                                                                                                      2
    static float* faRenderCoorsU;   // { 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f }                                                6           3
    static float* faRenderCoorsV;   // { 0.5f, 0.5f, 0.75f, 0.75f, 1.0f, 1.0f, 1.0f, 0.5f }
    static float* faRenderPosY;             // Size: 8
    static unsigned int* auRenderIndices; // Size: 30


    static void Init();
    static void CreateNumberOfBirds(CVector vecStartPos, CVector vecTargetPos, int iBirdCount, eBirdsBiome eBiome, bool bCheckObstacles);
    static void Shutdown();
    static void Update();
    static void Render();
    static void HandleGunShot(CVector const* pointA, CVector const* pointB);

    static void InjectHooks();
};

constexpr extern int32_t MAX_BIRDS = 6; // default: 6
