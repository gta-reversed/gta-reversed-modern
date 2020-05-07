#include "StdInc.h"

void InjectHooksMain(void)
{
    CStreaming::InjectHooks();
    CVehicleModelInfo::InjectHooks();
    CFileLoader::InjectHooks();
    CFileMgr::InjectHooks();
    CPhysical::InjectHooks();
    CRenderer::InjectHooks();
    CPed::InjectHooks();
    CPedIntelligence::InjectHooks();
    CTrain::InjectHooks();
    CAnimBlendAssociation::InjectHooks();
    CEventEditableResponse::InjectHooks();
    CEventDamage::InjectHooks();
    CTaskManager::InjectHooks();
    CTaskComplexUseSequence::InjectHooks();
    CTaskComplexSequence::InjectHooks();
    CTaskComplexWander::InjectHooks();
    CTaskComplexWanderCop::InjectHooks();
    CTaskSimplePlayerOnFoot::InjectHooks();
    CTaskSimpleSwim::InjectHooks();
    CTaskSimpleGoTo::InjectHooks();
    CTaskSimpleGoToPoint::InjectHooks();
    CTaskSimpleGoToPointFine::InjectHooks();
    CTaskSimpleStandStill::InjectHooks();
    CTaskComplexGoToPointAndStandStill::InjectHooks();
    CTaskComplexGoToPointAndStandStillTimed::InjectHooks();
    CTaskSimplePause::InjectHooks();
    CTaskSimpleHoldEntity::InjectHooks();
    CTaskSimplePutDownEntity::InjectHooks();
    CTaskSimplePickUpEntity::InjectHooks();
    cBuoyancy::InjectHooks();
    CWanted::InjectHooks();
    CWeapon::InjectHooks();
    CVehicle::InjectHooks();
    CPlayerPed::InjectHooks();
    CStats::InjectHooks();
    CCarCtrl::InjectHooks();
    CTheZones::InjectHooks();
    CMenuManager::InjectHooks();
    CSprite2d::InjectHooks();
    CVisibilityPlugins::InjectHooks();
}
