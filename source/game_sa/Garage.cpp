#include "StdInc.h"

void CGarage::InjectHooks()
{
    using namespace ReversibleHooks;
    Install("CGarage", "BuildRotatedDoorMatrix", 0x4479F0, &CGarage::BuildRotatedDoorMatrix);
    Install("CGarage", "StoreAndRemoveCarsForThisHideOut", 0x449900, &CGarage::StoreAndRemoveCarsForThisHideOut);
}

// 0x4479F0
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

// 0x449900
void CGarage::StoreAndRemoveCarsForThisHideOut(CStoredCar* storedCars, int32 maxSlot)
{
    maxSlot = std::min(maxSlot, 4);

    for (auto i = 0; i < 4; i++)
        storedCars[i].Clear();

    auto vehPool = CPools::GetVehiclePool();
    int vehIdx = 0;
    auto i = vehPool->GetSize();

    while (i--) {
        if (vehPool->m_byteMap[i].IntValue() >= 0) {
            auto veh = vehPool->GetAt(i);

            if (!veh)
                continue;

            if (IsPointInsideGarage(veh->GetPosition()) && veh->m_nCreatedBy != MISSION_VEHICLE) {
                if (vehIdx < maxSlot && !EntityHasASphereWayOutsideGarage(veh, 1.0f)) {
                    storedCars[vehIdx++].StoreCar(veh);
                }

                FindPlayerInfo().CancelPlayerEnteringCars(veh);
                CWorld::Remove(veh);

                delete veh;
            }
        }
    }

    for (i = vehIdx; i < 4; i++)
        storedCars[i].Clear();
}

// 0x449050
bool CGarage::EntityHasASphereWayOutsideGarage(CEntity* pEntity, float fRadius)
{
    return plugin::CallMethodAndReturn<bool, 0x449050, CGarage*, CEntity*, float>(this, pEntity, fRadius);
}

// 0x448740
bool CGarage::IsPointInsideGarage(CVector vecPoint)
{
    if (vecPoint.z < m_vPosn.z || vecPoint.z > m_fTopZ)
        return false;

    auto xDiff = vecPoint.x - m_vPosn.x;
    auto yDiff = vecPoint.y - m_vPosn.y;

    auto diffDirA = xDiff * m_vDirectionA.x + yDiff * m_vDirectionA.y;
    auto diffDirB = xDiff * m_vDirectionB.x + yDiff * m_vDirectionB.y;

    bool betweenA = diffDirA >= 0.0f && diffDirA <= m_fWidth;
    bool betweenB = diffDirB >= 0.0f && diffDirB <= m_fHeight;

    return betweenA && betweenB;
}

// todo move
// 0x449760
void CStoredCar::StoreCar(CVehicle* pVehicle)
{
    plugin::CallMethod<0x449760, CStoredCar*, CVehicle*>(this, pVehicle);
}
