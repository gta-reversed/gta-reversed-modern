/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CEntity;
class CPed;

// Just a theory..
// Since this is originally a virtual class..
// Maybe it was templated? Like: `template<class Entity_t, size_t MaxCount>` ?

class CEntityScanner {
protected:
    void* vtable;

public:
    int32    field_4;
    uint32   m_nCount{16};
    CEntity* m_apEntities[16]{};
    CEntity* m_pClosestEntityInRange;

public:
    static void InjectHooks();

    void     Clear();
    void     ScanForEntitiesInRange(int32 arg2, CPed* ped);
    CEntity* GetClosestPedInRange();
};

VALIDATE_SIZE(CEntityScanner, 0x50);
