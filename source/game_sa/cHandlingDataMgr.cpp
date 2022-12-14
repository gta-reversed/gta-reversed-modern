#include "StdInc.h"

#include "cHandlingDataMgr.h"

void cHandlingDataMgr::InjectHooks() {
    RH_ScopedClass(cHandlingDataMgr);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(LoadHandlingData, 0x5BD830);
    RH_ScopedInstall(GetFlyingPointer, 0x6F52D0, {.reversed = false});
    RH_ScopedInstall(GetBoatPointer, 0x6F5300, {.reversed = false});
    RH_ScopedInstall(HasFrontWheelDrive, 0x6A0480, {.reversed = false});
    RH_ScopedInstall(HasRearWheelDrive, 0x6A04B0, {.reversed = false});
    RH_ScopedInstall(GetHandlingId, 0x6F4FD0, {.reversed = false});
    RH_ScopedInstall(ConvertDataToWorldUnits, 0x6F5010, {.reversed = false});
    RH_ScopedInstall(ConvertDataToGameUnits, 0x6F5080, {.reversed = false});
    RH_ScopedInstall(ConvertBikeDataToWorldUnits, 0x6F5240);
    RH_ScopedInstall(ConvertBikeDataToGameUnits, 0x6F5290);
    RH_ScopedInstall(FindExactWord, 0x006F4F30);
};

int32 tHandlingData::InitFromData(int32 id, const char* line) {
    m_nVehicleId = id;

    const auto n = sscanf(
        line,
        "%*s\t%f\t%f\t%f\t%f\t%f\t%f\t%hhu\t%f\t%f\t%f\t%hhu\t%f\t%f\t%f\t%c\t%c\t%f\t%f\t%hhu\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%x\t%x\t%hhu\t%hhu\t%hhu", // Skips name
        &m_fMass, // 1
        &m_fTurnMass,
        &m_fDragMult,

        &m_vecCentreOfMass.x, // 4
        &m_vecCentreOfMass.y,
        &m_vecCentreOfMass.z,

        &m_nPercentSubmerged, // 7

        &m_fTractionMultiplier, // 8
        &m_fTractionLoss,
        &m_fTractionBias,

        &m_transmissionData.m_nNumberOfGears, // 11
        &m_transmissionData.m_fMaxGearVelocity,
        &m_transmissionData.m_fEngineAcceleration,
        &m_transmissionData.m_fEngineInertia,
        &m_transmissionData.m_nDriveType,
        &m_transmissionData.m_nEngineType,

        &m_fBrakeDeceleration, // 18
        &m_fBrakeBias,
        &m_bABS,
        &m_fSteeringLock,
        &m_fSuspensionForceLevel,

        &m_fSuspensionDampingLevel, // 22
        &m_fSuspensionHighSpdComDamp,
        &m_fSuspensionUpperLimit,
        &m_fSuspensionLowerLimit,
        &m_fSuspensionBiasBetweenFrontAndRear,
        &m_fSuspensionAntiDiveMultiplier,
        &m_fSeatOffsetDistance,
        &m_fCollisionDamageMultiplier,

        &m_nMonetaryValue, // 31
        &m_nModelFlags,
        &m_nHandlingFlags,
        &m_nFrontLights,
        &m_nRearLights,
        &m_nAnimGroup
    );
    m_transmissionData.m_handlingFlags = m_nHandlingFlags;
    return n == 35 ? -1 : n;
}

int32 tBoatHandlingData::InitFromData(int32 id, const char* line) {
    m_nVehicleId = id;

    const auto n = sscanf(
        line,
        "%*s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f", // Skips name (first token)
        &m_fThrustY,
        &m_fThrustZ,
        &m_fThrustAppZ,
        &m_fAqPlaneForce,
        &m_fAqPlaneLimit,
        &m_fAqPlaneOffset,
        &m_fWaveAudioMult,

        &m_vecMoveRes.x,
        &m_vecMoveRes.y,
        &m_vecMoveRes.z,

        &m_vecTurnRes.x,
        &m_vecTurnRes.y,
        &m_vecTurnRes.z,

        &m_fLookLRBehindCamHeight
    );
    return n == 14 ? -1 : n;
}

int32 tFlyingHandlingData::InitFromData(int32 id, const char* line) {
    const auto n = sscanf(
        line,
        "%*s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f%*c\t%f\t%f\t%f\t%f\t%f\t%f\t%f", // Skips name(first token)
        &m_fThrust, // 1                                            ^^^ there's an extra `s` for the `RCRAIDER` that we have to ignore
        &m_fThrustFallOff,
        &m_fYaw,
        &m_fYawStab,
        &m_fSideSlip, // 5
        &m_fRoll,
        &m_fRollStab,
        &m_fPitch,
        &m_fPitchStab,
        &m_fFormLift, // 10
        &m_fAttackLift,
        &m_fGearUpR,
        &m_fGearDownL,
        &m_fWindMult,
        &m_fMoveRes, // 15

        &m_vecTurnRes.x, // 16
        &m_vecTurnRes.y,
        &m_vecTurnRes.z,

        &m_vecSpeedRes.x, // 19
        &m_vecSpeedRes.y,
        &m_vecSpeedRes.z
    );
    return n == 21 ? -1 : n;
}

int32 tBikeHandlingData::InitFromData(int32 id, const char* line) {
    const auto n = sscanf(
        line,
        "%*s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f", // Skips name (first token)
        &m_fLeanFwdCOM,
        &m_fLeanFwdForce,
        &m_fLeanBakCOM,
        &m_fLeanBakForce,
        &m_fMaxLean,
        &m_fFullAnimLean,
        &m_fDesLean,
        &m_fSpeedSteer,
        &m_fSlipSteer,
        &m_fNoPlayerCOMz,
        &m_fWheelieAng,
        &m_fStoppieAng,
        &m_fWheelieSteer,
        &m_fWheelieStabMult,
        &m_fStoppieStabMult
    );
    return n == 15 ? -1 : n;
}

void cHandlingDataMgr::LoadHandlingData() {
    CFileMgr::SetDir("DATA");
    const auto file = CFileMgr::OpenFile("HANDLING.CFG", "rb");
    CFileMgr::SetDir("");

    // Automatically closes file on function return
    const notsa::AutoCallOnDestruct closeFile{ [&] { CFileMgr::CloseFile(file); } };

    auto nLoadedHandlings{ 1u };

    // Get handling by scanning name from `line` using `scanNameFormat`, then calls `GetHandlingFn` to get the handling ptr
    const auto DoLoadHandling = [&, this](const char* line, auto GetHandlingFn) -> int32 {
        char name[32]{};
        if (sscanf_s(line, "%s", name, std::size(name)) != 1) {
            return 0;
        }
        const auto id = FindExactWord(name, &VehicleNames[0][0], std::size(VehicleNames[0]), std::size(VehicleNames));
        if (id == -1) {
            return -1; // Issue logged by `FindExactWord`, so no need to care about it here
        }
        const auto ret = std::invoke(GetHandlingFn, this, id)->InitFromData(id, line);
        if (ret == -1) {
            nLoadedHandlings++;
        }
        return ret;
    };

    auto nline{1u}, nLoadedVehHandlings{1u};
    for (auto l = CFileLoader::LoadLine(file); l; l = CFileLoader::LoadLine(file), nline++) {
        if (!strcmp(l, ";the end")) { // End of data
            return;
        }

        // Each function returns the number of tokens read on error otherwise -1
        const auto ret = [&] {
            switch (l[0]) {
            case ';': return -1; // Comment
            case '!': return DoLoadHandling(l + 1, &cHandlingDataMgr::GetBikeHandlingPointer);
            case '$': return DoLoadHandling(l + 1, &cHandlingDataMgr::GetFlyingPointer);
            case '%': return DoLoadHandling(l + 1, &cHandlingDataMgr::GetBoatPointer);
            case '^': return CVehicleAnimGroupData::LoadAGroupFromData(l);
            default:  break;
            }
            nLoadedVehHandlings++;
            return DoLoadHandling(l, &cHandlingDataMgr::GetVehiclePointer);
        }();
        if (ret != -1) {
            NOTSA_UNREACHABLE("Failed to process handling. [Line: {}; #Tokens Read: {}]", nline, ret);
        }
    }
    DEV_LOG("Successfully loaded {}x handlings for {}x vehicles!", nLoadedHandlings, nLoadedVehHandlings);
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

int32 cHandlingDataMgr::FindExactWord(const char* name, const char* nameTable, uint32 entrySize, uint32 entryCount) {
    for (auto i = 0u; i < entryCount; i++) {
        const auto entry = &nameTable[entrySize * i];
        if (!strncmp(name, entry, strlen(entry))) {
            return i;
        }
    }
    DEV_LOG("Vehicle name not found in table: {}", name);
    return -1;
}
