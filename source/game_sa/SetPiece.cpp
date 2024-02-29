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
    if (m_nLastGenerationTime != 0 && CTimer::GetTimeInMS() <= m_nLastGenerationTime + 4'000u) {
        return;
    }

    const auto playerPos = FindPlayerCoors();
    if (!CRect{ m_AreaRect }.IsPointInside(playerPos)) {
        return;
    }

    switch (const auto t = m_nType) {
    case SETPIECE_2CARS_SLOW_SPEED:
    case SETPIECE_2CARS_MEDIUM_SPEED: {
        if (const auto* p = FindPlayerPed(); p->GetWantedLevel() < 1 || FindPlayerVehicle()) {
            break;
        }

        auto* car1 = TryToGenerateCopCar(GetSpawnCoord1(), GetTargetCoord1());
        if (!car1) {
            break;
        }

        auto* car2 = TryToGenerateCopCar(GetSpawnCoord2(), GetTargetCoord2());
        if (!car2) {
            CWorld::Remove(car1);
            delete car1;
            break;
        }

        const auto SetupCar = [this, t](CVehicle* car, const CVector2D& dest) {
            car->m_nStatus                         = STATUS_SIMPLE;
            car->m_autoPilot.m_nCruiseSpeed        = (t == SETPIECE_2CARS_SLOW_SPEED) ? 4 : 24;
            car->m_autoPilot.m_nCarDrivingStyle    = DRIVING_STYLE_SLOW_DOWN_FOR_CARS;
            car->m_autoPilot.m_nCarMission         = MISSION_SLOWLY_DRIVE_TOWARDS_PLAYER_1;
            car->m_autoPilot.m_speed               = car->m_autoPilot.m_nCruiseSpeed;
            car->m_autoPilot.m_vecDestinationCoors = CVector{ dest };
            car->m_nTimeTillWeNeedThisCar          = CTimer::GetTimeInMS() + 25'000;
            CCarAI::AddPoliceCarOccupants(car, false);
        };
        SetupCar(car1, GetTargetCoord1());
        SetupCar(car2, GetTargetCoord2());
        m_nLastGenerationTime = CTimer::GetTimeInMS();
        break;
    }
    case SETPIECE_1CAR_QUICK_SPEED: {
        if (const auto* p = FindPlayerPed(); p->GetWantedLevel() < 2 || !FindPlayerVehicle()) {
            break;
        }

        const auto playerToSpawn = FindPlayerCoors() - GetSpawnCoord1();
        if (playerToSpawn.Dot(FindPlayerSpeed()) >= 0.0f) {
            break;
        }

        if (auto* car = TryToGenerateCopCar(GetSpawnCoord1(), GetTargetCoord1())) {
            car->m_nStatus                      = STATUS_SIMPLE;
            car->m_autoPilot.m_nCruiseSpeed     = 16;
            car->m_autoPilot.m_nCarDrivingStyle = DRIVING_STYLE_PLOUGH_THROUGH;
            car->m_autoPilot.m_nCarMission      = MISSION_BLOCKPLAYER_FORWARDANDBACK;
            car->m_autoPilot.m_nTempAction      = 9; // TODO: enum
            car->m_autoPilot.m_nTempActionTime  = CTimer::GetTimeInMS() + 100;
            car->m_nTimeTillWeNeedThisCar       = CTimer::GetTimeInMS() + 10'000;
            car->GetMoveSpeed()                 = car->GetForward() * 2.0f / 3.0f;
            CCarAI::AddPoliceCarOccupants(car, false);
            m_nLastGenerationTime = CTimer::GetTimeInMS();
        }
        break;
    }
    case SETPIECE_1CAR_MEDIUM_SPEED:
        if (const auto* p = FindPlayerPed(); p->GetWantedLevel() < 2 || !FindPlayerVehicle()) {
            break;
        }


    }
}
