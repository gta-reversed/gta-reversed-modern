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
    CMatrix& matrix = pEntity->GetMatrix();

    const auto& vecForward = matrix.GetForward();
    matrix.GetUp() = CVector(-fSin * vecForward.y, fSin * vecForward.x, fCos);
    matrix.GetRight() = CrossProduct(vecForward, matrix.GetUp());
}
