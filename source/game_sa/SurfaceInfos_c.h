#pragma once
#include "PluginBase.h"
#include "SurfaceInfo_c.h"

class CColPoint;

class SurfaceInfos_c
{
public:
    float m_adhesiveLimits[6][6];
    SurfaceInfo_c m_surfaces[179];

    static char* cDefaultName;
    static void InjectHooks();

    void LoadAdhesiveLimits();
    unsigned int GetSurfaceIdFromName(char* cName);
    void LoadSurfaceAudioInfos();
    void LoadSurfaceInfos();
    void Init();
    eAdhesionGroup GetAdhesionGroup(unsigned int surfaceId);
    float GetTyreGrip(unsigned int surfaceId);
    float GetWetMultiplier(unsigned int surfaceId);
    unsigned int GetSkidmarkType(unsigned int surfaceId);
    eFrictionEffect GetFrictionEffect(unsigned int surfaceId);
    unsigned int GetBulletFx(unsigned int surfaceId);
    bool IsSoftLanding(unsigned int surfaceId);
    bool IsSeeThrough(unsigned int surfaceId);
    bool IsShootThrough(unsigned int surfaceId);
    bool IsSand(unsigned int surfaceId);
    bool IsWater(unsigned int surfaceId);
    bool IsShallowWater(unsigned int surfaceId);
    bool IsBeach(unsigned int surfaceId);
    bool IsSteepSlope(unsigned int surfaceId);
    bool IsGlass(unsigned int surfaceId);
    bool IsStairs(unsigned int surfaceId);
    bool IsSkateable(unsigned int surfaceId);
    bool IsPavement(unsigned int surfaceId);
    unsigned int GetRoughness(unsigned int surfaceId);
    unsigned int GetFlammability(unsigned int surfaceId);
    bool CreatesSparks(unsigned int surfaceId);
    bool CantSprintOn(unsigned int surfaceId);
    bool LeavesFootsteps(unsigned int surfaceId);
    bool ProducesFootDust(unsigned int surfaceId);
    bool MakesCarDirty(unsigned int surfaceId);
    bool MakesCarClean(unsigned int surfaceId);
    bool CreatesWheelGrass(unsigned int surfaceId);
    bool CreatesWheelGravel(unsigned int surfaceId);
    bool CreatesWheelMud(unsigned int surfaceId);
    bool CreatesWheelDust(unsigned int surfaceId);
    bool CreatesWheelSand(unsigned int surfaceId);
    bool CreatesWheelSpray(unsigned int surfaceId);
    bool CreatesPlants(unsigned int surfaceId);
    bool CreatesObjects(unsigned int surfaceId);
    bool CanClimb(unsigned int surfaceId);
    bool IsAudioConcrete(unsigned int surfaceId);
    bool IsAudioGrass(unsigned int surfaceId);
    bool IsAudioSand(unsigned int surfaceId);
    bool IsAudioGravel(unsigned int surfaceId);
    bool IsAudioWood(unsigned int surfaceId);
    bool IsAudioWater(unsigned int surfaceId);
    bool IsAudioMetal(unsigned int surfaceId);
    bool IsAudioLongGrass(unsigned int surfaceId);
    bool IsAudioTile(unsigned int surfaceId);
    float GetAdhesiveLimit(CColPoint* pColPoint);
};
VALIDATE_SIZE(SurfaceInfos_c, 0x8F4);

extern SurfaceInfos_c* g_surfaceInfos;
