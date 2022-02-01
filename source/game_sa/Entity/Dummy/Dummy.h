/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Entity.h"

class CDummy : public CEntity {
public:
    CDummy() : CEntity() { m_nType = eEntityType::ENTITY_TYPE_DUMMY; }
    static void* operator new(uint32 size);
    static void  operator delete(void* pObj);

public:
    static void InjectHooks();
};

VALIDATE_SIZE(CDummy, 0x38);

bool IsDummyPointerValid(CDummy* pDummy);
