#include "StdInc.h"

cBuoyancy& mod_Buoyancy = *(cBuoyancy*)0xC1C890;

bool cBuoyancy::ProcessBuoyancy(CEntity* pEntity, float fBuoyancy, CVector* pOutVecMoveForce, CVector* pOutVecTurnForce)
{
    return plugin::CallMethodAndReturn<bool, 0x6C3EF0, cBuoyancy*, CEntity*, float, CVector*, CVector*> 
        (this, pEntity, fBuoyancy, pOutVecMoveForce, pOutVecTurnForce);
}