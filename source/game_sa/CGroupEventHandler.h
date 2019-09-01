#pragma once
#include "CEvent.h"

/*
    !!!!!!!!!!!! WARNING  !!!!!!!!!!!!
    Size of CGroupEventHandler might be bigger. This may not be the complete class.
    This warning can be removed after confirming the class size.
*/

class CTask;
class CPedTaskPair;
class CEntity;

class CGroupEventHandler : public CEvent
{
    char field_4[8];
    union
    {
        CTask* m_pTask;
        int16_t m_taskId;
    };
    int f16;
    CEntity* m_pEntity;
    char field_24[16];
    CEntity* pAnotherEntity;
    char field_44[10];
    unsigned char f54;
    char field_55[3];
    char field_58[2];
    CPedTaskPair* m_pPedTaskPair;
    char field_64[656];
    signed char f720;
    char field_721 [3];
};

VALIDATE_SIZE(CGroupEventHandler, 0x2D4);
