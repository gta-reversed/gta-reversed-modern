/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CFire.h"

#define MAX_NUM_FIRES 60

class CFireManager {
public:
    CFire m_aFires[MAX_NUM_FIRES];
    uint32 m_nMaxFireGenerationsAllowed; // initialised with 999999 in Init()

    CFireManager();
    ~CFireManager();
    void Init();
    uint32 GetNumOfNonScriptFires();
    CFire* FindNearestFire(CVector const& position, bool notBeingExtinguished, bool notScript);
    bool PlentyFiresAvailable();
    void ExtinguishPoint(CVector point, float range);
    bool ExtinguishPointWithWater(CVector point, float range, float fireSizeMp);
    bool IsScriptFireExtinguished(int16 fireIndex);
    void RemoveScriptFire(int16 fireIndex);
    void RemoveAllScriptFires();
    void ClearAllScriptFireFlags();
    void SetScriptFireAudio(int16 fireIndex, bool enable);
    CVector* GetScriptFireCoords(int16 fireIndex);
    uint32 GetNumFiresInRange(CVector* point, float range);
    uint32 GetNumFiresInArea(float cornerA_x, float cornerA_y, float cornerA_z, float cornerB_x, float cornerB_y, float cornerB_z);
    void DestroyAllFxSystems();
    void CreateAllFxSystems();
    void Shutdown();
    void GetNextFreeFire(uint8 bAllowDeletingOldFire); // bAllowDeletingOldFire - allow deleting old fire if no free slots available
    CFire* StartFire(CVector point, _IGNORED_ float size, _IGNORED_ uint8 arg2, CEntity* creator, uint32 time, signed char numGenerations, _IGNORED_ uint8 arg6);
    CFire* StartFire(CEntity* target, CEntity* creator, _IGNORED_ float size, _IGNORED_ uint8 arg3, uint32 time, signed char numGenerations);
    int32 StartScriptFire(CVector const& point, CEntity* target, _IGNORED_ float arg2, _IGNORED_ uint8 arg3, signed char numGenerations, int32 size);
    void Update();
};

VALIDATE_SIZE(CFireManager, 0x964);

extern CFireManager &gFireManager;