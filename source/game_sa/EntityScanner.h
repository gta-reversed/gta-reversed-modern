/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RepeatSector.h"
#include <extensions/utility.hpp>

class CEntity;
class CPed;

// Just a theory..
// Since this is originally a virtual class..
// Maybe it was templated? Like: `template<class Entity_t, size_t MaxCount>` ?

class CEntityScanner {
public:
    constexpr static size_t MAX_ENTITIES = 16;

public:
    int32    field_4;
    uint32   m_nCount;
    std::array<CEntity*, MAX_ENTITIES> m_apEntities; /// SEEMINGLY: The array might have "holes" in it, also it's sorted by distance (closer to further)
    CEntity* m_pClosestEntityInRange;

public:
    static void InjectHooks();

    CEntityScanner();
    ~CEntityScanner();

    /// View of all non-null entities as a view of `T&`
    template<typename T = CEntity>
    auto GetEntities() const {
        using namespace rng::views;
        using namespace notsa;

        return m_apEntities
             | filter(Not(IsNull<CEntity*>)) // Filter all null
             | transform([](CEntity* e) -> T& { return static_cast<T&>(*e); }); // Cast to required type and dereference
    }
    auto GetEntitiesPtr() { return m_apEntities.data(); }

    void Clear();
    virtual void ScanForEntitiesInRange(eRepeatSectorList sectorList, const CPed& ped);
};

VALIDATE_SIZE(CEntityScanner, 0x50);
