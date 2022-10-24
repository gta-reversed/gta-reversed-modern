#include "StdInc.h"

#include "cHandlingDataMgr.h"

void cHandlingDataMgr::InjectHooks() {
    RH_ScopedClass(cHandlingDataMgr);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(LoadHandlingData, 0x5BD830, {.reversed = false});
    RH_ScopedInstall(GetFlyingPointer, 0x6F52D0, {.reversed = false});
    RH_ScopedInstall(GetBoatPointer, 0x6F5300, {.reversed = false});
    RH_ScopedInstall(HasFrontWheelDrive, 0x6A0480, {.reversed = false});
    RH_ScopedInstall(HasRearWheelDrive, 0x6A04B0, {.reversed = false});
    RH_ScopedInstall(GetHandlingId, 0x6F4FD0, {.reversed = false});
    RH_ScopedInstall(ConvertDataToWorldUnits, 0x6F5010, {.reversed = false});
    RH_ScopedInstall(ConvertDataToGameUnits, 0x6F5080, {.reversed = false});
    RH_ScopedInstall(ConvertBikeDataToWorldUnits, 0x6F5240);
    RH_ScopedInstall(ConvertBikeDataToGameUnits, 0x6F5290);
};

void cHandlingDataMgr::LoadHandlingData() {
    plugin::CallMethod<0x5BD830, cHandlingDataMgr*>(this);
}

tFlyingHandlingData* cHandlingDataMgr::GetFlyingPointer(uint8 handlingId) {
    return plugin::CallMethodAndReturn<tFlyingHandlingData*, 0x6F52D0, cHandlingDataMgr*, uint8>(this, handlingId);
}

tBoatHandlingData* cHandlingDataMgr::GetBoatPointer(uint8 handlingId) {
    return plugin::CallMethodAndReturn<tBoatHandlingData*, 0x6F5300, cHandlingDataMgr*, uint8>(this, handlingId);
}

bool cHandlingDataMgr::HasFrontWheelDrive(uint8 handlingId) {
    return plugin::CallMethodAndReturn<bool, 0x6A0480, cHandlingDataMgr*, uint8>(this, handlingId);
};

bool cHandlingDataMgr::HasRearWheelDrive(uint8 handlingId) {
    return plugin::CallMethodAndReturn<bool, 0x6A04B0, cHandlingDataMgr*, uint8>(this, handlingId);
}

// get handling id by name
// 0x6F4FD0
int32 cHandlingDataMgr::GetHandlingId(const char* name) {
    return plugin::CallMethodAndReturn<int32, 0x6F4FD0>(this, name);
}

// update some handling variables with some world-specific multipliers
// 0x6F5010
void cHandlingDataMgr::ConvertDataToWorldUnits(tHandlingData* handling) {
    plugin::CallMethod<0x6F5010, cHandlingDataMgr*, tHandlingData*>(this, handling);
}

// update some handling variables with some game-specific multipliers
// 0x6F5080
void cHandlingDataMgr::ConvertDataToGameUnits(tHandlingData* handling) {
    plugin::CallMethod<0x6F5080, cHandlingDataMgr*, tHandlingData*>(this, handling);
}

// 0x6F5240
void cHandlingDataMgr::ConvertBikeDataToWorldUnits(tBikeHandlingData* bikeHandling) {
    bikeHandling->m_fMaxLean = RadiansToDegrees(asin(bikeHandling->m_fMaxLean));
    bikeHandling->m_fFullAnimLean = RadiansToDegrees(bikeHandling->m_fFullAnimLean);
    bikeHandling->m_fWheelieAng = RadiansToDegrees(asin(bikeHandling->m_fWheelieAng));
    bikeHandling->m_fStoppieAng = RadiansToDegrees(asin(bikeHandling->m_fStoppieAng));
}

// 0x6F5290
void cHandlingDataMgr::ConvertBikeDataToGameUnits(tBikeHandlingData* bikeHandling) {
    bikeHandling->m_fMaxLean = sin(DegreesToRadians(bikeHandling->m_fMaxLean));
    bikeHandling->m_fFullAnimLean = DegreesToRadians(bikeHandling->m_fFullAnimLean);
    bikeHandling->m_fWheelieAng = sin(DegreesToRadians(bikeHandling->m_fWheelieAng));
    bikeHandling->m_fStoppieAng = sin(DegreesToRadians(bikeHandling->m_fStoppieAng));
}
