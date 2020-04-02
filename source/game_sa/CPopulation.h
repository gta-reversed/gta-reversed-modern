/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CLoadedCarGroup.h"
#include "CPed.h"
#include "CDummy.h"
#include "CDummyObject.h"
#include "CZone.h"

enum ePedRace {
    RACE_DEFAULT = 0,
    RACE_BLACK = 1,    // 'B'
    RACE_WHITE = 2,    // 'W'
    RACE_ORIENTAL = 3, // 'O', 'I'
    RACE_HISPANIC = 4  // 'H'
};

enum eUpdatePedCounterState {
    UPDATE_PED_COUNTER_INCREASE = 0,
    UPDATE_PED_COUNTER_DECREASE = 1
};

struct tPedGroupTranslationData {
    unsigned int pedGroupId;
    int field_4;
    int field_8;
};

class  CPopulation {
public:
    // static variables

    static float                     & PedDensityMultiplier;
    static int                       & m_AllRandomPedsThisType;
    static unsigned int              & MaxNumberOfPedsInUse;
    static unsigned int              & NumberOfPedsInUseInterior;
    // static tPedGroupTranslationData m_TranslationArray[33]
    static tPedGroupTranslationData  * m_TranslationArray;
    static CLoadedCarGroup           & m_LoadedBoats;
    static CLoadedCarGroup           & m_InAppropriateLoadedCars;
    static CLoadedCarGroup           & m_AppropriateLoadedCars;
    // static CLoadedCarGroup m_LoadedGangCars[11]
    static CLoadedCarGroup           * m_LoadedGangCars;
    static bool                      & bZoneChangeHasHappened;
    static unsigned char             & m_CountDownToPedsAtStart;
    static unsigned int              & ms_nTotalMissionPeds;
    static unsigned int              & ms_nTotalPeds;
    static unsigned int              & ms_nTotalGangPeds;
    static unsigned int              & ms_nTotalCivPeds;
    static unsigned int              & ms_nTotalCarPassengerPeds;
    static unsigned int              & ms_nNumDealers;
    // static unsigned int ms_nNumGang[10]
    static unsigned int              * ms_nNumGang;
    static unsigned int              & ms_nNumEmergency;
    static unsigned int              & ms_nNumCop;
    static unsigned int              & ms_nNumCivFemale;
    static unsigned int              & ms_nNumCivMale;
    // static unsigned short m_nNumCarsInGroup[POPCYCLE_TOTAL_NUM_CARGROUPS] (34)
    static unsigned short            * m_nNumCarsInGroup;
    // static unsigned short m_nNumPedsInGroup[POPCYCLE_TOTAL_NUM_PEDGROUPS] (57)
    static unsigned short            * m_nNumPedsInGroup;
    // static short m_CarGroups[POPCYCLE_TOTAL_NUM_CARGROUPS][23] (34)
    static short                     (* m_CarGroups )[23];
    // static short m_PedGroups[POPCYCLE_TOTAL_NUM_PEDGROUPS][21] (57)
    static short                     (* m_PedGroups )[21];
    static bool                      & m_bDontCreateRandomGangMembers;
    static bool                      & m_bOnlyCreateRandomGangMembers;
    static bool                      & m_bDontCreateRandomCops;
    static bool                      & m_bMoreCarsAndFewerPeds;
    static bool                      & bInPoliceStation;
    static unsigned int              & NumMiamiViceCops;
    static unsigned int              & CurrentWorldZone;

    // static functions

    // returns ePedRace value
    static int FindPedRaceFromName(char* modelName);
    // loads pedgrp.dat
    static void LoadPedGroups();
    // loads cargrp.dat
    static void LoadCarGroups();
    // init variables at game init and reinit
    static void Initialise();
    // empty function
    static void Shutdown();
    static float FindDummyDistForModel(int modelIndex);
    static float FindPedDensityMultiplierCullZone();
    // CWorld::Remove(ped); delete ped;
    static void RemovePed(CPed* ped);
    // returns 0
    static int ChoosePolicePedOccupation();
    static bool ArePedStatsCompatible(int statType1, int statType2);
    static bool PedMICanBeCreatedAtAttractor(int modelIndex);
    // checks if ped with specific model index can be created at script attractor
    static bool PedMICanBeCreatedAtThisAttractor(int modelIndex, char* attrName);
    static bool PedMICanBeCreatedInInterior(int modelIndex);
    // is model male
    static bool IsMale(int modelIndex);
    // is model female
    static bool IsFemale(int modelIndex);
    // returns false
    static bool IsSecurityGuard(ePedType pedType);
    // checks if surface at this point is skateable
    static bool IsSkateable(CVector const& point);
    // calls CGangs::ChooseGangPedModel(int); parameter - gang id?
    static void ChooseGangOccupation(int arg0);
    // empty function, returns ped
    static CPed* AddExistingPedInCar(CPed* ped, CVehicle* vehicle);
    // updates ped counter, for updateState see eUpdatePedCounterState
    static void UpdatePedCount(CPed* ped, unsigned char updateState);
    // empty function
    static void MoveCarsAndPedsOutOfAbandonedZones();
    // empty function
    static void DealWithZoneChange(eLevelName arg0, eLevelName arg1, bool arg2);
    // returns ped creation distance multiplier
    static float PedCreationDistMultiplier();
    static bool IsSunbather(int modelIndex);
    // returns false
    static bool CanSolicitPlayerOnFoot(int modelIndex);
    // returns true if ped type is PED_TYPE_PROSTITUTE
    static bool CanSolicitPlayerInCar(int modelIndex);
    // returns true if ped type is PED_TYPE_CIVMALE
    static bool CanJeerAtStripper(int modelIndex);
    static void PlaceGangMembers(ePedType pedType, int arg1, CVector const& posn);
    static void LoadSpecificDriverModelsForCar(int carModelIndex);
    // returns ped model index
    static int FindSpecificDriverModelForCar_ToUse(int carModelIndex);
    static void RemoveSpecificDriverModelsForCar(int carModelIndex);
    static bool IsCorrectTimeOfDayForEffect(C2dEffect const* effect);
    // return CPopulation::m_bMoreCarsAndFewerPeds? 1.7f : 1.0f;
    static float FindCarMultiplierMotorway();
    // return 1.0f;
    static float FindPedMultiplierMotorway();
    static void ManagePed(CPed* ped, CVector const& playerPosn);
    static int FindNumberOfPedsWeCanPlaceOnBenches();
    static void RemoveAllRandomPeds();
    static bool TestRoomForDummyObject(CObject* object);
    static bool TestSafeForRealObject(CDummyObject* dummyObject);
    static CPed* AddPed(ePedType pedType, unsigned int modelIndex, CVector const& posn, bool makeWander);
    // creates male01 ped in front of car?
    static CPed* AddDeadPedInFrontOfCar(CVector const& posn, CVehicle* vehicle);
    static int ChooseCivilianOccupation(bool male, bool female, int animType, int ignoreModelIndex, int statType, bool arg5, bool arg6, bool checkAttractor, char* attrName);
    static void ChooseCivilianCoupleOccupations(int& model1, int& model2);
    static int ChooseCivilianOccupationForVehicle(bool male, CVehicle* vehicle);
    static void CreateWaitingCoppers(CVector posn, float arg1);
    // Creates ped in a vehicle. gangPedType can be set to -1
    static CPed* AddPedInCar(CVehicle* vehicle, bool driver, int gangPedType, int seatNumber, bool male, bool criminal);
    static void PlaceMallPedsAsStationaryGroup(CVector const& posn);
    static void PlaceCouple(ePedType pedType1, int modelIndex1, ePedType pedType2, int modelIndex2, CVector posn);
    // Creates ped at attractor. decisionMakerType can be set to -1
    static bool AddPedAtAttractor(int modelIndex, C2dEffect* attractor, CVector posn, CEntity* entity, int decisionMakerType);
    static float FindDistanceToNearestPedOfType(ePedType pedType, CVector posn);
    static int PickGangCar(int carGroupID);
    static int PickRiotRoadBlockCar();
    static void ConvertToRealObject(CDummyObject* dummyObject);
    static void ConvertToDummyObject(CObject* object);
    static bool AddToPopulation(float arg0, float arg1, float arg2, float arg3);
    // returns number of generated peds?
    static int GeneratePedsAtAttractors(CVector posn, float arg1, float arg2, float arg3, float arg4, int decisionMakerType, int numPeds);
    static void GeneratePedsAtStartOfGame();
    static void ManageObject(CObject* object, CVector const& posn);
    static void ManageDummy(CDummy* dummy, CVector const& posn);
    static void ManageAllPopulation();
    static void ManagePopulation();
    static void RemovePedsIfThePoolGetsFull();
    static void ConvertAllObjectsToDummyObjects();
    static void PopulateInterior(int numPeds, CVector posn);
    static void Update(bool generatePeds);
};