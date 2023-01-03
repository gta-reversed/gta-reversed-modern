/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Population.h"

float& CPopulation::PedDensityMultiplier = *(float*)0x8D2530;
int32& CPopulation::m_AllRandomPedsThisType = *(int32*)0x8D2534;
uint32& CPopulation::MaxNumberOfPedsInUse = *(uint32*)0x8D2538;
uint32& CPopulation::NumberOfPedsInUseInterior = *(uint32*)0x8D253C;
CLoadedCarGroup& CPopulation::m_LoadedBoats = *(CLoadedCarGroup*)0xC0E998;
CLoadedCarGroup& CPopulation::m_InAppropriateLoadedCars = *(CLoadedCarGroup*)0xC0E9C8;
CLoadedCarGroup& CPopulation::m_AppropriateLoadedCars = *(CLoadedCarGroup*)0xC0E9F8;
CLoadedCarGroup (&CPopulation::m_LoadedGangCars)[10] = *(CLoadedCarGroup(*)[10])0xC0EA28;
bool& CPopulation::bZoneChangeHasHappened = *(bool*)0xC0EC22;
uint8& CPopulation::m_CountDownToPedsAtStart = *(uint8*)0xC0EC23;
uint32& CPopulation::ms_nTotalMissionPeds = *(uint32*)0xC0EC24;
uint32& CPopulation::ms_nTotalPeds = *(uint32*)0xC0EC28;
uint32& CPopulation::ms_nTotalGangPeds = *(uint32*)0xC0EC2C;
uint32& CPopulation::ms_nTotalCivPeds = *(uint32*)0xC0EC30;
uint32& CPopulation::ms_nTotalCarPassengerPeds = *(uint32*)0xC0EC34;
uint32& CPopulation::ms_nNumDealers = *(uint32*)0xC0EC38;
std::array<uint32, TOTAL_GANGS>& CPopulation::ms_nNumGang = *(std::array<uint32, TOTAL_GANGS>*)0xC0EC3C;
uint32& CPopulation::ms_nNumEmergency = *(uint32*)0xC0EC64;
uint32& CPopulation::ms_nNumCop = *(uint32*)0xC0EC68;
uint32& CPopulation::ms_nNumCivFemale = *(uint32*)0xC0EC6C;
uint32& CPopulation::ms_nNumCivMale = *(uint32*)0xC0EC70;
uint16* CPopulation::m_nNumCarsInGroup = (uint16*)0xC0EC78;
uint16* CPopulation::m_nNumPedsInGroup = (uint16*)0xC0ECC0;
int16(*CPopulation::m_CarGroups)[23] = (int16(*)[23])0xC0ED38;
bool& CPopulation::m_bDontCreateRandomGangMembers = *(bool*)0xC0FCB2;
bool& CPopulation::m_bOnlyCreateRandomGangMembers = *(bool*)0xC0FCB3;
bool& CPopulation::m_bDontCreateRandomCops = *(bool*)0xC0FCB4;
bool& CPopulation::m_bMoreCarsAndFewerPeds = *(bool*)0xC0FCB5;
bool& CPopulation::bInPoliceStation = *(bool*)0xC0FCB6;
uint32& CPopulation::NumMiamiViceCops = *(uint32*)0xC0FCB8;
uint32& CPopulation::CurrentWorldZone = *(uint32*)0xC0FCBC;

void CPopulation::InjectHooks() {
    RH_ScopedClass(CPopulation);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(DoesCarGroupHaveModelId, 0x406F50, { .reversed = false });
    RH_ScopedGlobalInstall(ManagePed, 0x611FC0, { .reversed = false });
    RH_ScopedGlobalInstall(FindNumberOfPedsWeCanPlaceOnBenches, 0x612240, { .reversed = false });
    RH_ScopedGlobalInstall(RemoveAllRandomPeds, 0x6122C0, { .reversed = false });
    RH_ScopedGlobalInstall(TestRoomForDummyObject, 0x612320, { .reversed = false });
    RH_ScopedGlobalInstall(TestSafeForRealObject, 0x6123A0, { .reversed = false });
    RH_ScopedGlobalInstall(AddPed, 0x612710, { .reversed = false });
    RH_ScopedGlobalInstall(AddDeadPedInFrontOfCar, 0x612CD0, { .reversed = false });
    RH_ScopedGlobalInstall(ChooseCivilianOccupation, 0x612F90, { .reversed = false });
    RH_ScopedGlobalInstall(ChooseCivilianCoupleOccupations, 0x613180, { .reversed = false });
    RH_ScopedGlobalInstall(ChooseCivilianOccupationForVehicle, 0x613260, { .reversed = false });
    RH_ScopedGlobalInstall(CreateWaitingCoppers, 0x6133F0, { .reversed = false });
    RH_ScopedGlobalInstall(AddPedInCar, 0x613A00, { .reversed = false });
    RH_ScopedGlobalInstall(PlaceMallPedsAsStationaryGroup, 0x613CD0, { .reversed = false });
    RH_ScopedGlobalInstall(PlaceCouple, 0x613D60, { .reversed = false });
    RH_ScopedGlobalInstall(AddPedAtAttractor, 0x614210, { .reversed = false });
    RH_ScopedGlobalInstall(FindDistanceToNearestPedOfType, 0x6143E0, { .reversed = false });
    RH_ScopedGlobalInstall(PickGangCar, 0x614490, { .reversed = false });
    RH_ScopedGlobalInstall(PickRiotRoadBlockCar, 0x6144B0, { .reversed = false });
    RH_ScopedGlobalInstall(ConvertToRealObject, 0x614580);
    RH_ScopedGlobalInstall(ConvertToDummyObject, 0x614670);
    RH_ScopedGlobalInstall(AddToPopulation, 0x614720, { .reversed = false });
    RH_ScopedGlobalInstall(GeneratePedsAtAttractors, 0x615970, { .reversed = false });
    RH_ScopedGlobalInstall(GeneratePedsAtStartOfGame, 0x615C90, { .reversed = false });
    RH_ScopedGlobalInstall(ManageObject, 0x615DC0, { .reversed = false });
    RH_ScopedGlobalInstall(ManageDummy, 0x616000, { .reversed = false });
    RH_ScopedGlobalInstall(ManageAllPopulation, 0x6160A0, { .reversed = false });
    RH_ScopedGlobalInstall(ManagePopulation, 0x616190, { .reversed = false });
    RH_ScopedGlobalInstall(RemovePedsIfThePoolGetsFull, 0x616300, { .reversed = false });
    RH_ScopedGlobalInstall(ConvertAllObjectsToDummyObjects, 0x616420, { .reversed = false });
    RH_ScopedGlobalInstall(FindPedMultiplierMotorway, 0x611B80, { .reversed = false });
    RH_ScopedGlobalInstall(FindCarMultiplierMotorway, 0x611B60, { .reversed = false });
    RH_ScopedGlobalInstall(IsCorrectTimeOfDayForEffect, 0x611B20, { .reversed = false });
    RH_ScopedGlobalInstall(RemoveSpecificDriverModelsForCar, 0x6119D0, { .reversed = false });
    RH_ScopedGlobalInstall(FindPedRaceFromName, 0x5B6D40);
    RH_ScopedGlobalInstall(LoadPedGroups, 0x5BCFE0);
    RH_ScopedGlobalInstall(LoadCarGroups, 0x5BD1A0, { .reversed = false });
    RH_ScopedGlobalInstall(Initialise, 0x610E10, { .reversed = false });
    RH_ScopedGlobalInstall(Shutdown, 0x610EC0, { .reversed = false });
    RH_ScopedGlobalInstall(FindDummyDistForModel, 0x610ED0, { .reversed = false });
    RH_ScopedGlobalInstall(FindPedDensityMultiplierCullZone, 0x610F00, { .reversed = false });
    RH_ScopedGlobalInstall(RemovePed, 0x610F20);
    RH_ScopedGlobalInstall(ChoosePolicePedOccupation, 0x610F40, { .reversed = false });
    RH_ScopedGlobalInstall(ArePedStatsCompatible, 0x610F50, { .reversed = false });
    RH_ScopedGlobalInstall(PedMICanBeCreatedAtAttractor, 0x6110C0, { .reversed = false });
    RH_ScopedGlobalInstall(PedMICanBeCreatedAtThisAttractor, 0x6110E0, { .reversed = false });
    RH_ScopedGlobalInstall(PedMICanBeCreatedInInterior, 0x611450, { .reversed = false });
    RH_ScopedGlobalInstall(IsMale, 0x611470, { .reversed = false });
    RH_ScopedGlobalInstall(PopulateInterior, 0x616470, { .reversed = false });
    RH_ScopedGlobalInstall(IsFemale, 0x611490, { .reversed = false });
    RH_ScopedGlobalInstall(IsSkateable, 0x6114C0, { .reversed = false });
    RH_ScopedGlobalInstall(ChooseGangOccupation, 0x611550, { .reversed = false });
    RH_ScopedGlobalInstall(AddExistingPedInCar, 0x611560, { .reversed = false });
    RH_ScopedGlobalInstall(UpdatePedCount, 0x611570, { .reversed = false });
    RH_ScopedGlobalInstall(MoveCarsAndPedsOutOfAbandonedZones, 0x6116A0, { .reversed = false });
    RH_ScopedGlobalInstall(DealWithZoneChange, 0x6116B0, { .reversed = false });
    RH_ScopedGlobalInstall(PedCreationDistMultiplier, 0x6116C0, { .reversed = false });
    //RH_ScopedGlobalInstall(IsSunbather, 0x611760, { .reversed = false });
    RH_ScopedGlobalInstall(CanSolicitPlayerOnFoot, 0x611780, { .reversed = false });
    RH_ScopedGlobalInstall(CanSolicitPlayerInCar, 0x611790, { .reversed = false });
    RH_ScopedGlobalInstall(CanJeerAtStripper, 0x6117B0, { .reversed = false });
    RH_ScopedGlobalInstall(PlaceGangMembers, 0x6117D0, { .reversed = false });
    RH_ScopedGlobalInstall(LoadSpecificDriverModelsForCar, 0x6117F0, { .reversed = false });
    RH_ScopedGlobalInstall(FindSpecificDriverModelForCar_ToUse, 0x611900, { .reversed = false });
    RH_ScopedGlobalInstall(IsSecurityGuard, 0x6114B0, { .reversed = false });
    RH_ScopedGlobalInstall(Update, 0x616650);
}

// 0x5B6D40
ePedRace CPopulation::FindPedRaceFromName(const char* modelName) {
    for (size_t i{}; i < 2; i++) {
        switch (toupper(modelName[i])) {
        case 0:   return RACE_DEFAULT; // Not handled properly originally
        case 'B': return RACE_BLACK;
        case 'H': return RACE_HISPANIC;
        case 'O':
        case 'I': return RACE_ORIENTAL;
        case 'W': return RACE_WHITE;
        }
    }
    return RACE_DEFAULT;
}

// 0x5BCFE0
void CPopulation::LoadPedGroups() {
    CFileMgr::ChangeDir("\\DATA\\");
    const auto file = CFileMgr::OpenFile("PEDGRP.DAT", "r");
    CFileMgr::ChangeDir("\\");

    size_t currGrpIdx{}, lineno{1};
    for (;const auto l = CFileLoader::LoadLine(file); lineno++) { // Also replaces `,` with ` ` (space) (Important to know)
        uint16 npeds{};
        for (auto begin = l, end = l; *begin; begin = end) {
            begin = CFileLoader::FindFirstNonNullOrWS(begin);
            if (*begin == '#') {
                break;
            }
            end = CFileLoader::FindFirstNullOrWS(begin);
            if (begin == end) {
                break;
            }

#ifdef _DEBUG // See bottom of the outer loop for info
            if (currGrpIdx >= m_PedGroups.size()) {
                DEV_LOG("Data found past-the-end! This would crash the vanilla game! [Line: {}]", lineno);
                break;
            }
#endif

            // Originally this check was at the end of the loop
            // but we want to print a useful error message, so the
            // loop is let to do one more iteration before breaking
            // to see if there are any more models to be added
            if (npeds >= m_PedGroups[currGrpIdx].size()) {
                DEV_LOG("There are peds to be loaded, but there's no memory! [Group: {}]", currGrpIdx);
                break;
            }
            
            char modelName[256]{};
            strncpy_s(modelName, begin, end - begin);
            if (int32 pedModelIdx{ MODEL_INVALID }; CModelInfo::GetModelInfo(modelName, &pedModelIdx)) {
                m_PedGroups[currGrpIdx][npeds++] = pedModelIdx;
            } else {
                DEV_LOG("Model ({}) doesn't exist!", modelName);
            }
        }
        
        if (npeds == 0) {
            continue; // Blank line
        }
        DEV_LOG("Loaded ({}) peds into the group ({})", m_nNumPedsInGroup[currGrpIdx], currGrpIdx);

        // Only now set this
        m_nNumPedsInGroup[currGrpIdx] = npeds;

        // Fill the rest (unused slots) with a value
        rng::fill(m_PedGroups[currGrpIdx] | rng::views::drop(m_nNumPedsInGroup[currGrpIdx]), m_DefaultModelIDForUnusedSlot);

        // Only increment this if it wasn't a blank line
        currGrpIdx++;

#ifndef _DEBUG // In debug mode we let the loop go to check for past-the-end data (and report it)
        if (currGrpIdx == m_PedGroups.size()) {
            break; // No more data needed - This if kind of a bugfix too, as the original game would just keep going, and if there was anything after the last group it would just corrupt the memory :D
        }
#endif
    };

    if (currGrpIdx == m_PedGroups.size()) {
        DEV_LOG("PEDGRP.DAT has been loaded successfully! [#Groups Loaded: {}]", currGrpIdx);
    } else {
        NOTSA_UNREACHABLE("Missing group data in PEDGRP.DAT! [#Groups Loaded: {}/{}]", currGrpIdx, m_PedGroups.size());
    }

    CFileMgr::CloseFile(file);
}

// 0x5BD1A0
void CPopulation::LoadCarGroups() {
    ((void(__cdecl*)())0x5BD1A0)();
}

// 0x610E10
void CPopulation::Initialise() {
    ((void(__cdecl*)())0x610E10)();
}

// 0x610EC0
void CPopulation::Shutdown() {
    ((void(__cdecl*)())0x610EC0)();
}

// 0x610ED0
float CPopulation::FindDummyDistForModel(int32 modelIndex) {
    return ((float(__cdecl*)(int32))0x610ED0)(modelIndex);
}

// 0x610F00
float CPopulation::FindPedDensityMultiplierCullZone() {
    return ((float(__cdecl*)())0x610F00)();
}

// 0x610F20
void CPopulation::RemovePed(CPed* ped) {
    CWorld::Remove(ped);
    delete ped;
}

// 0x610F40
int32 CPopulation::ChoosePolicePedOccupation() {
    return 0;
}

// 0x610F50
bool CPopulation::ArePedStatsCompatible(int32 statType1, int32 statType2) {
    return ((bool(__cdecl*)(int32, int32))0x610F50)(statType1, statType2);
}

// 0x6110C0
bool CPopulation::PedMICanBeCreatedAtAttractor(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x6110C0)(modelIndex);
}

// 0x6110E0
bool CPopulation::PedMICanBeCreatedAtThisAttractor(int32 modelIndex, char* attrName) {
    return ((bool(__cdecl*)(int32, char*))0x6110E0)(modelIndex, attrName);
}

// 0x611450
bool CPopulation::PedMICanBeCreatedInInterior(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x611450)(modelIndex);
}

// 0x611470
bool CPopulation::IsMale(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x611470)(modelIndex);
}

// 0x611490
bool CPopulation::IsFemale(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x611490)(modelIndex);
}

// 0x6114B0
bool CPopulation::IsSecurityGuard(ePedType pedType) {
    return ((bool(__cdecl*)(ePedType))0x6114B0)(pedType);
}

// 0x6114C0
bool CPopulation::IsSkateable(const CVector& point) {
    return ((bool(__cdecl*)(const CVector&))0x6114C0)(point);
}

// 0x611550
int32 CPopulation::ChooseGangOccupation(int32 arg0) {
    return ((int32(__cdecl*)(int32))0x611550)(arg0);
}

// 0x611560
CPed* CPopulation::AddExistingPedInCar(CPed* ped, CVehicle* vehicle) {
    return ((CPed * (__cdecl*)(CPed*, CVehicle*))0x611560)(ped, vehicle);
}

// 0x611570
void CPopulation::UpdatePedCount(CPed* ped, uint8 updateState) {
    ((void(__cdecl*)(CPed*, uint8))0x611570)(ped, updateState);
}

// 0x6116A0
void CPopulation::MoveCarsAndPedsOutOfAbandonedZones() {
    ((void(__cdecl*)())0x6116A0)();
}

// 0x6116B0
void CPopulation::DealWithZoneChange(eLevelName arg0, eLevelName arg1, bool arg2) {
    ((void(__cdecl*)(eLevelName, eLevelName, bool))0x6116B0)(arg0, arg1, arg2);
}

// 0x6116C0
float CPopulation::PedCreationDistMultiplier() {
    return ((float(__cdecl*)())0x6116C0)();
}

// 0x611760
bool CPopulation::IsSunbather(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x611760)(modelIndex);
}

bool CPopulation::IsSunbather(CPed* ped) {
    return IsSunbather(ped->m_nModelIndex);
}

// 0x611780
bool CPopulation::CanSolicitPlayerOnFoot(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x611780)(modelIndex);
}

// 0x611790
bool CPopulation::CanSolicitPlayerInCar(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x611790)(modelIndex);
}

// 0x6117B0
bool CPopulation::CanJeerAtStripper(int32 modelIndex) {
    return ((bool(__cdecl*)(int32))0x6117B0)(modelIndex);
}

// 0x6117D0
void CPopulation::PlaceGangMembers(ePedType pedType, int32 arg1, const CVector& posn) {
    ((void(__cdecl*)(ePedType, int32, const CVector&))0x6117D0)(pedType, arg1, posn);
}

// 0x6117F0
void CPopulation::LoadSpecificDriverModelsForCar(int32 carModelIndex) {
    ((void(__cdecl*)(int32))0x6117F0)(carModelIndex);
}

// 0x611900
int32 CPopulation::FindSpecificDriverModelForCar_ToUse(int32 carModelIndex) {
    return ((int32(__cdecl*)(int32))0x611900)(carModelIndex);
}

// 0x6119D0
void CPopulation::RemoveSpecificDriverModelsForCar(int32 carModelIndex) {
    ((void(__cdecl*)(int32))0x6119D0)(carModelIndex);
}

// 0x611B20
bool CPopulation::IsCorrectTimeOfDayForEffect(const C2dEffect* effect) {
    return ((bool(__cdecl*)(const C2dEffect*))0x611B20)(effect);
}

// 0x611B60
float CPopulation::FindCarMultiplierMotorway() {
    return ((float(__cdecl*)())0x611B60)();
}

// 0x611B80
float CPopulation::FindPedMultiplierMotorway() {
    return ((float(__cdecl*)())0x611B80)();
}

// 0x611FC0
void CPopulation::ManagePed(CPed* ped, const CVector& playerPosn) {
    ((void(__cdecl*)(CPed*, const CVector&))0x611FC0)(ped, playerPosn);
}

// 0x612240
int32 CPopulation::FindNumberOfPedsWeCanPlaceOnBenches() {
    return ((int32(__cdecl*)())0x612240)();
}

// 0x6122C0
void CPopulation::RemoveAllRandomPeds() {
    ((void(__cdecl*)())0x6122C0)();
}

// 0x612320
bool CPopulation::TestRoomForDummyObject(CObject* object) {
    return ((bool(__cdecl*)(CObject*))0x612320)(object);
}

// 0x6123A0
bool CPopulation::TestSafeForRealObject(CDummyObject* dummyObject) {
    return ((bool(__cdecl*)(CDummyObject*))0x6123A0)(dummyObject);
}

// 0x612710
CPed* CPopulation::AddPed(ePedType pedType, uint32 modelIndex, const CVector& posn, bool makeWander) {
    return ((CPed * (__cdecl*)(ePedType, uint32, const CVector&, bool))0x612710)(pedType, modelIndex, posn, makeWander);
}

// 0x612CD0
CPed* CPopulation::AddDeadPedInFrontOfCar(const CVector& posn, CVehicle* vehicle) {
    return ((CPed * (__cdecl*)(const CVector&, CVehicle*))0x612CD0)(posn, vehicle);
}

// 0x612F90
int32 CPopulation::ChooseCivilianOccupation(bool male, bool female, int32 animType, int32 ignoreModelIndex, int32 statType, bool arg5, bool arg6, bool checkAttractor, char* attrName) {
    return ((int32(__cdecl*)(bool, bool, int32, int32, int32, bool, bool, bool, char*))0x612F90)(male, female, animType, ignoreModelIndex, statType, arg5, arg6, checkAttractor, attrName);
}

// 0x613180
void CPopulation::ChooseCivilianCoupleOccupations(int32& model1, int32& model2) {
    ((void(__cdecl*)(int32&, int32&))0x613180)(model1, model2);
}

// 0x613260
int32 CPopulation::ChooseCivilianOccupationForVehicle(bool male, CVehicle* vehicle) {
    return ((int32(__cdecl*)(bool, CVehicle*))0x613260)(male, vehicle);
}

// 0x6133F0
void CPopulation::CreateWaitingCoppers(CVector posn, float arg1) {
    ((void(__cdecl*)(CVector, float))0x6133F0)(posn, arg1);
}

// 0x613A00
CPed* CPopulation::AddPedInCar(CVehicle* vehicle, bool driver, int32 gangPedType, int32 seatNumber, bool male, bool criminal) {
    return ((CPed * (__cdecl*)(CVehicle*, bool, int32, int32, bool, bool))0x613A00)(vehicle, driver, gangPedType, seatNumber, male, criminal);
}

// 0x613CD0
void CPopulation::PlaceMallPedsAsStationaryGroup(const CVector& posn) {
    ((void(__cdecl*)(const CVector&))0x613CD0)(posn);
}

// 0x613D60
void CPopulation::PlaceCouple(ePedType pedType1, int32 modelIndex1, ePedType pedType2, int32 modelIndex2, CVector posn) {
    ((void(__cdecl*)(ePedType, int32, ePedType, int32, CVector))0x613D60)(pedType1, modelIndex1, pedType2, modelIndex2, posn);
}

// 0x614210
bool CPopulation::AddPedAtAttractor(int32 modelIndex, C2dEffect* attractor, CVector posn, CEntity* entity, int32 decisionMakerType) {
    return ((bool(__cdecl*)(int32, C2dEffect*, CVector, CEntity*, int32))0x614210)(modelIndex, attractor, posn, entity, decisionMakerType);
}

// 0x6143E0
float CPopulation::FindDistanceToNearestPedOfType(ePedType pedType, CVector posn) {
    return ((float(__cdecl*)(ePedType, CVector))0x6143E0)(pedType, posn);
}

// 0x614490
int32 CPopulation::PickGangCar(int32 carGroupID) {
    return ((int32(__cdecl*)(int32))0x614490)(carGroupID);
}

// 0x6144B0
int32 CPopulation::PickRiotRoadBlockCar() {
    return ((int32(__cdecl*)())0x6144B0)();
}

// 0x614580
void CPopulation::ConvertToRealObject(CDummyObject* dummyObject) {
    if (!CPopulation::TestSafeForRealObject(dummyObject))
        return;

    auto* obj = dummyObject->CreateObject();
    if (!obj)
        return;

    CWorld::Remove(dummyObject);
    dummyObject->m_bIsVisible = false;
    dummyObject->ResolveReferences();

    obj->SetRelatedDummy(dummyObject);
    CWorld::Add(obj);

    if (!IsGlassModel(obj) || CModelInfo::GetModelInfo(obj->m_nModelIndex)->IsGlassType2())
    {
        if (obj->m_nModelIndex == ModelIndices::MI_BUOY || obj->physicalFlags.bAttachedToEntity)
        {
            obj->SetIsStatic(false);
            obj->m_vecMoveSpeed.Set(0.0F, 0.0F, -0.001F);
            obj->physicalFlags.bTouchingWater = true;
            obj->AddToMovingList();
        }
    }
    else
    {
        obj->m_bIsVisible = false;
    }
}

// 0x614670
void CPopulation::ConvertToDummyObject(CObject* object) {
    auto* dummy = object->m_pDummyObject;
    if (dummy) {
        if (!CPopulation::TestRoomForDummyObject(object)) {
            return;
        }

        dummy->m_bIsVisible = true;
        dummy->UpdateFromObject(object);
    }

    if (object->IsObject()) {
        auto* mi = object->GetModelInfo()->AsAtomicModelInfoPtr();
        if (mi && mi->IsGlassType1()) {
            if (dummy) {
                dummy->m_bIsVisible = false;
            } else {
                assert(false && "FIX_BUGS: dummy == nullptr");
            }
        }
    }

    CWorld::Remove(object);
    delete object;
    if (dummy) {
        CWorld::Add(dummy);
    }
}

// 0x614720
bool CPopulation::AddToPopulation(float arg0, float arg1, float arg2, float arg3) {
    return ((bool(__cdecl*)(float, float, float, float))0x614720)(arg0, arg1, arg2, arg3);
}

// 0x615970
int32 CPopulation::GeneratePedsAtAttractors(CVector posn, float arg1, float arg2, float arg3, float arg4, int32 decisionMakerType, int32 numPeds) {
    return ((int32(__cdecl*)(CVector, float, float, float, float, int32, int32))0x615970)(posn, arg1, arg2, arg3, arg4, decisionMakerType, numPeds);
}

// 0x615C90
void CPopulation::GeneratePedsAtStartOfGame() {
    ((void(__cdecl*)())0x615C90)();
}

// 0x615DC0
void CPopulation::ManageObject(CObject* object, const CVector& posn) {
    ((void(__cdecl*)(CObject*, const CVector&))0x615DC0)(object, posn);
}

// 0x616000
void CPopulation::ManageDummy(CDummy* dummy, const CVector& posn) {
    ((void(__cdecl*)(CDummy*, const CVector&))0x616000)(dummy, posn);
}

// 0x6160A0
void CPopulation::ManageAllPopulation() {
    ((void(__cdecl*)())0x6160A0)();
}

// 0x616190
void CPopulation::ManagePopulation() {
    ((void(__cdecl*)())0x616190)();
}

// 0x616300
void CPopulation::RemovePedsIfThePoolGetsFull() {
    ((void(__cdecl*)())0x616300)();
}

// 0x616420
void CPopulation::ConvertAllObjectsToDummyObjects() {
    ((void(__cdecl*)())0x616420)();
}

// 0x616470
void CPopulation::PopulateInterior(int32 numPeds, CVector posn) {
    ((void(__cdecl*)(int32, CVector))0x616470)(numPeds, posn);
}

// 0x616650
void CPopulation::Update(bool generatePeds) {
    CurrentWorldZone = [] {
        switch (CWeather::WeatherRegion) {
        case WEATHER_REGION_DEFAULT:
        case WEATHER_REGION_LA:
        case WEATHER_REGION_DESERT:
            return 0;
        case WEATHER_REGION_SF:
            return 1;
        case WEATHER_REGION_LV:
            return 2;
        default:
            NOTSA_UNREACHABLE();
        }
    }();

    if (CReplay::Mode == MODE_PLAYBACK) {
        return;
    }

    ManagePopulation();
    RemovePedsIfThePoolGetsFull();

    if (m_CountDownToPedsAtStart) {
        if (--m_CountDownToPedsAtStart == 0) {
            GeneratePedsAtStartOfGame();
        }
        return;
    }

    ms_nTotalGangPeds = GetTotalNumGang();
    ms_nTotalCivPeds  = ms_nNumCivMale + ms_nNumCivFemale;
    ms_nTotalPeds     = ms_nTotalPeds + ms_nTotalGangPeds + ms_nNumCop + ms_nNumEmergency;

    if (CCutsceneMgr::IsCutsceneProcessing() || !generatePeds) {
        return;
    }

    const auto pcdm = PedCreationDistMultiplier();
    const auto gdm  = TheCamera.m_fGenerationDistMultiplier;
    const float dists[]{
        pcdm * gdm * 42.5f,
        pcdm * gdm * 50.5f,
        pcdm * 25.f - 10.f,
        pcdm * 25.f
    };

    if (AddToPopulation(dists[0], dists[1], dists[2], dists[3])) {
        GeneratePedsAtAttractors(
            FindPlayerCentreOfWorld(),
            dists[0], dists[1],
            dists[2], dists[3],
            CGame::CanSeeOutSideFromCurrArea() ? -1 : 7,
            true
        );
    }
}

bool CPopulation::DoesCarGroupHaveModelId(int32 carGroupId, int32 modelId)
{
    return plugin::CallAndReturn<bool, 0x406F50, int32, int32>(carGroupId, modelId);
}

uint32 CPopulation::GetTotalNumGang() {
    return std::accumulate(
        ms_nNumGang.begin(),
        ms_nNumGang.end(),
        0
    );
}
