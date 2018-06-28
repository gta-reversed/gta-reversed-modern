/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CFire.h"

#define MAX_NUM_FIRES 60

class  CFireManager {
public:
    CFire m_aFires[MAX_NUM_FIRES];
    unsigned int m_nMaxFireGenerationsAllowed; // initialised with 999999 in Init()

    CFireManager();
    ~CFireManager();
    void Init();
    unsigned int GetNumOfNonScriptFires();
    CFire* FindNearestFire(CVector const& position, bool notBeingExtinguished, bool notScript);
    bool PlentyFiresAvailable();
    void ExtinguishPoint(CVector point, float range);
    bool ExtinguishPointWithWater(CVector point, float range, float fireSizeMp);
    bool IsScriptFireExtinguished(short fireIndex);
    void RemoveScriptFire(short fireIndex);
    void RemoveAllScriptFires();
    void ClearAllScriptFireFlags();
    void SetScriptFireAudio(short fireIndex, bool enable);
    CVector* GetScriptFireCoords(short fireIndex);
    unsigned int GetNumFiresInRange(CVector* point, float range);
    unsigned int GetNumFiresInArea(float cornerA_x, float cornerA_y, float cornerA_z, float cornerB_x, float cornerB_y, float cornerB_z);
    void DestroyAllFxSystems();
    void CreateAllFxSystems();
    void Shutdown();
    void GetNextFreeFire(unsigned char bAllowDeletingOldFire); // bAllowDeletingOldFire - allow deleting old fire if no free slots available
    CFire* StartFire(CVector point, _IGNORED_ float size, _IGNORED_ unsigned char arg2, CEntity* creator, unsigned int time, signed char numGenerations, _IGNORED_ unsigned char arg6);
    CFire* StartFire(CEntity* target, CEntity* creator, _IGNORED_ float size, _IGNORED_ unsigned char arg3, unsigned int time, signed char numGenerations);
    int StartScriptFire(CVector const& point, CEntity* target, _IGNORED_ float arg2, _IGNORED_ unsigned char arg3, signed char numGenerations, int size);
    void Update();
};

VALIDATE_SIZE(CFireManager, 0x964);

extern CFireManager &gFireManager;