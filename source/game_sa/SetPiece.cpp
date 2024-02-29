#include "StdInc.h"
#include "Automobile.h"

void CSetPiece::InjectHooks() {
    RH_ScopedClass(CSetPiece);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(TryToGenerateCopPed, 0x499690);
    RH_ScopedInstall(TryToGenerateCopCar, 0x4998A0);
    RH_ScopedInstall(Update, 0x499A80, {.reversed=false});
}

// 0x499690
CCopPed* CSetPiece::TryToGenerateCopPed(CVector2D posn) {
    CVector   point{ posn, 1000.0f };
    CColPoint cp{};
    CEntity*  entity{};
    if (CWorld::ProcessVerticalLine(
        point,
        -1000.0f,
        cp,
        entity,
        true,
        false,
        false,
        false,
        true
    )) {
        point.z = cp.m_vecPoint.z + 0.9f;
    }

    int16 numCollidingObjects{};
    CWorld::FindObjectsKindaColliding(
        point,
        0.6f,
        false,
        &numCollidingObjects,
        16,
        nullptr,
        false,
        true,
        true,
        false,
        false
    );

    if (!numCollidingObjects) {
        return nullptr;
    }

    auto* cop = new CCopPed(0);
    cop->SetPosn(point);
    CWorld::Add(cop);
    return cop;
}

// 0x4998A0
CVehicle* CSetPiece::TryToGenerateCopCar(CVector2D posn, CVector2D target) {
    const auto carModel = CStreaming::GetDefaultCopCarModel();
    if (carModel < 0) {
        return nullptr;
    }

    auto* car = new CAutomobile(carModel, RANDOM_VEHICLE, true);

    CVector point{ posn, 1000.0f };
    CColPoint cp{};
    CEntity*  entity{};
    if (CWorld::ProcessVerticalLine(
        point,
        -1000.0f,
        cp,
        entity,
        true,
        false,
        false,
        false,
        true
    )) {
        point.z = car->GetHeightAboveRoad() + cp.m_vecPoint.z;
    }

    const CVector dir{ (target - posn).Normalized() };
    // TODO?
    car->GetForward()  = dir;
    car->GetRight()    = CVector{ dir.y, -dir.x, 0.0f };
    car->GetUp()       = CVector::ZAxisVector();
    car->GetPosition() = point;

    int16 numCollidingObjects{};
    CWorld::FindObjectsKindaColliding(
        point,
        car->GetColModel()->GetBoundRadius(),
        false,
        &numCollidingObjects,
        16,
        nullptr,
        false,
        true,
        true,
        false,
        false
    );

    if (!numCollidingObjects) {
        car->ChangeLawEnforcerState(true);
        CWorld::Add(car);
    } else {
        delete std::exchange(car, nullptr);
    }

    return car;
}

// 0x499A80
void CSetPiece::Update() {
    if (m_nLastGenerationTime != 0 && CTimer::GetTimeInMS() <= m_nLastGenerationTime + 4000) {
        return;
    }

    const auto playerPos = FindPlayerCoors();
}
