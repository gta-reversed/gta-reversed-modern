#include "StdInc.h"

void CGarage::InjectHooks()
{
    ReversibleHooks::Install("CGarage", "BuildRotatedDoorMatrix", 0x4479F0, &CGarage::BuildRotatedDoorMatrix);
}

void CGarage::BuildRotatedDoorMatrix(CEntity* pEntity, float fDoorPosition)
{
    const auto fAngle = fDoorPosition * -HALF_PI;
    const auto fSin = sin(fAngle);
    const auto fCos = cos(fAngle);
    auto* pMat = pEntity->GetMatrix();

    const auto& vecForward = pMat->GetForward();
    pMat->GetUp() = CVector(-fSin * vecForward.y, fSin * vecForward.x, fCos);
    pMat->GetRight() = CrossProduct(vecForward, pMat->GetUp());
}
