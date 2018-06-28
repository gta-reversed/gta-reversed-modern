/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAutomobile.h"

enum eHeliNodes {
    HELI_NODE_NONE = 0,
    HELI_CHASSIS = 1,
    HELI_WHEEL_RF = 2,
    HELI_WHEEL_RM = 3,
    HELI_WHEEL_RB = 4,
    HELI_WHEEL_LF = 5,
    HELI_WHEEL_LM = 6,
    HELI_WHEEL_LB = 7,
    HELI_DOOR_RF = 8,
    HELI_DOOR_RR = 9,
    HELI_DOOR_LF = 10,
    HELI_DOOR_LR = 11,
    HELI_STATIC_ROTOR = 12,
    HELI_MOVING_ROTOR = 13,
    HELI_STATIC_ROTOR2 = 14,
    HELI_MOVING_ROTOR2 = 15,
    HELI_RUDDER = 16,
    HELI_ELEVATORS = 17,
    HELI_MISC_A = 18,
    HELI_MISC_B = 19,
    HELI_MISC_C = 20,
    HELI_MISC_D = 21,
    HELI_NUM_NODES
};

struct tHeliLight {
    CVector m_vecOrigin;
    CVector m_vecTarget;
    float m_fTargetRadius;
    float m_fPower;
    int m_nCoronaIndex;
    bool field_24; // unknown flag
    bool m_bDrawShadow;
    char _pad[2];
    CVector field_28[3];
};

VALIDATE_SIZE(tHeliLight, 0x4C);

class CHeli : public CAutomobile {
protected:
    CHeli(plugin::dummy_func_t) : CAutomobile(plugin::dummy) {}
public:
    char               m_nHeliFlags;
    char _pad1[3];
    float              m_fLeftRightSkid;
    float              m_fSteeringUpDown;
    float              m_fSteeringLeftRight;
    float              m_fAccelerationBreakStatus;
    int field_99C;
    int                m_fRotorZ;
    int                m_fSecondRotorZ;
    float              m_fMaxAltitude;
    float field_9AC;
    float              m_fMinAltitude;
    int field_9B4;
    char field_9B8;
    char               m_nNumSwatOccupants;
    char               m_anSwatIDs[4];
    char _pad2[2];
    int field_9C0[4];
    int field_9D0;
    class FxSystem_c **m_pParticlesList;
    char field_9D8[24];
    int field_9F0;
    CVector            m_vecSearchLightTarget;
    float              m_fSearchLightIntensity;
    int field_A04;
    int field_A08;
    class FxSystem_c **m_ppGunflashFx;
    char               m_nFiringMultiplier;
    bool               m_bSearchLightEnabled;
    char _pad3[2];
    float field_A14;

    static bool& bPoliceHelisAllowed; // 1
    static unsigned int& TestForNewRandomHelisTimer;
    static CHeli** pHelis; // CHeli* pHelis[2];
    static unsigned int& NumberOfSearchLights;
    static bool& bHeliControlsCheat;
    static tHeliLight* HeliSearchLights; // tHeliLight CHeli::HeliSearchLights[4]

    CHeli(int modelIndex, unsigned char createdBy);

    void PreRenderAlways(); // dummy function
    CVector FindSwatPositionRelativeToHeli(int swatNumber);
    bool SendDownSwat();

    static void InitHelis();
    static void AddHeliSearchLight(CVector const& origin, CVector const& target, float targetRadius, float power, unsigned int coronaIndex, unsigned char unknownFlag, unsigned char drawShadow);
    static void Pre_SearchLightCone();
    static void Post_SearchLightCone();
    static void SpecialHeliPreRender(); // dummy function
    static void SwitchPoliceHelis(bool enable);
    static void SearchLightCone(int coronaIndex, CVector origin, CVector target, float targetRadius, float power, unsigned char unknownFlag, unsigned char drawShadow, CVector* arg7, CVector* arg8, CVector* arg9, bool arg10, float baseRadius);
    static CHeli* GenerateHeli(CPed* target, bool newsHeli);
    static bool TestSniperCollision(CVector* origin, CVector* target);
    static void UpdateHelis();
    static void RenderAllHeliSearchLights();
};

VALIDATE_SIZE(CHeli, 0xA18);