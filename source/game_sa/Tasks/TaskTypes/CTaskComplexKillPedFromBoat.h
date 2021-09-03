/*
    Plugin-SDK (Grand Theft Auto) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskComplex.h"
#include "CPed.h"

class CTaskComplexKillPedFromBoat : public CTaskComplex {
public:
	CPed *pPed;

	CTaskComplexKillPedFromBoat(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexKillPedFromBoat, 0x10);

