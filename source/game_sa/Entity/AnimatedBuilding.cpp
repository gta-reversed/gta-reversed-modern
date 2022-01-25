#include "StdInc.h"

void CAnimatedBuilding::InjectHooks()
{
    Install("CAnimatedBuilding", "ProcessControl", 0x537A30, &CAnimatedBuilding::ProcessControl_Reversed);
    Install("CAnimatedBuilding", "ProcessCollision", 0x537A40, &CAnimatedBuilding::ProcessCollision_Reversed);
    Install("CAnimatedBuilding", "PreRender", 0x403F00, &CAnimatedBuilding::PreRender_Reversed);
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
