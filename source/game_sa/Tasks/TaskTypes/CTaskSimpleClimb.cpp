/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CTaskSimpleClimb::CTaskSimpleClimb(CEntity *pClimbEnt, const CVector &vecTarget, float fHeading, unsigned char nSurfaceType, eClimbHeights nHeight, bool bForceClimb)
    : CTaskSimple(plugin::dummy)
{
    plugin::CallMethod<0x67A110, CTaskSimpleClimb*, CEntity*, const CVector&, float, unsigned char, eClimbHeights, bool>
        (this, pClimbEnt, vecTarget, fHeading, nSurfaceType, nHeight, bForceClimb);
}

CEntity * CTaskSimpleClimb::TestForClimb(CPed* pPed, CVector& climbPos, float& fAngle, unsigned char& nSurfaceType, bool theBool)
{
    return plugin::CallAndReturn<CEntity *, 0x6803A0, CPed*, CVector&, float&, unsigned char&, bool>(pPed, climbPos, fAngle, nSurfaceType, theBool);
}