/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "Ped.h"

class NOTSA_EXPORT_VTABLE CTaskComplexKillPedFromBoat : public CTaskComplex {
public:
    static constexpr auto Type = TASK_KILL_PED_FROM_BOAT;

    CPed* m_pPed;

public:
    CTaskComplexKillPedFromBoat(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexKillPedFromBoat, 0x10);
