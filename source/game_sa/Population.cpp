/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "Population.h"

//! Define this to have extra DEV_LOG's of CPopulation
#define EXTRA_DEBUG_LOGS

#ifdef EXTRA_DEBUG_LOGS
#define POP_DEV_LOG DEV_LOG
#else
#define POP_DEV_LOG(...)
#endif

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

    RH_ScopedGlobalInstall(FindPedRaceFromName, 0x5B6D40);

    RH_ScopedGlobalInstall(LoadPedGroups, 0x5BCFE0);
    RH_ScopedGlobalInstall(LoadCarGroups, 0x5BD1A0);

    RH_ScopedGlobalInstall(DoesCarGroupHaveModelId, 0x406F50, { .reversed = false });
    RH_ScopedGlobalInstall(ManagePed, 0x611FC0);
    RH_ScopedGlobalInstall(FindNumberOfPedsWeCanPlaceOnBenches, 0x612240);
    RH_ScopedGlobalInstall(RemoveAllRandomPeds, 0x6122C0);
    RH_ScopedGlobalInstall(TestRoomForDummyObject, 0x612320);
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
    RH_ScopedGlobalInstall(FindPedMultiplierMotorway, 0x611B80);
    RH_ScopedGlobalInstall(FindCarMultiplierMotorway, 0x611B60);
    RH_ScopedGlobalInstall(IsCorrectTimeOfDayForEffect, 0x611B20);
    RH_ScopedGlobalInstall(RemoveSpecificDriverModelsForCar, 0x6119D0);
    RH_ScopedGlobalInstall(Initialise, 0x610E10, { .reversed = false });
    RH_ScopedGlobalInstall(Shutdown, 0x610EC0, { .reversed = false });
    RH_ScopedGlobalInstall(FindDummyDistForModel, 0x610ED0);
    RH_ScopedGlobalInstall(FindPedDensityMultiplierCullZone, 0x610F00);
    RH_ScopedGlobalInstall(RemovePed, 0x610F20);
    RH_ScopedGlobalInstall(ChoosePolicePedOccupation, 0x610F40, { .reversed = false });
    RH_ScopedGlobalInstall(ArePedStatsCompatible, 0x610F50);
    RH_ScopedGlobalInstall(PedMICanBeCreatedAtAttractor, 0x6110C0);
    RH_ScopedGlobalInstall(PedMICanBeCreatedAtThisAttractor, 0x6110E0);
    RH_ScopedGlobalInstall(PedMICanBeCreatedInInterior, 0x611450);
    RH_ScopedGlobalInstall(IsMale, 0x611470, { .reversed = false });
    RH_ScopedGlobalInstall(PopulateInterior, 0x616470, { .reversed = false });
    RH_ScopedGlobalInstall(IsFemale, 0x611490, { .reversed = false });
    RH_ScopedGlobalInstall(IsSkateable, 0x6114C0);
    RH_ScopedGlobalInstall(ChooseGangOccupation, 0x611550);
    RH_ScopedGlobalInstall(AddExistingPedInCar, 0x611560);
    RH_ScopedGlobalInstall(UpdatePedCount, 0x611570);
    RH_ScopedGlobalInstall(MoveCarsAndPedsOutOfAbandonedZones, 0x6116A0);
    RH_ScopedGlobalInstall(DealWithZoneChange, 0x6116B0);
    RH_ScopedGlobalInstall(PedCreationDistMultiplier, 0x6116C0);
    RH_ScopedGlobalInstall(CanSolicitPlayerOnFoot, 0x611780);
    RH_ScopedGlobalInstall(CanSolicitPlayerInCar, 0x611790);
    RH_ScopedGlobalInstall(CanJeerAtStripper, 0x6117B0);
    RH_ScopedGlobalInstall(PlaceGangMembers, 0x6117D0);
    RH_ScopedGlobalInstall(LoadSpecificDriverModelsForCar, 0x6117F0);
    RH_ScopedGlobalInstall(FindSpecificDriverModelForCar_ToUse, 0x611900);
    RH_ScopedGlobalInstall(IsSecurityGuard, 0x6114B0, { .reversed = false });
    RH_ScopedGlobalInstall(Update, 0x616650);

    RH_ScopedGlobalOverloadedInstall(IsSunbather, "ModelID", 0x611760, bool(*)(eModelID));
    //RH_ScopedGlobalOverloadedInstall(IsSunbather, "Ped", 0x611760, bool(*)(CPed*));
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

//! NOTSA - Unified function to read pedgrp.dat/cargrp.dat
void LoadGroup(const char* fileName, auto& outModelsInGroup, auto& outNumOfModelsPerGroup) {
    CFileMgr::ChangeDir("\\DATA\\");
    const auto file = CFileMgr::OpenFile(fileName, "r");
    CFileMgr::ChangeDir("\\");

    POP_DEV_LOG("Loading `{}`...", fileName);

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
            if (currGrpIdx >= outModelsInGroup.size()) {
                POP_DEV_LOG("Data found past-the-end! This would crash the vanilla game! [Line: {}]", lineno);
                break;
            }
#endif

            // Originally this check was at the end of the loop
            // but we want to print a useful error message, so the
            // loop is let to do one more iteration before breaking
            // to see if there are any more models to be added
            if (npeds >= outModelsInGroup[currGrpIdx].size()) {
                POP_DEV_LOG("There are models to be added to the group, but there's no memory! [Group ID: {}; Line: {}]", currGrpIdx, lineno);
                break;
            }
            
            char modelName[256]{};
            strncpy_s(modelName, begin, end - begin);
            if (int32 pedModelIdx{ MODEL_INVALID }; CModelInfo::GetModelInfo(modelName, &pedModelIdx)) {
                assert(pedModelIdx != MODEL_PLAYER);
                outModelsInGroup[currGrpIdx][npeds++] = pedModelIdx;
            } else {
                DEV_LOG("Model ({}) doesn't exist! [Group ID: {}; Line: {}]", modelName, currGrpIdx, lineno);
            }
        }
        
        if (npeds == 0) {
            continue; // Blank line
        }

        //POP_DEV_LOG("Loaded ({}) models into the group ({})", outNumOfModelsPerGroup[currGrpIdx], currGrpIdx);

        // Only now set this
        outNumOfModelsPerGroup[currGrpIdx] = npeds;

        // Fill the rest (unused slots) with a value
        rng::fill(outModelsInGroup[currGrpIdx] | rng::views::drop(npeds), CPopulation::m_DefaultModelIDForUnusedSlot);
        assert(!notsa::contains(outModelsInGroup[currGrpIdx], 0));

        // Only increment this if it wasn't a blank line
        currGrpIdx++;
#ifndef _DEBUG // In debug mode we let the loop go to check for past-the-end data (and report it)
        if (currGrpIdx == outModelsInGroup.size()) {
            break; // No more data needed - This if kind of a bugfix too, as the original game would just keep going, and if there was anything after the last group it would just corrupt the memory :D
        }
#endif
    };

    if (currGrpIdx == outModelsInGroup.size()) {
        DEV_LOG("{} has been loaded successfully! [#Groups Loaded: {}]", fileName, currGrpIdx);
    } else {
        NOTSA_UNREACHABLE("Missing group data in {}! [#Groups Loaded: {}/{}]", fileName, currGrpIdx, outModelsInGroup.size());
    }

    CFileMgr::CloseFile(file);
}

// 0x5BCFE0
void CPopulation::LoadPedGroups() {
    LoadGroup("PEDGRP.DAT", m_PedGroups, m_nNumPedsInGroup);
}

// 0x5BD1A0
void CPopulation::LoadCarGroups() {
    LoadGroup("CARGRP.DAT", m_CarGroups, m_nNumCarsInGroup);
}

// 0x610E10
void CPopulation::Initialise() {
    ms_nNumCivMale = 0;
    ms_nNumCivFemale = 0;
    ms_nNumCop = 0;
    ms_nNumEmergency = 0;
    rng::fill(ms_nNumGang, 0);
    ms_nTotalCarPassengerPeds = 0;
    ms_nTotalCivPeds = 0;
    ms_nTotalGangPeds = 0;
    ms_nTotalPeds = 0;
    ms_nTotalMissionPeds = 0;
    m_CountDownToPedsAtStart = 5;
    bZoneChangeHasHappened = 0;
    PedDensityMultiplier = 1.0f;
    m_AllRandomPedsThisType = -1;
    MaxNumberOfPedsInUse = 25;
    NumberOfPedsInUseInterior = 40;
    bInPoliceStation = 0;
    m_bDontCreateRandomGangMembers = 0;
    m_bOnlyCreateRandomGangMembers = 0;
    m_bDontCreateRandomCops = 0;
    m_bMoreCarsAndFewerPeds = 0;
    LoadPedGroups();
    LoadCarGroups();
}

// 0x610EC0
void CPopulation::Shutdown() {
    /* nop */
}

// 0x610ED0
float CPopulation::FindDummyDistForModel(eModelID modelIndex) {
    return (modelIndex == ModelIndices::MI_SAMSITE || modelIndex == ModelIndices::MI_SAMSITE2)
        ? 750.f
        : 80.f;
}

// 0x610F00
float CPopulation::FindPedDensityMultiplierCullZone() {
    return CCullZones::FewerPeds()
        ? 0.6f
        : 1.f;
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
bool CPopulation::ArePedStatsCompatible(ePedStats st1, ePedStats st2) {
    for (auto stype : { st1, st2 }) {
        switch (stype) {
        case ePedStats::PLAYER:
        case ePedStats::COP:
        case ePedStats::MEDIC:
        case ePedStats::FIREMAN:
        case ePedStats::TRAMP_MALE:
        case ePedStats::TRAMP_FEMALE:
        case ePedStats::TOURIST:
        case ePedStats::PROSTITUTE:
        case ePedStats::CRIMINAL:
        case ePedStats::BUSKER:
        case ePedStats::TAXIDRIVER:
        case ePedStats::PSYCHO:
        case ePedStats::STEWARD:
        case ePedStats::SPORTSFAN:
        case ePedStats::SHOPPER:
        case ePedStats::OLDSHOPPER:
        case ePedStats::BEACH_GUY:
        case ePedStats::BEACH_GIRL:
        case ePedStats::SKATER:
        case ePedStats::STD_MISSION:
        case ePedStats::COWARD:
        case ePedStats::GANG1:
        case ePedStats::GANG2:
        case ePedStats::GANG3:
        case ePedStats::GANG4:
        case ePedStats::GANG5:
        case ePedStats::GANG6:
        case ePedStats::GANG7:
            return false;
        }
        return true;
    }
    const auto IsOldGuyOrGirl = [](ePedStats st) {
        switch (st) {
        case ePedStats::OLD_GUY:
        case ePedStats::OLD_GIRL:
            return true;
        }
        return false;
    };
    return !IsOldGuyOrGirl(st1) || IsOldGuyOrGirl(st2);
}

// 0x6110C0
bool CPopulation::PedMICanBeCreatedAtAttractor(eModelID modelIndex) {
    switch (CModelInfo::GetPedModelInfo(modelIndex)->GetPedType()) {
    case PED_TYPE_DEALER:
    case PED_TYPE_MEDIC:
    case PED_TYPE_FIREMAN:
    case PED_TYPE_CRIMINAL:
    case PED_TYPE_BUM:
    case PED_TYPE_PROSTITUTE:
        return false;
    }
    return true;
}

// 0x6110E0
bool CPopulation::PedMICanBeCreatedAtThisAttractor(eModelID modelId, const char* attrName) {
    if (!attrName) {
        return true;
    }

    const auto NameIsAnyOf = [&](auto... anyOfValues) {
        return (... || (_stricmp(attrName, anyOfValues) == 0));
    };

    const auto pedType = CModelInfo::GetPedModelInfo(modelId)->GetPedType();

    if (NameIsAnyOf("COPST", "COPLOOK", "BROWSE")) {
        return pedType == PED_TYPE_COP;
    }

    if (pedType == PED_TYPE_COP) {
        return false;
    }

    if (NameIsAnyOf("DANCER")) {
        switch (modelId) {
        case MODEL_BFYRI:
        case MODEL_BMYRI:
        case MODEL_BMYST:
        case MODEL_HFYRI:
        case MODEL_HMYRI:
        case MODEL_OFYST:
        case MODEL_OMOST:
        case MODEL_OMYRI:
        case MODEL_OMYST:
        case MODEL_WFYRI:
        case MODEL_WFYST:
        case MODEL_WMYRI:
        case MODEL_WMYST:
            return true;
        }
        return false;
    }

    if (NameIsAnyOf("BARGUY", "PEDROUL", "PEDCARD", "PEDSLOT")) {
        switch (modelId) {
        case MODEL_WMYCON:
        case MODEL_HMOGAR:
        case MODEL_WMYMECH:
        case MODEL_SBFYST:
        case MODEL_WMYSGRD:
        case MODEL_SWMYHP1:
        case MODEL_SWMYHP2:
        case MODEL_SWMOTR1:
        case MODEL_SBMOTR2SBMOTR2:
        case MODEL_SWMOTR2:
        case MODEL_SBMYTR3:
        case MODEL_SWMOTR3:
        case MODEL_SBMYST:
        case MODEL_WMYCONB:
        case MODEL_SOMYST:
        case MODEL_SBFOST:
        case MODEL_SOFOST:
        case MODEL_SOFYST:
        case MODEL_SOMOST:
        case MODEL_SWMOTR5:
        case MODEL_SWFOST:
        case MODEL_SWFYST:
        case MODEL_SWMOST:
        case MODEL_SWMOTR4:
            return false; // TODO/BUG: Is this correct? Shouldn't it return true?
        }
        return true;
    }

    if (NameIsAnyOf("STRIPW")) {
        switch (modelId) {
        case MODEL_VWFYST1:
        case MODEL_VBFYST2:
        case MODEL_VHFYST3:
        case MODEL_SBFYSTR:
        case MODEL_SWFYSTR:
            return true;
        }
        return false;
    }

    if (NameIsAnyOf("STRIPM")) {
        return pedType != PED_TYPE_CIVFEMALE;
    }

    return false;
}

// 0x611450
bool CPopulation::PedMICanBeCreatedInInterior(eModelID modelIndex) {
    switch (CModelInfo::GetPedModelInfo(modelIndex)->GetPedType()) {
    case PED_TYPE_COP:
    case PED_TYPE_GANG1:
    case PED_TYPE_GANG2:
    case PED_TYPE_GANG3:
    case PED_TYPE_GANG4:
    case PED_TYPE_GANG5:
    case PED_TYPE_GANG6:
    case PED_TYPE_GANG7:
    case PED_TYPE_GANG8:
    case PED_TYPE_GANG9:
    case PED_TYPE_GANG10:
    case PED_TYPE_DEALER:
    case PED_TYPE_MEDIC:
    case PED_TYPE_FIREMAN:
    case PED_TYPE_CRIMINAL:
    case PED_TYPE_BUM:
    case PED_TYPE_PROSTITUTE:
        return false;
    }
    return true;
}

// 0x611470
bool CPopulation::IsMale(eModelID modelIndex) {
    return CModelInfo::GetPedModelInfo(modelIndex)->GetPedType() == PED_TYPE_CIVMALE;
}

// 0x611490
bool CPopulation::IsFemale(eModelID modelIndex) {
    return CModelInfo::GetPedModelInfo(modelIndex)->GetPedType() == PED_TYPE_CIVFEMALE;
}

// 0x6114B0
bool CPopulation::IsSecurityGuard(ePedType pedType) {
    return false;
}

// 0x6114C0
bool CPopulation::IsSkateable(const CVector& point) {
    CColPoint cp{};
    CEntity* hitEntity{};
    CWorld::ProcessVerticalLine(point + CVector{ 0.f, 0.f, 2.f }, point.z - 2.f, cp, hitEntity, true);
    return hitEntity && g_surfaceInfos.IsSkateable(cp.m_nSurfaceTypeB);
}

// 0x611550
int32 CPopulation::ChooseGangOccupation(eGangID gangId) {
    return CGangs::ChooseGangPedModel(gangId);
}

// 0x611560 (Unused)
CPed* CPopulation::AddExistingPedInCar(CPed* ped, CVehicle* vehicle) {
    NOTSA_UNREACHABLE(); // Does nothing (At least not what the name suggests)
}

// 0x611570
void CPopulation::UpdatePedCount(CPed* ped, uint8 pedAddedOrRemoved) {
    if (pedAddedOrRemoved != ped->bHasBeenAddedToPopulation) {
        return;
    }

    ped->bHasBeenAddedToPopulation = !pedAddedOrRemoved;

    const auto DoOp = [&](auto& value) {
        if (pedAddedOrRemoved) {
            value--;
        } else {
            value++;
        }
    };

    switch (ped->m_nPedType) {
    case PED_TYPE_CIVMALE:
    case PED_TYPE_CRIMINAL:
        DoOp(ms_nNumCivMale);
        break;
    case PED_TYPE_CIVFEMALE:
    case PED_TYPE_PROSTITUTE:
        DoOp(ms_nNumCivFemale);
        break;
    case PED_TYPE_COP:
        DoOp(ms_nNumCop);
        break;
    case PED_TYPE_GANG1:
    case PED_TYPE_GANG2:
    case PED_TYPE_GANG3:
    case PED_TYPE_GANG4:
    case PED_TYPE_GANG5:
    case PED_TYPE_GANG6:
    case PED_TYPE_GANG7:
    case PED_TYPE_GANG8:
    case PED_TYPE_GANG9:
    case PED_TYPE_GANG10:
#ifdef FIX_BUGS
        DoOp(ms_nNumGang[ped->m_nPedType - PED_TYPE_GANG1]);
#else
        DoOp(ms_nNumGang[ped->m_nPedType]);
#endif
        break;
    case PED_TYPE_DEALER:
        DoOp(ms_nNumDealers);
        break;
    case PED_TYPE_MEDIC:
    case PED_TYPE_FIREMAN:
        DoOp(ms_nNumEmergency);
        break;
    }
}

// 0x6116A0
void CPopulation::MoveCarsAndPedsOutOfAbandonedZones() {
    /* nop */
}

// 0x6116B0
void CPopulation::DealWithZoneChange(eLevelName arg0, eLevelName arg1, bool arg2) {
    /* nop */
}

// 0x6116C0
float CPopulation::PedCreationDistMultiplier() {
    if (const auto veh = FindPlayerVehicle()) {
        return std::clamp(veh->m_vecMoveSpeed.Magnitude2D() - 0.1f + 1.f, 1.f, 1.5f);
    }
    return 1.f;
}

// 0x611760
bool CPopulation::IsSunbather(eModelID modelIndex) {
    switch (CModelInfo::GetPedModelInfo(modelIndex)->GetPedStatType()) {
    case ePedStats::BEACH_GUY:
    case ePedStats::BEACH_GIRL:
        return true;
    }
    return false;
}

bool CPopulation::IsSunbather(CPed* ped) {
    return IsSunbather(ped->GetModelID());
}

// 0x611780
bool CPopulation::CanSolicitPlayerOnFoot(eModelID modelIndex) {
    return false;
}

// 0x611790
bool CPopulation::CanSolicitPlayerInCar(eModelID modelIndex) {
    return CModelInfo::GetPedModelInfo(modelIndex)->GetPedType() == PED_TYPE_PROSTITUTE;
}

// 0x6117B0
bool CPopulation::CanJeerAtStripper(eModelID modelIndex) {
    return CModelInfo::GetPedModelInfo(modelIndex)->GetPedType() == PED_TYPE_CIVMALE;
}

// 0x6117D0
void CPopulation::PlaceGangMembers(ePedType pedType, uint32 numOfPeds, const CVector& posn) {
    CPedGroupPlacer{}.PlaceGroup(pedType, numOfPeds, posn, ePedGroupDefaultTaskAllocatorType::RANDOM);
}

//! NOTSA - Helper
void ProcessPossibleDriverModelsOfCar(eModelID carModelIndex, auto&& ProcessModel) {
    if (carModelIndex == MODEL_FREEWAY) {
        ProcessModel(MODEL_BIKERA);
        ProcessModel(MODEL_BIKERB);
    } else {
        const auto model = [&] {
            switch (carModelIndex) {
            case MODEL_STRETCH:     return MODEL_WMYCH;
            case MODEL_TAXI:
            case MODEL_CABBIE:      return (eModelID)(CStreaming::GetDefaultCabDriverModel());
            case MODEL_MRWHOOP:     return MODEL_WMOICE;
            case MODEL_SECURICA:    return MODEL_WMYSGRD;
            case MODEL_PIZZABOY:    return MODEL_WMYPIZZ;
            case MODEL_FREEWAY:     return MODEL_BIKERA;
            case MODEL_BMX:         return MODEL_WMYBMX;
            default:                return MODEL_INVALID;
        }}();
        if (model != MODEL_INVALID) {
            ProcessModel(model);
        }
    }
}

// 0x6117F0
void CPopulation::LoadSpecificDriverModelsForCar(eModelID carModelIndex) {
    ProcessPossibleDriverModelsOfCar(carModelIndex, [&](eModelID model) {
        CStreaming::RequestModel(model, STREAMING_KEEP_IN_MEMORY | STREAMING_GAME_REQUIRED);
    });
}

// 0x6119D0
void CPopulation::RemoveSpecificDriverModelsForCar(eModelID carModelIndex) {
    ProcessPossibleDriverModelsOfCar(carModelIndex, CStreaming::SetModelAndItsTxdDeletable);
}

// 0x611900
eModelID CPopulation::FindSpecificDriverModelForCar_ToUse(eModelID carModelIndex) {
    switch (carModelIndex) {
    case MODEL_STRETCH:  return MODEL_WMYCH;
    case MODEL_TAXI:
    case MODEL_CABBIE:   return (eModelID)(CStreaming::GetDefaultCabDriverModel());
    case MODEL_MRWHOOP:  return MODEL_WMOICE;
    case MODEL_SECURICA: return MODEL_WMYSGRD;
    case MODEL_PIZZABOY: return MODEL_WMYPIZZ;
    case MODEL_BMX:      return MODEL_WMYBMX;
    case MODEL_FREEWAY: {
        switch (CGeneral::GetRandomNumberInRange(0, 3)) {
        case 0:  return MODEL_BIKERA;
        case 1:  return MODEL_BIKERB;
        default: return MODEL_INVALID;
        }
    }
    }
    return MODEL_INVALID;
}

// 0x611B20
bool CPopulation::IsCorrectTimeOfDayForEffect(const C2dEffect* effect) {
    switch (effect->pedAttractor.m_nAttractorType) {
    case PED_ATTRACTOR_PIZZA:
    case PED_ATTRACTOR_SHELTER:
    case PED_ATTRACTOR_TRIGGER_SCRIPT:
    case PED_ATTRACTOR_LOOK_AT:
    case PED_ATTRACTOR_SCRIPTED:
    case PED_ATTRACTOR_PARK:
    case PED_ATTRACTOR_STEP:
        return true;
    }
    return CClock::GetIsTimeInRange(9, 20); // 9 is correct, because the function uses `>=` not `>`
}

// 0x611B60
float CPopulation::FindCarMultiplierMotorway() {
    return m_bMoreCarsAndFewerPeds
        ? 1.7f
        : 1.f;
}

// 0x611B80
float CPopulation::FindPedMultiplierMotorway() {
    return 1.f;
}

// 0x611FC0
void CPopulation::ManagePed(CPed* ped, const CVector& playerPosn) {
    if (ped->IsPlayer()) {
        return;
    }

    if (!ped->CanBeDeleted()) {
        return;
    }

    if (ped->bInVehicle) {
        return;
    }

    if (ped->m_pAttachedTo && ped->m_pAttachedTo->m_nType == ENTITY_TYPE_VEHICLE) {
        return;
    }

    // If pead is dead, possibly fade them out
    if (ped->IsStateDead()) {
        const auto delta = CTimer::GetTimeInMS() - ped->m_nDeathTimeMS;
        if (   delta > 30'000
            || CDarkel::FrenzyOnGoing() && delta > 15'000
            || CGangWars::GangWarFightingGoingOn() && delta > 8'000
        ) {
            ped->bFadeOut = true;
        }
    }

    // If we've faded the ped completely out, remove it
    if (ped->bFadeOut && CVisibilityPlugins::GetClumpAlpha(ped->m_pRwClump) == 0) {
        RemovePed(ped);
        return;
    }

    const auto pedsRemovalDist = [&] {
        const auto GetDist = [&] {
            return (ped->GetPosition() - playerPosn).Magnitude2D() * ped->m_fRemovalDistMultiplier;
        };
        if (IsPedTypeGang(ped->m_nPedType)) {
            return GetDist() - 30.f;
        } else if (ped->bDeadPedInFrontOfCar && ped->field_590) { // Never true, because `field_590` is always 0
            return 0.f;
        } else {
            return GetDist();
        }
    }() / PedCreationDistMultiplier(); // Simplify the conditions below by dividing here

    if (TheCamera.m_fGenerationDistMultiplier * (ped->bCullExtraFarAway ? 65.f : 54.5f) <= pedsRemovalDist) {
        if (ped->GetIsOnScreen()) {
            ped->bFadeOut = true;
        } else {
            RemovePed(ped);
        }
    } else if (pedsRemovalDist <= 25.f || ped->GetIsOnScreen()) { // From here on I did some truth table magic, and was able to remove some of the redudant code (So some of the code is missing)
        ped->m_nTimeTillWeNeedThisPed = CTimer::GetTimeInMS() + (ped->m_nPedType == PED_TYPE_COP ? 10'000 : 4'000);
    } else if (CTimer::GetTimeInMS() > ped->m_nTimeTillWeNeedThisPed) { // Ped not needed anymore
        const auto& activeCam = TheCamera.GetActiveCamera();
        switch (activeCam.m_nMode) {
        case MODE_SNIPER:
        case MODE_SNIPER_RUNABOUT:
        case MODE_CAMERA:
            return;
        }
        if (activeCam.m_bLookingLeft || activeCam.m_bLookingRight || activeCam.m_bLookingBehind) {
            return;
        }
        RemovePed(ped);
    }
}

// 0x612240
int32 CPopulation::FindNumberOfPedsWeCanPlaceOnBenches() {
    const auto baseNum = [] {
        if (CGame::CanSeeOutSideFromCurrArea()) {
            return NumberOfPedsInUseInterior;
        }
        return (uint32)(
              std::floor(std::min((float)MaxNumberOfPedsInUse, CPopCycle::m_NumOther_Peds))
            * PedDensityMultiplier
            * FindPedDensityMultiplierCullZone()
        );
    }();
    return baseNum - ms_nNumCivMale - ms_nNumCivFemale + 2;
}

// 0x6122C0
void CPopulation::RemoveAllRandomPeds() {
    for (auto& ped : GetPedPool()->GetAllValid()) {
        if (ped.CanBeDeleted()) {
            RemovePed(&ped);
        }
    }
}

// 0x612320
bool CPopulation::TestRoomForDummyObject(CObject* object) {
    int16 ncolliding{};
    CWorld::FindObjectsKindaColliding(
        object->GetBoundCentre(),
        object->GetModelInfo()->GetColModel()->GetBoundRadius(),
        false,
        &ncolliding,
        2,              // TODO: Why 2?
        nullptr,
        false,
        true,
        true,
        false,
        false
    );
    return ncolliding == 0;
}

// 0x6123A0
bool CPopulation::TestSafeForRealObject(CDummyObject* dummyObject) {
    return ((bool(__cdecl*)(CDummyObject*))0x6123A0)(dummyObject);
}

// 0x612710
CPed* CPopulation::AddPed(ePedType pedType, eModelID modelIndex, const CVector& posn, bool makeWander) {
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
void CPopulation::PlaceCouple(ePedType pedType1, eModelID modelIndex1, ePedType pedType2, eModelID modelIndex2, CVector posn) {
    ((void(__cdecl*)(ePedType, int32, ePedType, int32, CVector))0x613D60)(pedType1, modelIndex1, pedType2, modelIndex2, posn);
}

// 0x614210
bool CPopulation::AddPedAtAttractor(eModelID modelIndex, C2dEffect* attractor, CVector posn, CEntity* entity, int32 decisionMakerType) {
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

    ms_nTotalGangPeds = CalculateTotalNumGangPeds();
    ms_nTotalCivPeds  = ms_nNumCivMale + ms_nNumCivFemale;
    ms_nTotalPeds     = ms_nTotalCivPeds + ms_nTotalGangPeds + ms_nNumCop + ms_nNumEmergency;

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

// NOTSA
uint32 CPopulation::CalculateTotalNumGangPeds() {
    return notsa::accumulate(ms_nNumGang, 0u);
}
