#pragma once

/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"

enum eComplexJumpType 
{
    COMPLEX_JUMP_TYPE_JUMP = 0,
    COMPLEX_JUMP_TYPE_CLIMB = 1
};

class CTaskComplexJump : public CTaskComplex {
public:
    unsigned int m_nType; // 0 - jump , 1 - climb
    bool bUnkFlag;

    // 0 - jump , 1 - climb
    CTaskComplexJump* Constructor(unsigned int jumpType);
};

VALIDATE_SIZE(CTaskComplexJump, 0x14);