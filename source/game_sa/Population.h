/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eLevelName.h"
#include "ePedRace.h"

class CLoadedCarGroup;
class CPed;
class CDummy;
class CDummyObject;
class CZone;

enum eUpdatePedCounterState {
    UPDATE_PED_COUNTER_INCREASE = 0,
    UPDATE_PED_COUNTER_DECREASE = 1
};

// for the most part, pedGroupIds[0] is used, but in some cases
// it's used like this: pedGroupIds[CPopulation::CurrentWorldZone]
struct tPedGroupTranslationData {
    ePopcyclePedGroup pedGroupIds[3]{};
};
VALIDATE_SIZE(tPedGroupTranslationData, 0xC);

class CPopulation {
public:
    static float&  PedDensityMultiplier;
    static int32&  m_AllRandomPedsThisType;
    static uint32& MaxNumberOfPedsInUse;
    static uint32& NumberOfPedsInUseInterior;
    static inline tPedGroupTranslationData (&m_TranslationArray)[POPCYCLE_TOTAL_GROUPS] = *(tPedGroupTranslationData(*)[33])0x8D2540;
    static CLoadedCarGroup&          m_LoadedBoats;
    static CLoadedCarGroup&          m_InAppropriateLoadedCars;
    static CLoadedCarGroup&          m_AppropriateLoadedCars;
    static CLoadedCarGroup           (&m_LoadedGangCars)[10];
    static bool&                     bZoneChangeHasHappened;
    static uint8&                    m_CountDownToPedsAtStart;
    static uint32&                   ms_nTotalMissionPeds;
    static uint32&                   ms_nTotalPeds;
    static uint32&                   ms_nTotalGangPeds;
    static uint32&                   ms_nTotalCivPeds;
    static uint32&                   ms_nTotalCarPassengerPeds;
    static uint32&                   ms_nNumDealers;
    static std::array<uint32, TOTAL_GANGS>& ms_nNumGang;
    static uint32& ms_nNumEmergency;
    static uint32& ms_nNumCop;
    static uint32& ms_nNumCivFemale;
    static uint32& ms_nNumCivMale;
    // static uint16 m_nNumCarsInGroup[POPCYCLE_TOTAL_NUM_CARGROUPS] (34)
    static uint16* m_nNumCarsInGroup;
    // static uint16 m_nNumPedsInGroup[POPCYCLE_TOTAL_NUM_PEDGROUPS] (57)
    static uint16* m_nNumPedsInGroup;
    // static int16 m_CarGroups[POPCYCLE_TOTAL_NUM_CARGROUPS][23] (34)
    static int16 (*m_CarGroups)[23];
    static const uint16 m_DefaultModelIDForUnusedSlot = 2000; // means not loaded
    static bool&   m_bDontCreateRandomGangMembers;
    static bool&   m_bOnlyCreateRandomGangMembers;
    static bool&   m_bDontCreateRandomCops;
    static bool&   m_bMoreCarsAndFewerPeds;
    static bool&   bInPoliceStation;
    static uint32& NumMiamiViceCops;
    static uint32& CurrentWorldZone;

    /// Array of (possible) model IDs in a given popcycle group
    static inline auto& m_PedGroups = *(std::array<std::array<int16, 21>, POPCYCLE_TOTAL_PEDGROUPS>*)0xC0F358;

public:
    static void InjectHooks();
    // static functions

    // returns ePedRace value
    static ePedRace FindPedRaceFromName(const char* modelName);
    // loads pedgrp.dat
    static void LoadPedGroups();
    // loads cargrp.dat
    static void LoadCarGroups();
    // init variables at game init and reinit
    static void Initialise();
    // empty function
    static void  Shutdown();
    static float FindDummyDistForModel(int32 modelIndex);
    static float FindPedDensityMultiplierCullZone();
    // CWorld::Remove(ped); delete ped;
    static void RemovePed(CPed* ped);
    // returns 0
    static int32 ChoosePolicePedOccupation();
    static bool  ArePedStatsCompatible(int32 statType1, int32 statType2);
    static bool  PedMICanBeCreatedAtAttractor(int32 modelIndex);
    // checks if ped with specific model index can be created at script attractor
    static bool PedMICanBeCreatedAtThisAttractor(int32 modelIndex, char* attrName);
    static bool PedMICanBeCreatedInInterior(int32 modelIndex);
    // is model male
    static bool IsMale(int32 modelIndex);
    // is model female
    static bool IsFemale(int32 modelIndex);
    // returns false
    static bool IsSecurityGuard(ePedType pedType);
    // checks if surface at this point is skateable
    static bool IsSkateable(const CVector& point);
    // calls CGangs::ChooseGangPedModel(int32); parameter - gang id?
    static int32 ChooseGangOccupation(int32 arg0);
    // empty function, returns ped
    static CPed* AddExistingPedInCar(CPed* ped, CVehicle* vehicle);
    // updates ped counter, for updateState see eUpdatePedCounterState
    static void UpdatePedCount(CPed* ped, uint8 updateState);
    // empty function
    static void MoveCarsAndPedsOutOfAbandonedZones();
    // empty function
    static void DealWithZoneChange(eLevelName arg0, eLevelName arg1, bool arg2);
    // returns ped creation distance multiplier
    static float PedCreationDistMultiplier();
    static bool  IsSunbather(int32 modelIndex);
    static bool  IsSunbather(CPed* ped); // NOTSA
    // returns false
    static bool CanSolicitPlayerOnFoot(int32 modelIndex);
    // returns true if ped type is PED_TYPE_PROSTITUTE
    static bool CanSolicitPlayerInCar(int32 modelIndex);
    // returns true if ped type is PED_TYPE_CIVMALE
    static bool CanJeerAtStripper(int32 modelIndex);
    static void PlaceGangMembers(ePedType pedType, int32 arg1, const CVector& posn);
    static void LoadSpecificDriverModelsForCar(int32 carModelIndex);
    // returns ped model index
    static int32 FindSpecificDriverModelForCar_ToUse(int32 carModelIndex);
    static void  RemoveSpecificDriverModelsForCar(int32 carModelIndex);
    static bool  IsCorrectTimeOfDayForEffect(const C2dEffect* effect);
    // return CPopulation::m_bMoreCarsAndFewerPeds? 1.7f : 1.0f;
    static float FindCarMultiplierMotorway();
    // return 1.0f;
    static float FindPedMultiplierMotorway();
    static void  ManagePed(CPed* ped, const CVector& playerPosn);
    static int32 FindNumberOfPedsWeCanPlaceOnBenches();
    static void  RemoveAllRandomPeds();
    static bool  TestRoomForDummyObject(CObject* object);
    static bool  TestSafeForRealObject(CDummyObject* dummyObject);
    static CPed* AddPed(ePedType pedType, uint32 modelIndex, const CVector& posn, bool makeWander);
    // creates male01 ped in front of car?
    static CPed* AddDeadPedInFrontOfCar(const CVector& posn, CVehicle* vehicle);
    static int32 ChooseCivilianOccupation(bool male, bool female, int32 animType, int32 ignoreModelIndex, int32 statType, bool arg5, bool arg6, bool checkAttractor, char* attrName);
    static void  ChooseCivilianCoupleOccupations(int32& model1, int32& model2);
    static int32 ChooseCivilianOccupationForVehicle(bool male, CVehicle* vehicle);
    static void  CreateWaitingCoppers(CVector posn, float arg1);
    // Creates ped in a vehicle. gangPedType can be set to -1
    static CPed* AddPedInCar(CVehicle* vehicle, bool driver, int32 gangPedType, int32 seatNumber, bool male, bool criminal);
    static void  PlaceMallPedsAsStationaryGroup(const CVector& posn);
    static void  PlaceCouple(ePedType pedType1, int32 modelIndex1, ePedType pedType2, int32 modelIndex2, CVector posn);
    // Creates ped at attractor. decisionMakerType can be set to -1
    static bool  AddPedAtAttractor(int32 modelIndex, C2dEffect* attractor, CVector posn, CEntity* entity, int32 decisionMakerType);
    static float FindDistanceToNearestPedOfType(ePedType pedType, CVector posn);
    static int32 PickGangCar(int32 carGroupID);
    static int32 PickRiotRoadBlockCar();
    static void  ConvertToRealObject(CDummyObject* dummyObject);
    static void  ConvertToDummyObject(CObject* object);
    static bool  AddToPopulation(float arg0, float arg1, float arg2, float arg3);
    // returns number of generated peds?
    static int32 GeneratePedsAtAttractors(CVector posn, float arg1, float arg2, float arg3, float arg4, int32 decisionMakerType, int32 numPeds);
    static void GeneratePedsAtStartOfGame();
    static void ManageObject(CObject* object, const CVector& posn);
    static void ManageDummy(CDummy* dummy, const CVector& posn);
    static void ManageAllPopulation();
    static void ManagePopulation();
    static void RemovePedsIfThePoolGetsFull();
    static void ConvertAllObjectsToDummyObjects();
    static void PopulateInterior(int32 numPeds, CVector posn);
    static void Update(bool generatePeds);
    static bool DoesCarGroupHaveModelId(int32 carGroupId, int32 modelId);
    static uint32 GetTotalNumGang();

    static const auto& GetPedGroupsOfGroup(ePopcycleGroup popcycleGroup) { return m_TranslationArray[popcycleGroup].pedGroupIds; }
    static ePopcyclePedGroup GetPedGroupId(ePopcycleGroup popcycleGroup, size_t worldZone = 0) { return static_cast<ePopcyclePedGroup>(m_TranslationArray[popcycleGroup].pedGroupIds[worldZone]); }
    static ePopcyclePedGroup GetGangGroupId(eGangID gang, int32 worldZone = 0) { return static_cast<ePopcyclePedGroup>(m_TranslationArray[gang + POPCYCLE_GROUP_BALLAS].pedGroupIds[worldZone]); }
    static int32 GetNumPedsInGroup(ePopcycleGroup popcycleGroup, int32 worldZone) { return m_nNumPedsInGroup[GetPedGroupId(popcycleGroup, worldZone)]; }
    static int32 GetNumPedsInGroup(ePopcyclePedGroup pedGroup) { return m_nNumPedsInGroup[pedGroup]; }

    static auto GetModelsInPedGroup(ePopcyclePedGroup pedGroup) { return m_PedGroups[pedGroup] | rng::views::take((size_t)GetNumPedsInGroup(pedGroup)); }
    static int32 GetPedGroupModelId(ePopcyclePedGroup pedGroup, int32 slot) { return GetModelsInPedGroup(pedGroup)[slot]; } // Doing it like this for (out-of-range) debug checks 
};
