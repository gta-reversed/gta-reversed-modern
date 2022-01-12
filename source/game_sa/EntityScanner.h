/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CEntity;
class CPed;

class CEntityScanner {
protected:
    void* vtable;

public:
    int32    field_4;
    uint32   m_nCount;
    CEntity* m_apEntities[16];
    CEntity* m_pClosestEntityInRange;

public:
    static void InjectHooks();

    void     Clear();
    void     ScanForEntitiesInRange(int32 arg2, CPed* pPed);
    CEntity* GetClosestPedInRange();
};

VALIDATE_SIZE(CEntityScanner, 0x50);
