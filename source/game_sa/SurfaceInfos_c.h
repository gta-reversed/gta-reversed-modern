#pragma once

#include "SurfaceInfo_c.h"

class CColPoint;

class SurfaceInfos_c {
public:
    float         m_adhesiveLimits[6][6];
    SurfaceInfo_c m_surfaces[179];

    static char* cDefaultName;
    static void InjectHooks();

    void LoadAdhesiveLimits();
    uint32 GetSurfaceIdFromName(char* cName);
    void LoadSurfaceAudioInfos();
    void LoadSurfaceInfos();
    void Init();
    eAdhesionGroup GetAdhesionGroup(uint32 surfaceId);
    float GetTyreGrip(uint32 surfaceId);
    float GetWetMultiplier(uint32 surfaceId);
    uint32 GetSkidmarkType(uint32 surfaceId);
    eFrictionEffect GetFrictionEffect(uint32 surfaceId);
    uint32 GetBulletFx(uint32 surfaceId);
    bool IsSoftLanding(uint32 surfaceId);
    bool IsSeeThrough(uint32 surfaceId);
    bool IsShootThrough(uint32 surfaceId);
    bool IsSand(uint32 surfaceId);
    bool IsWater(uint32 surfaceId);
    bool IsShallowWater(uint32 surfaceId);
    bool IsBeach(uint32 surfaceId);
    bool IsSteepSlope(uint32 surfaceId);
    bool IsGlass(uint32 surfaceId);
    bool IsStairs(uint32 surfaceId);
    bool IsSkateable(uint32 surfaceId);
    bool IsPavement(uint32 surfaceId);
    uint32 GetRoughness(uint32 surfaceId);
    uint32 GetFlammability(uint32 surfaceId);
    bool CreatesSparks(uint32 surfaceId);
    bool CantSprintOn(uint32 surfaceId);
    bool LeavesFootsteps(uint32 surfaceId);
    bool ProducesFootDust(uint32 surfaceId);
    bool MakesCarDirty(uint32 surfaceId);
    bool MakesCarClean(uint32 surfaceId);
    bool CreatesWheelGrass(uint32 surfaceId);
    bool CreatesWheelGravel(uint32 surfaceId);
    bool CreatesWheelMud(uint32 surfaceId);
    bool CreatesWheelDust(uint32 surfaceId);
    bool CreatesWheelSand(uint32 surfaceId);
    bool CreatesWheelSpray(uint32 surfaceId);
    bool CreatesPlants(uint32 surfaceId);
    bool CreatesObjects(uint32 surfaceId);
    bool CanClimb(uint32 surfaceId);
    bool IsAudioConcrete(uint32 surfaceId);
    bool IsAudioGrass(uint32 surfaceId);
    bool IsAudioSand(uint32 surfaceId);
    bool IsAudioGravel(uint32 surfaceId);
    bool IsAudioWood(uint32 surfaceId);
    bool IsAudioWater(uint32 surfaceId);
    bool IsAudioMetal(uint32 surfaceId);
    bool IsAudioLongGrass(uint32 surfaceId);
    bool IsAudioTile(uint32 surfaceId);
    float GetAdhesiveLimit(CColPoint* colPoint);
};
VALIDATE_SIZE(SurfaceInfos_c, 0x8F4);

extern SurfaceInfos_c* g_surfaceInfos;
