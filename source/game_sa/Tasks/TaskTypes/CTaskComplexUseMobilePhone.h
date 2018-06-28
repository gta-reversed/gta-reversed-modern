/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CTaskTimer.h"

class  CTaskComplexUseMobilePhone : public CTaskComplex {
protected:
    CTaskComplexUseMobilePhone(plugin::dummy_func_t a) : CTaskComplex(a) , m_timer(a) {}
public:
    int m_nDuration;
    CTaskTimer m_timer;
    bool m_bIsAborting;
    bool m_bQuit;

    CTaskComplexUseMobilePhone(int nDuration);
};

VALIDATE_SIZE(CTaskComplexUseMobilePhone, 0x20);

