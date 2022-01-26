#include "StdInc.h"

void CAnimatedBuilding::InjectHooks()
{
    RH_ScopedInstall(ProcessControl_Reversed, 0x537A30);
    RH_ScopedInstall(ProcessCollision_Reversed, 0x537A40);
    RH_ScopedInstall(PreRender_Reversed, 0x403F00);
}

void CAnimatedBuilding::ProcessControl()
{
    ProcessControl_Reversed();
}
void CAnimatedBuilding::ProcessControl_Reversed()
{}

void CAnimatedBuilding::ProcessCollision()
{
    CAnimatedBuilding::ProcessCollision_Reversed();
}
void CAnimatedBuilding::ProcessCollision_Reversed()
{
    m_bIsInSafePosition = true;
}

void CAnimatedBuilding::PreRender()
{
    CAnimatedBuilding::PreRender_Reversed();
}
void CAnimatedBuilding::PreRender_Reversed()
{
    if (!m_pRwObject)
        return;

    CEntity::PreRender();
    CEntity::UpdateRwFrame();
    CEntity::UpdateRpHAnim();
}
