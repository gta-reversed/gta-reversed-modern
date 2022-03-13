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
public:
    int32    field_4;
    uint32   m_nCount;
    CEntity* m_apEntities[16];
    CEntity* m_pClosestEntityInRange;

public:
    static void InjectHooks();

    CEntityScanner();
    ~CEntityScanner();

    void Clear();
    virtual void ScanForEntitiesInRange(int32 arg2, const CPed& ped);
    [[nodiscard]] CEntity* GetClosestPedInRange() const;
};

VALIDATE_SIZE(CEntityScanner, 0x50);
