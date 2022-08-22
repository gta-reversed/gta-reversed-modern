#include "StdInc.h"

#include "AnimatedBuilding.h"

void CAnimatedBuilding::InjectHooks()
{
    RH_ScopedClass(CAnimatedBuilding);
    RH_ScopedCategory("Entity");

    RH_ScopedVirtualInstall(ProcessControl, 0x537A30);
    RH_ScopedVirtualInstall(ProcessCollision, 0x537A40);
    RH_ScopedVirtualInstall(PreRender, 0x403F00);
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
