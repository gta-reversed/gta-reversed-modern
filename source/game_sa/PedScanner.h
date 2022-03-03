#pragma once

#include "EntityScanner.h"
#include "Ped.h"

class CPedScanner : public CEntityScanner {
public:
    CPed* GetClosestPedInRange() { return m_pClosestEntityInRange->AsPed(); }
};
