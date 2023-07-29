#include "StdInc.h"

#include "StuckCarCheck.h"

void CStuckCarCheck::InjectHooks() {
    RH_ScopedClass(CStuckCarCheck);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x4639E0);
    RH_ScopedInstall(AddCarToCheck, 0x465970, { .reversed = false });
    RH_ScopedInstall(AttemptToWarpVehicle, 0x463A60, { .reversed = false });
    RH_ScopedInstall(ClearStuckFlagForCar, 0x463C40);
    RH_ScopedInstall(HasCarBeenStuckForAWhile, 0x463C00, { .reversed = false });
    RH_ScopedInstall(IsCarInStuckCarArray, 0x463C70, { .reversed = false });
    RH_ScopedInstall(Process, 0x465680, { .reversed = false });
    RH_ScopedInstall(RemoveCarFromCheck, 0x463B80, { .reversed = false });
}

// 0x4639E0
void CStuckCarCheck::Init() {
    for (auto& car : m_aStuckCars) {
        ResetArrayElement(car);
    }
}

// 0x465970
void CStuckCarCheck::AddCarToCheck(int32 carHandle, float distance, uint32 time, uint8 a5, bool bStuck, bool bFlipped, bool bWarp, int8 pathId) {
    plugin::CallMethod<0x465970, CStuckCarCheck*, int32, float, uint32, uint8, bool, bool, bool, int8>(this, carHandle, distance, time, a5, bStuck, bFlipped, bWarp, pathId);
}

// 0x463A60
bool CStuckCarCheck::AttemptToWarpVehicle(CVehicle* vehicle, CVector* origin, float orientation) {
    return plugin::CallMethodAndReturn<bool, 0x463A60, CStuckCarCheck*, CVehicle*, CVector*, float>(this, vehicle, origin, orientation);
}

// 0x463C40
void CStuckCarCheck::ClearStuckFlagForCar(int32 carHandle) {
    for (auto& car : m_aStuckCars) {
        if (car.m_nCarHandle == carHandle) {
            car.m_bCarStuck = false;
            return; // NOTSA optimization
        }
    }
}

// 0x463C00
bool CStuckCarCheck::HasCarBeenStuckForAWhile(int32 carHandle) {
    return plugin::CallMethodAndReturn<bool, 0x463C00, CStuckCarCheck*, int32>(this, carHandle);

    for (auto& car : m_aStuckCars) {
        if (car.m_nCarHandle == carHandle && car.m_bCarStuck) {
            return true;
        }
    }
    return false;
}

// 0x463C70
bool CStuckCarCheck::IsCarInStuckCarArray(int32 carHandle) {
    return plugin::CallMethodAndReturn<bool, 0x463C70, CStuckCarCheck*, int32>(this, carHandle);

    for (auto& car : m_aStuckCars) {
        if (car.m_nCarHandle == carHandle) {
            return true;
        }
    }
    return false;
}

// 0x465680
void CStuckCarCheck::Process() {
    ZoneScoped;

    plugin::CallMethod<0x465680, CStuckCarCheck*>(this);
}

// 0x463B80
void CStuckCarCheck::RemoveCarFromCheck(int32 carHandle) {
    return plugin::CallMethod<0x463B80, CStuckCarCheck*, int32>(this, carHandle);

    for (auto& car : m_aStuckCars) {
        if (car.m_nCarHandle == carHandle) {
            ResetArrayElement(car);
        }
    }
}

// 0x463970 | refactored
void CStuckCarCheck::ResetArrayElement(uint16 carHandle) {
    ResetArrayElement(m_aStuckCars[carHandle]);
}

// NOTSA
void CStuckCarCheck::ResetArrayElement(tStuckCar& car) {
    car.m_vCarPos    = CVector(-5000.0f, -5000.0f, -5000.0f);
    car.m_nCarHandle = -1;
    car.m_nStartTime = -1;
    car.m_fDistance  = 0.0f;
    car.m_nStuckTime = 0;
    car.m_bCarStuck  = false;
    car.field_1D     = 0;
    car.m_bStuck     = false;
    car.m_bFlipped   = false;
    car.m_bbWarp     = false;
    car.m_nPathId     = 0;
}
