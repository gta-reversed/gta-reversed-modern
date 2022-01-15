#include "StdInc.h"
#include "Garages.h"

void CGarages::InjectHooks() {
    // Static functions (21x)
    ReversibleHooks::Install("CGarages", "Init", 0x447120, &CGarages::Init);
    ReversibleHooks::Install("CGarages", "CloseHideOutGaragesBeforeSave", 0x44A170, &CGarages::CloseHideOutGaragesBeforeSave);
    ReversibleHooks::Install("CGarages", "PlayerArrestedOrDied", 0x449E60, &CGarages::PlayerArrestedOrDied);
    ReversibleHooks::Install("CGarages", "Init_AfterRestart", 0x448B60, &CGarages::Init_AfterRestart);
    ReversibleHooks::Install("CGarages", "AllRespraysCloseOrOpen", 0x448B30, &CGarages::AllRespraysCloseOrOpen);
    ReversibleHooks::Install("CGarages", "IsModelIndexADoor", 0x448AF0, &CGarages::IsModelIndexADoor);
    ReversibleHooks::Install("CGarages", "FindSafeHouseIndexForGarageType", 0x4489F0, &CGarages::FindSafeHouseIndexForGarageType);
    ReversibleHooks::Install("CGarages", "IsPointWithinHideOutGarage", 0x448900, &CGarages::IsPointWithinHideOutGarage);
    ReversibleHooks::Install("CGarages", "IsGarageDoorClosed", 0x447D30, &CGarages::IsGarageDoorClosed);
    ReversibleHooks::Install("CGarages", "Update", 0x44C8C0, &CGarages::Update);
    ReversibleHooks::Install("CGarages", "ActivateGarage", 0x447CD0, &CGarages::ActivateGarage);
    ReversibleHooks::Install("CGarages", "SetTargetCar", 0x447C40, &CGarages::SetTargetCar);
    ReversibleHooks::Install("CGarages", "TriggerMessage", 0x447B80, &CGarages::TriggerMessage);
    ReversibleHooks::Install("CGarages", "IsCarSprayable", 0x4479A0, &CGarages::IsCarSprayable);
    // ReversibleHooks::Install("CGarages", "PrintMessages", 0x447790, &CGarages::PrintMessages);
    // ReversibleHooks::Install("CGarages", "setGarageType", 0x4476D0, &CGarages::SetGarageType);
    // ReversibleHooks::Install("CGarages", "AddOne", 0x4471E0, &CGarages::AddOne);
    // ReversibleHooks::Install("CGarages", "Shutdown", 0x4471B0, &CGarages::Shutdown);
    // ReversibleHooks::Install("CGarages", "deactivateGarage", 0x447CB0, &CGarages::DeactivateGarage);
    // ReversibleHooks::Install("CGarages", "Save", 0x5D3160, &CGarages::Save);
    // ReversibleHooks::Install("CGarages", "getGarageNumberByName", 0x447680, &CGarages::GetGarageNumberByName);
}

// Static functions
// 0x447120
void CGarages::Init() {
    NumGarages = 0;
    MessageEndTime = 0;
    MessageStartTime = 0;
    PlayerInGarage = 0;
    BombsAreFree = 0;
    CarsCollected = 0;
    BankVansCollected = 0;
    PoliceCarsCollected = 0;
    CarTypesCollected = 0;
    CrushedCarId = 0;
    LastTimeHelpMessage = 0;
    // dword_96BFF8 = 0; - Never refernced
    CrushedCarId = -1;
    LastTimeHelpMessage = 0;
    LastGaragePlayerWasIn = -1;
    NoResprays = 0;

    for (auto& safeHouseCars : aCarsInSafeHouse) {
        for (auto& car : safeHouseCars) {
            car.m_wModelIndex = 0;
        }
    }
}

// 0x44A170
void CGarages::CloseHideOutGaragesBeforeSave() {
    for (auto& v : aGarages) {
        switch (v.m_nType) { // Perhaps this was some kind of function? Like `CGarage::IsHideOutGarage()`?
        case eGarageType::SAFEHOUSE_GANTON:
        case eGarageType::SAFEHOUSE_SANTAMARIA:
        case eGarageType::SAGEHOUSE_ROCKSHORE:
        case eGarageType::SAFEHOUSE_FORTCARSON:
        case eGarageType::SAFEHOUSE_VERDANTMEADOWS:
        case eGarageType::SAFEHOUSE_DILLIMORE:
        case eGarageType::SAFEHOUSE_PRICKLEPINE:
        case eGarageType::SAFEHOUSE_WHITEWOOD:
        case eGarageType::SAFEHOUSE_PALOMINOCREEK:
        case eGarageType::SAFEHOUSE_REDSANDSWEST:
        case eGarageType::SAFEHOUSE_ELCORONA:
        case eGarageType::SAFEHOUSE_MULHOLLAND:
        case eGarageType::SAFEHOUSE_CALTONHEIGHTS:
        case eGarageType::SAFEHOUSE_PARADISO:
        case eGarageType::SAFEHOUSE_DOHERTY:
        case eGarageType::SAFEHOUSE_HASHBURY:
        case eGarageType::HANGAR_ABANDONED_AIRPORT: {
            if (v.m_nDoorState != eGarageDoorState::GARAGE_DOOR_CLOSED) {
                v.m_nDoorState = eGarageDoorState::GARAGE_DOOR_CLOSED;
                v.StoreAndRemoveCarsForThisHideOut(GetStoredCarsInSafehouse(FindSafeHouseIndexForGarageType(v.m_nType)), 4);
                v.RemoveCarsBlockingDoorNotInside();
                v.m_fDoorPosition = 0.0f;
            }
            break;
        }
        }
    }
}

// 0x449E60
void CGarages::PlayerArrestedOrDied() {
    for (auto& v : aGarages) {
        if (v.m_nType != eGarageType::INVALID) {
            v.PlayerArrestedOrDied();
        }
    }

    MessageEndTime = 0;
    MessageStartTime = 0;
}

// 0x448B60
void CGarages::Init_AfterRestart() {
    if (NumGarages) {
        for (auto i = 0; i < NumGarages; i++) {
            auto& v = aGarages[i];
            v.m_nType = v.m_nOriginalType;
            v.InitDoorsAtStart();
            v.m_GarageAudio.Reset();
        }
    }

    CGarages::NoResprays = false;

    for (auto& safeHouseCars : aCarsInSafeHouse) { // TODO: Seems like inlined?
        for (auto& car : safeHouseCars) {
            car.m_wModelIndex = 0;
        }
    }
}

// 0x448B30
void CGarages::AllRespraysCloseOrOpen(bool bOpen) {
    if (NumGarages) {
        for (auto i = 0; i < NumGarages; i++) {
            auto& v = aGarages[i];
            if (v.m_nType == eGarageType::PAYNSPRAY) {
                v.m_nDoorState = bOpen ? eGarageDoorState::GARAGE_DOOR_OPEN : eGarageDoorState::GARAGE_DOOR_CLOSED;
            }
        }
    }
}

// 0x448AF0
bool CGarages::IsModelIndexADoor(int32 model) {
    if (model >= 0) {
        if (const auto MI = CModelInfo::GetModelInfo(model)) {
            if (const auto AMI = MI->AsAtomicModelInfoPtr()) {
                return AMI->IsGarageDoor();
            }
        }
    }
    return false;
}

// 0x4489F0
int32 CGarages::FindSafeHouseIndexForGarageType(eGarageType gtype) {
    switch (gtype)
    {
    case SAFEHOUSE_SANTAMARIA:
        return 1;
    case SAGEHOUSE_ROCKSHORE:
        return 2;
    case SAFEHOUSE_FORTCARSON:
        return 3;
    case SAFEHOUSE_VERDANTMEADOWS:
        return 4;
    case SAFEHOUSE_DILLIMORE:
        return 5;
    case SAFEHOUSE_PRICKLEPINE:
        return 6;
    case SAFEHOUSE_WHITEWOOD:
        return 7;
    case SAFEHOUSE_PALOMINOCREEK:
        return 8;
    case SAFEHOUSE_REDSANDSWEST:
        return 9;
    case SAFEHOUSE_ELCORONA:
        return 10;
    case SAFEHOUSE_MULHOLLAND:
        return 11;
    case IMPOUND_LS:
        return 12;
    case IMPOUND_SF:
        return 13;
    case IMPOUND_LV:
        return 14;
    case SAFEHOUSE_CALTONHEIGHTS:
        return 15;
    case SAFEHOUSE_PARADISO:
        return 16;
    case SAFEHOUSE_DOHERTY:
        return 17;
    case SAFEHOUSE_HASHBURY:
        return 18;
    case HANGAR_ABANDONED_AIRPORT:
        return 19;
    default:
        return 0;
    }
}

// 0x448900
bool CGarages::IsPointWithinHideOutGarage(const CVector & point) {
    for (auto& v : aGarages) {
        switch (v.m_nType) { // TODO: Same switch used in CloseHideOutGaragesBeforeSave. This is def. inlined.
        case eGarageType::SAFEHOUSE_GANTON:
        case eGarageType::SAFEHOUSE_SANTAMARIA:
        case eGarageType::SAGEHOUSE_ROCKSHORE:
        case eGarageType::SAFEHOUSE_FORTCARSON:
        case eGarageType::SAFEHOUSE_VERDANTMEADOWS:
        case eGarageType::SAFEHOUSE_DILLIMORE:
        case eGarageType::SAFEHOUSE_PRICKLEPINE:
        case eGarageType::SAFEHOUSE_WHITEWOOD:
        case eGarageType::SAFEHOUSE_PALOMINOCREEK:
        case eGarageType::SAFEHOUSE_REDSANDSWEST:
        case eGarageType::SAFEHOUSE_ELCORONA:
        case eGarageType::SAFEHOUSE_MULHOLLAND:
        case eGarageType::SAFEHOUSE_CALTONHEIGHTS:
        case eGarageType::SAFEHOUSE_PARADISO:
        case eGarageType::SAFEHOUSE_DOHERTY:
        case eGarageType::SAFEHOUSE_HASHBURY:
        case eGarageType::HANGAR_ABANDONED_AIRPORT: {
            if (v.IsPointInsideGarage(point))
                return true;
            break;
        }
        }
    }
    return false;
}

// 0x447D30
bool CGarages::IsGarageDoorClosed(int16 garageId) {
    return aGarages[garageId].m_nDoorState == eGarageDoorState::GARAGE_DOOR_CLOSED;
}

// 0x44C8C0
void CGarages::Update() {
    if (CReplay::Mode == eReplayMode::REPLAY_MODE_1 || CGameLogic::IsCoopGameGoingOn())
        return;
    
    uint32 i{};
    for (auto& v : aGarages) {
        v.Update(i++);
    }

    static uint32& lastUpdatedGarage = *(uint32*)0x96EA78;
    if (CTimer::GetFrameCounter() % 16 != 12)
        return;

    auto& garageToCheck = aGarages[lastUpdatedGarage++];
    if (lastUpdatedGarage >= std::size(aGarages))
        lastUpdatedGarage = 0;

    if (garageToCheck.m_nType == eGarageType::INVALID)
        return;

    // Originally they've clearly used an some kind of `abs` macro (probably to "optimize" it)... And failed miserably lol
    const auto camPos = TheCamera.GetPosition();
    if (   std::abs(garageToCheck.m_fPosMinX - camPos.x) < 40.f
        && std::abs(garageToCheck.m_fPosMinY - camPos.y) < 40.f
    ) {
        garageToCheck.TidyUpGarageClose();
    } else {
        garageToCheck.TidyUpGarage();
    }
}

// 0x447CD0
void CGarages::ActivateGarage(int16 garageId) {
    auto& v = aGarages[garageId];
    v.m_bInactive = false;
    if (   v.m_nType == eGarageType::UNKN_CLOSESONTOUCH
        && v.m_nDoorState != eGarageDoorState::GARAGE_DOOR_CLOSED
    ) {
        v.m_nDoorState = eGarageDoorState::GARAGE_DOOR_OPENING;
    }
}

// 0x447C40
void CGarages::SetTargetCar(int16 garageId, CVehicle* veh) {
    auto& v = aGarages[garageId];
    if (veh) {
        v.m_pTargetCar = veh;
        veh->RegisterReference(reinterpret_cast<CEntity**>(&v.m_pTargetCar));
        if (v.m_nDoorState == eGarageDoorState::GARAGE_DOOR_CLOSED_DROPPED_CAR)
            v.m_nDoorState = eGarageDoorState::GARAGE_DOOR_CLOSED;
    } else {
        // NOTE/TODO: They forgot to call `UnregisterReference` 
        v.m_pTargetCar = nullptr; 
    }
}

// 0x447B80
void CGarages::TriggerMessage(const char * tagMsg, int16 numInStr1, uint16 time, int16 numInStr2) {
    if (   strcmp(tagMsg, MessageIDString) // Different strings
        || CTimer::GetTimeInMS() < MessageStartTime
        || CTimer::GetTimeInMS() >= MessageEndTime
    ) {
        strcpy_s(MessageIDString, tagMsg);
        MessageStartTime = CTimer::GetTimeInMS();
    } else {
        if (CTimer::GetTimeInMS() - MessageStartTime <= 500)
            return;
        MessageStartTime = CTimer::GetTimeInMS() - 500;
    }
    MessageEndTime = MessageStartTime + time;
    MessageNumberInString = numInStr1;
    MessageNumberInString2 = numInStr2;
}

// 0x4479A0
bool CGarages::IsCarSprayable(CVehicle* veh) {
    if (veh->IsLawEnforcementVehicle() || veh->IsSubclassBMX())
        return false;

    switch (veh->m_nModelIndex) {
    case eModelID::MODEL_BUS:
    case eModelID::MODEL_COACH:
    case eModelID::MODEL_ARTICT1: // TODO: In the source it compares against -2, but the in the ASM comment it says `artict1`.. test it.
    case eModelID::MODEL_FIRETRUK:
    case eModelID::MODEL_AMBULAN:
        return false;
    }
    return true;
}

// 0x447790
void CGarages::PrintMessages() {
    plugin::Call<0x447790>();
}

// 0x4476D0
void CGarages::SetGarageType(int16 garageId, eGarageType type, int32 unused) {
    plugin::Call<0x4476D0, int16, eGarageType, int32>(garageId, type, unused);
}

// 0x4471E0
// Garage flags
// 0x1	door opens up and rotate
// 0x2	door goes in
// 0x4	camera follow players
void CGarages::AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, uint8 type, uint32 a10, char* name, uint32 argFlags) {
    return plugin::Call<0x4471E0, float, float, float, float, float, float, float, float, uint8, uint32, char*, uint32>(x1, y1, z1, frontX, frontY, x2, y2, z2,
                                                                                                                                        type, a10, name, argFlags);
}

// 0x4471B0
void CGarages::Shutdown() {
    return plugin::Call<0x4471B0>();
}

// 0x447CB0
void CGarages::DeactivateGarage(int16 grgIdx) {
    plugin::Call<0x447CB0>(grgIdx);
}

// 0x5D3160
bool CGarages::Save() {
    return plugin::CallAndReturn<bool, 0x5D3160>();
}

bool CGarages::Load() {
    return plugin::CallAndReturn<bool, 0x5D3270>();
}

int16 CGarages::FindGarageForObject(CObject* obj) {
    return plugin::CallAndReturn<int16, 0x44A240>(obj);
}

// 0x447680
int16 CGarages::GetGarageNumberByName(const char* name) {
    return plugin::CallAndReturn<int16, 0x447680>(name);
}
