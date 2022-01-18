#include "StdInc.h"

#include "Garages.h"

static uint32& LastUpdatedGarageId = *(uint32*)0x96EA78;

void CGarages::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CGarages", "Init", 0x447120, &CGarages::Init);
    Install("CGarages", "Init_AfterRestart", 0x448B60, &CGarages::Init_AfterRestart);
    Install("CGarages", "Shutdown", 0x4471B0, &CGarages::Shutdown);
    // Install("CGarages", "AddOne", 0x4471E0, &CGarages::AddOne);
    Install("CGarages", "CloseHideOutGaragesBeforeSave", 0x44A170, &CGarages::CloseHideOutGaragesBeforeSave);
    Install("CGarages", "PlayerArrestedOrDied", 0x449E60, &CGarages::PlayerArrestedOrDied);
    Install("CGarages", "AllRespraysCloseOrOpen", 0x448B30, &CGarages::AllRespraysCloseOrOpen);
    Install("CGarages", "IsModelIndexADoor", 0x448AF0, &CGarages::IsModelIndexADoor);
    Install("CGarages", "FindSafeHouseIndexForGarageType", 0x4489F0, &CGarages::FindSafeHouseIndexForGarageType);
    Install("CGarages", "FindGarageForObject", 0x4489F0, &CGarages::FindGarageForObject);
    Install("CGarages", "IsPointWithinHideOutGarage", 0x448900, &CGarages::IsPointWithinHideOutGarage);
    Install("CGarages", "IsGarageOpen", 0x447D00, &CGarages::IsGarageOpen);
    Install("CGarages", "IsGarageClosed", 0x447D30, &CGarages::IsGarageClosed);
    Install("CGarages", "IsCarSprayable", 0x4479A0, &CGarages::IsCarSprayable);
    Install("CGarages", "Update", 0x44C8C0, &CGarages::Update);
    Install("CGarages", "ActivateGarage", 0x447CD0, &CGarages::ActivateGarage);
    Install("CGarages", "DeactivateGarage", 0x447CB0, &CGarages::DeactivateGarage);
    Install("CGarages", "SetTargetCar", 0x447C40, &CGarages::SetTargetCar);
    Install("CGarages", "TriggerMessage", 0x447B80, &CGarages::TriggerMessage);
    Install("CGarages", "PrintMessages", 0x447790, &CGarages::PrintMessages);
    Install("CGarages", "SetGarageType", 0x4476D0, &CGarages::SetGarageType);
    Install("CGarages", "GetGarageNumberByName", 0x447680, &CGarages::GetGarageNumberByName);
    Install("CGarages", "Load", 0x5D3270, &CGarages::Load);
    Install("CGarages", "Save", 0x5D3160, &CGarages::Save);
}

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
    CarTypesCollected[0] = 0;
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

// 0x448B60
void CGarages::Init_AfterRestart() {
    if (NumGarages) {
        for (auto i = 0; i < NumGarages; i++) {
            auto& garage = aGarages[i];
            garage.m_nType = garage.m_nOriginalType;
            garage.InitDoorsAtStart();
            garage.m_GarageAudio.Reset();
        }
    }

    CGarages::NoResprays = false;

    for (auto& safeHouseCars : aCarsInSafeHouse) { // TODO: Seems like inlined?
        for (auto& car : safeHouseCars) {
            car.m_wModelIndex = 0;
        }
    }
}

// 0x4471B0
void CGarages::Shutdown() {
    for (auto& garage : aGarages) {
        garage.m_GarageAudio.Reset();
    }
}

// 0x4471E0
// Garage flags
// 0x1	door opens up and rotate
// 0x2	door goes in
// 0x4	camera follow players
// TODO...
void CGarages::AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, uint8 type, uint32 a10, char* name, uint32 argFlags) {
    return plugin::Call<0x4471E0, float, float, float, float, float, float, float, float, uint8, uint32, char*, uint32>(x1, y1, z1, frontX, frontY, x2, y2, z2, type, a10, name, argFlags);
}

// 0x44A170
void CGarages::CloseHideOutGaragesBeforeSave() {
    for (auto& garage : aGarages) {
        switch (garage.m_nType) { // Perhaps this was some kind of function? Like `CGarage::IsHideOutGarage()`?
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
            if (garage.m_nDoorState != eGarageDoorState::GARAGE_DOOR_CLOSED) {
                garage.m_nDoorState = eGarageDoorState::GARAGE_DOOR_CLOSED;
                garage.StoreAndRemoveCarsForThisHideOut(GetStoredCarsInSafehouse(FindSafeHouseIndexForGarageType(garage.m_nType)), 4);
                garage.RemoveCarsBlockingDoorNotInside();
                garage.m_fDoorPosition = 0.0f;
            }
            break;
        }
        }
    }
}

// 0x449E60
void CGarages::PlayerArrestedOrDied() {
    for (auto& garage : aGarages) {
        if (garage.m_nType != eGarageType::INVALID) {
            garage.PlayerArrestedOrDied();
        }
    }

    MessageEndTime = 0;
    MessageStartTime = 0;
}

// 0x448B30
void CGarages::AllRespraysCloseOrOpen(bool bOpen) {
    if (NumGarages) {
        for (auto i = 0; i < NumGarages; i++) {
            auto& garage = aGarages[i];
            if (garage.m_nType == eGarageType::PAYNSPRAY) {
                garage.m_nDoorState = bOpen ? eGarageDoorState::GARAGE_DOOR_OPEN : eGarageDoorState::GARAGE_DOOR_CLOSED;
            }
        }
    }
}

// 0x448AF0
bool CGarages::IsModelIndexADoor(int32 model) {
    if (model >= 0) {
        if (const auto mi = CModelInfo::GetModelInfo(model)) {
            if (const auto ami = mi->AsAtomicModelInfoPtr()) {
                return ami->IsGarageDoor();
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

// 0x44A240
int16 CGarages::FindGarageForObject(CObject* obj) {
    return plugin::CallAndReturn<int16, 0x44A240>(obj);
}

// 0x448900
bool CGarages::IsPointWithinHideOutGarage(const CVector& point) {
    for (auto& garage : aGarages) {
        switch (garage.m_nType) { // TODO: Same switch used in CloseHideOutGaragesBeforeSave. This is def. inlined.
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
            if (garage.IsPointInsideGarage(point))
                return true;
            break;
        }
        }
    }
    return false;
}

// 0x447D00
bool CGarages::IsGarageOpen(int16 garageId) {
    switch (aGarages[garageId].m_nDoorState) {
    case GARAGE_DOOR_OPEN:
    case GARAGE_DOOR_WAITING_PLAYER_TO_EXIT:
        return true;
    }
    return false;
}

// 0x447D30
bool CGarages::IsGarageClosed(int16 garageId) {
    return aGarages[garageId].m_nDoorState == eGarageDoorState::GARAGE_DOOR_CLOSED;
}

// 0x4479A0
bool CGarages::IsCarSprayable(CVehicle* vehicle) {
    if (vehicle->IsLawEnforcementVehicle() || vehicle->IsSubclassBMX())
        return false;

    switch (vehicle->m_nModelIndex) {
    case eModelID::MODEL_BUS:
    case eModelID::MODEL_COACH:
    /* TODO:
    * In the source it compares against -2, but the in the ASM comment it says `artict1`
    * artict1 is Articulated Trailer which by logic cannot to sprayed due big size, but who know..
    * original code also disallow artict1 to be sprayed (tested)
    */
    case eModelID::MODEL_ARTICT1: // 
    case eModelID::MODEL_FIRETRUK:
    case eModelID::MODEL_AMBULAN:
        return false;
    }
    return true;
}

// 0x44C8C0
void CGarages::Update() {
    if (CReplay::Mode == eReplayMode::REPLAY_MODE_1 || CGameLogic::IsCoopGameGoingOn())
        return;
    
    uint32 i{};
    for (auto& garage : aGarages) {
        garage.Update(i++);
    }

    if (CTimer::GetFrameCounter() % 16 != 12)
        return;

    auto& garageToCheck = aGarages[LastUpdatedGarageId++];
    if (LastUpdatedGarageId >= std::size(aGarages))
        LastUpdatedGarageId = 0;

    if (garageToCheck.m_nType == eGarageType::INVALID)
        return;

    // Originally they've clearly used an some kind of `abs` macro (probably to "optimize" it)... And failed miserably lol
    const auto camPos = TheCamera.GetPosition();
    if (   std::abs(garageToCheck.m_fLeftCoord - camPos.x) < 40.f
        && std::abs(garageToCheck.m_fFrontCoord - camPos.y) < 40.f
    ) {
        garageToCheck.TidyUpGarageClose();
    } else {
        garageToCheck.TidyUpGarage();
    }
}

// 0x447CD0
void CGarages::ActivateGarage(int16 garageId) {
    auto& garage = aGarages[garageId];
    garage.m_bInactive = false;
    if (   garage.m_nType == eGarageType::UNKN_CLOSESONTOUCH
        && garage.m_nDoorState != eGarageDoorState::GARAGE_DOOR_CLOSED
    ) {
        garage.m_nDoorState = eGarageDoorState::GARAGE_DOOR_OPENING;
    }
}

// 0x447CB0
void CGarages::DeactivateGarage(int16 garageId) {
    aGarages[garageId].m_bInactive = true;
}

// 0x447C40
void CGarages::SetTargetCar(int16 garageId, CVehicle* vehicle) {
    auto& garage = aGarages[garageId];
    if (vehicle) {
        garage.m_pTargetCar = vehicle;
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&garage.m_pTargetCar));
        if (garage.m_nDoorState == eGarageDoorState::GARAGE_DOOR_CLOSED_DROPPED_CAR)
            garage.m_nDoorState = eGarageDoorState::GARAGE_DOOR_CLOSED;
    } else {
#if FIX_BUGS
        // NOTE/TODO: They forgot to call `UnregisterReference`
#endif
        garage.m_pTargetCar = nullptr;
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

// 0x447790
void CGarages::PrintMessages() {
    if (   CTimer::GetTimeInMS() < MessageStartTime
        || CTimer::GetTimeInMS() >= MessageEndTime
    ) {
        // Time over
        MessageIDString[0] = 0;
        return;
    }

    // Draw it
    CFont::SetScale(SCREEN_WIDTH_UNIT * 0.5f, SCREEN_HEIGHT_UNIT * 1.4f);
    CFont::SetProportional(true);
    CFont::SetBackground(false, false);
    CFont::SetCentreSize(SCREEN_WIDTH - SCREEN_WIDTH_UNIT * 230.f);
    CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
    CFont::SetFontStyle(eFontStyle::FONT_MENU);
    CFont::SetColor(HudColour.GetRGB(eHudColours::HUD_COLOUR_LIGHT_BLUE));
    CFont::SetEdge(2);
    CFont::SetDropColor({ 0, 0, 0, 255 });

    const auto DrawFormattedString = [&](auto... formatArgs) {
        CMessages::InsertNumberInString(TheText.Get(MessageIDString), formatArgs..., gGxtString);
        CFont::PrintString(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT_UNIT * 155.f, gGxtString);
    };

    if (MessageNumberInString < 0) {
        if (MessageNumberInString2 < 0) {
            CFont::PrintString(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT_UNIT * 155.f, TheText.Get(MessageIDString));
        } else {
            DrawFormattedString(MessageNumberInString2, -1, -1, -1, -1, -1);
        }
    } else {
        DrawFormattedString(MessageNumberInString, MessageNumberInString2, -1, -1, -1, -1);
    }
}

// 0x4476D0
void CGarages::SetGarageType(int16 garageId, eGarageType type, int32 unused) {
    auto& garage = aGarages[garageId];
    garage.m_nType = type;
    switch (type) {
    case eGarageType::BOMBSHOP_TIMED:
    case eGarageType::BOMBSHOP_ENGINE:
    case eGarageType::BOMBSHOP_REMOTE:
    case eGarageType::PAYNSPRAY: {
        garage.m_nDoorState = eGarageDoorState::GARAGE_DOOR_CLOSED;
        garage.m_fDoorPosition = 0.f;
        break;
    }
    case eGarageType::BURGLARY: {
        break; // NOP
    }
    default: {
        if (garage.m_nDoorState == eGarageDoorState::GARAGE_DOOR_CLOSED) {
            garage.m_nDoorState = eGarageDoorState::GARAGE_DOOR_OPEN;
            garage.m_fDoorPosition = 1.f;
        }
        break;
    }
    }
}

// 0x447680
int16 CGarages::GetGarageNumberByName(const char* name) {
    for (auto i = 0; i < NumGarages; i++) {
        const auto& garage = aGarages[i];
        if (stricmp(garage.m_anName, name) == 0)
            return i;
    }
    return -1;
}

bool CGarages::Load() {
    LoadDataFromBuffer(NumGarages);
    LoadDataFromBuffer(BombsAreFree);
    LoadDataFromBuffer(RespraysAreFree);
    LoadDataFromBuffer(NoResprays);
    LoadDataFromBuffer(CarsCollected);
    LoadDataFromBuffer(BankVansCollected);
    LoadDataFromBuffer(PoliceCarsCollected);

    for (auto v : CarTypesCollected) {
        LoadDataFromBuffer(v);
    }

    LoadDataFromBuffer(LastTimeHelpMessage);

    // NOTE: Here they messsed up the order of loops
    //       C/C++ is row-major, so, the row loop should've been the outer one..
    //       This is important, because the array isn't accessed contiguously
    //       Which means the data isn't saved contiguously either, so watch out for that.
    for (auto c = 0; c < 4; c++) {
        for (auto r = 0; r < 20; r++) {
            LoadDataFromBuffer(aCarsInSafeHouse[r][c]);
        }
    }

    for (auto i = 0; i < NumGarages; i++) {
        CSaveGarage sg{};
        LoadDataFromBuffer(sg);
        sg.CopyGarageOutOfSaveGarage(aGarages[i]);
    }

    MessageEndTime = 0;
    MessageStartTime = 0;
    bCamShouldBeOutside = 0;

    return true;
}

// todo: fix Update()
// 0x5D3160
bool CGarages::Save() {
    SaveToBuffer(NumGarages);
    SaveToBuffer(BombsAreFree);
    SaveToBuffer(RespraysAreFree);
    SaveToBuffer(NoResprays);
    SaveToBuffer(CarsCollected);
    SaveToBuffer(BankVansCollected);
    SaveToBuffer(PoliceCarsCollected);

    for (auto carType : CarTypesCollected) {
        SaveToBuffer(carType);
    }

    SaveToBuffer(LastTimeHelpMessage);

    // NOTE: Here they messsed up the order of loops
    //       C/C++ is row-major, so, the row loop should've been the outer one..
    //       This is important, because the array isn't accessed contiguously
    //       Which means the data isn't saved contiguously either, so watch out for that.
    for (auto c = 0; c < 4; c++) {
        for (auto r = 0; r < 20; r++) {
            SaveToBuffer(aCarsInSafeHouse[r][c]); 
        }
    }

    for (auto i = 0; i < NumGarages; i++) {
        CSaveGarage sg{};
        sg.CopyGarageIntoSaveGarage(aGarages[i]);
        SaveToBuffer(sg);
    }

    return true;
}
