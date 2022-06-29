/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CZoneInfo;
class CZone;

enum ePedType : uint32;

// used in CPopCycle::m_nPercTypeGroup
enum ePopcycleGroupPerc {
    POPCYCLE_GROUP_PERC_WORKERS = 0,
    POPCYCLE_GROUP_PERC_BUSINESS,
    POPCYCLE_GROUP_PERC_CLUBBERS,
    POPCYCLE_GROUP_PERC_FARMERS,
    POPCYCLE_GROUP_PERC_BEACHFOLK,
    POPCYCLE_GROUP_PERC_PARKFOLK,
    POPCYCLE_GROUP_PERC_CASUAL_RICH,
    POPCYCLE_GROUP_PERC_CASUAL_AVERAGE,
    POPCYCLE_GROUP_PERC_CASUAL_POOR,
    POPCYCLE_GROUP_PERC_PROZZIES,
    POPCYCLE_GROUP_PERC_CRIMIMALS,
    POPCYCLE_GROUP_PERC_GOLFERS,
    POPCYCLE_GROUP_PERC_SERVANTS,
    POPCYCLE_GROUP_PERC_AIRCREW,
    POPCYCLE_GROUP_PERC_ENTERTAINERS,
    POPCYCLE_GROUP_PERC_OOT_FACT, // means out of town factory
    POPCYCLE_GROUP_PERC_DESERTFOLK,
    POPCYCLE_GROUP_PERC_AIRCREW_RUNWAY,
    POPCYCLE_TOTAL_GROUP_PERCS
};

// used in CPopulation::m_TranslationArray
enum ePopcycleGroup {
    POPCYCLE_GROUP_WORKERS = 0,
    POPCYCLE_GROUP_BUSINESS,
    POPCYCLE_GROUP_CLUBBERS,
    POPCYCLE_GROUP_FARMERS,
    POPCYCLE_GROUP_BEACHFOLK,
    POPCYCLE_GROUP_PARKFOLK,
    POPCYCLE_GROUP_CASUAL_RICH,
    POPCYCLE_GROUP_CASUAL_AVERAGE,
    POPCYCLE_GROUP_CASUAL_POOR,
    POPCYCLE_GROUP_PROSTITUTES,
    POPCYCLE_GROUP_CRIMINALS,
    POPCYCLE_GROUP_GOLFERS,
    POPCYCLE_GROUP_SERVANTS,
    POPCYCLE_GROUP_AIRCREW,
    POPCYCLE_GROUP_ENTERTAINERS,
    POPCYCLE_GROUP_OUT_OF_TOWN_FACTORY_WORKERS,
    POPCYCLE_GROUP_DESERT_FOLK,
    POPCYCLE_GROUP_AIRCREW_RUNWAY,

    POPCYCLE_GROUP_BALLAS,
    POPCYCLE_GROUP_GROVE,
    POPCYCLE_GROUP_VAGOS,
    POPCYCLE_GROUP_SF_RIFA,
    POPCYCLE_GROUP_DA_NANG_BOYS,
    POPCYCLE_GROUP_ITALIAN_MAFIA,
    POPCYCLE_GROUP_TRIADS,
    POPCYCLE_GROUP_VARRIO_LOS_AZTECAZ,
    POPCYCLE_GROUP_UNUSED_1,
    POPCYCLE_GROUP_UNUSED_2,
    POPCYCLE_GROUP_DEALERS,
    POPCYCLE_GROUP_SHOPKEEPERS,
    POPCYCLE_GROUP_OFFICE_WORKERS,
    POPCYCLE_GROUP_HUSBANDS,
    POPCYCLE_GROUP_WIVES,
    POPCYCLE_TOTAL_GROUPS
};

// used in CPopulation::m_PedGroups
enum ePopcyclePedGroup {
    POPCYCLE_PEDGROUP_WORKERS_LA,
    POPCYCLE_PEDGROUP_WORKERS_SF,
    POPCYCLE_PEDGROUP_WORKERS_VG,
    POPCYCLE_PEDGROUP_BUSINESS_LA,
    POPCYCLE_PEDGROUP_BUSINESS_SF,
    POPCYCLE_PEDGROUP_BUSINESS_VG,
    POPCYCLE_PEDGROUP_CLUBBERS_LA,
    POPCYCLE_PEDGROUP_CLUBBERS_SF,
    POPCYCLE_PEDGROUP_CLUBBERS_VG,
    POPCYCLE_PEDGROUP_FARMERS,
    POPCYCLE_PEDGROUP_BEACHFOLK,
    POPCYCLE_PEDGROUP_PARKFOLK_LA,
    POPCYCLE_PEDGROUP_PARKFOLK_SF,
    POPCYCLE_PEDGROUP_PARKFOLK_VG,
    POPCYCLE_PEDGROUP_CASUAL_RICH_LA,
    POPCYCLE_PEDGROUP_CASUAL_RICH_SF,
    POPCYCLE_PEDGROUP_CASUAL_RICH_VG,
    POPCYCLE_PEDGROUP_CASUAL_AVERAGE_LA,
    POPCYCLE_PEDGROUP_CASUAL_AVERAGE_SF,
    POPCYCLE_PEDGROUP_CASUAL_AVERAGE_VG,
    POPCYCLE_PEDGROUP_CASUAL_POOR_LA,
    POPCYCLE_PEDGROUP_CASUAL_POOR_SF,
    POPCYCLE_PEDGROUP_CASUAL_POOR_VG,
    POPCYCLE_PEDGROUP_PROSTITUTES_LA,
    POPCYCLE_PEDGROUP_PROSTITUTES_SF,
    POPCYCLE_PEDGROUP_PROSTITUTES_VG,
    POPCYCLE_PEDGROUP_CRIMINALS_LA,
    POPCYCLE_PEDGROUP_CRIMINALS_SF,
    POPCYCLE_PEDGROUP_CRIMINALS_VG,
    POPCYCLE_PEDGROUP_GOLFERS,
    POPCYCLE_PEDGROUP_SERVANTS_LA,
    POPCYCLE_PEDGROUP_SERVANTS_SF,
    POPCYCLE_PEDGROUP_SERVANTS_VG,
    POPCYCLE_PEDGROUP_AIRCREW_LA,
    POPCYCLE_PEDGROUP_AIRCREW_SF,
    POPCYCLE_PEDGROUP_AIRCREW_VG,
    POPCYCLE_PEDGROUP_ENTERTAINERS_LA,
    POPCYCLE_PEDGROUP_ENTERTAINERS_SF,
    POPCYCLE_PEDGROUP_ENTERTAINERS_VG,
    POPCYCLE_PEDGROUP_OUT_OF_TOWN_FACTORY_WORKERS,
    POPCYCLE_PEDGROUP_DESERT_FOLK,
    POPCYCLE_PEDGROUP_AIRCREW_RUNWAY,
    POPCYCLE_PEDGROUP_BALLAS,
    POPCYCLE_PEDGROUP_GROVE,
    POPCYCLE_PEDGROUP_VAGOS,
    POPCYCLE_PEDGROUP_SF_RIFA,
    POPCYCLE_PEDGROUP_DA_NANG_BOYS,
    POPCYCLE_PEDGROUP_ITALIAN_MAFIA,
    POPCYCLE_PEDGROUP_TRIADS,
    POPCYCLE_PEDGROUP_VARRIO_LOS_AZTECAZ,
    POPCYCLE_PEDGROUP_DEALERS = 52,
    POPCYCLE_PEDGROUP_SHOPKEEPERS,
    POPCYCLE_PEDGROUP_OFFICE_WORKERS,
    POPCYCLE_PEDGROUP_HUSBANDS,
    POPCYCLE_PEDGROUP_WIVES,
    POPCYCLE_TOTAL_PEDGROUPS
};

// used in CPopulation::m_nNumCarsInGroup and CPopulation::m_CarGroups
enum ePopcycleCarGroup {
    POPCYCLE_CARGROUP_WORKERS,
    POPCYCLE_CARGROUP_BUSINESS,
    POPCYCLE_CARGROUP_CLUBBERS,
    POPCYCLE_CARGROUP_FARMERS,
    POPCYCLE_CARGROUP_BEACHFOLK,
    POPCYCLE_CARGROUP_PARKFOLK,
    POPCYCLE_CARGROUP_CASUAL_RICH,
    POPCYCLE_CARGROUP_CASUAL_AVERAGE,
    POPCYCLE_CARGROUP_CASUAL_POOR,
    POPCYCLE_CARGROUP_PROSTITUTES,
    POPCYCLE_CARGROUP_CRIMINALS,
    POPCYCLE_CARGROUP_GOLFERS,
    POPCYCLE_CARGROUP_SERVANTS,
    POPCYCLE_CARGROUP_AIRCREW,
    POPCYCLE_CARGROUP_ENTERTAINERS,
    POPCYCLE_CARGROUP_OUT_OF_TOWN_FACTORY,
    POPCYCLE_CARGROUP_DESERT_FOLK,
    POPCYCLE_CARGROUP_AIRCREW_RUNWAY,
    POPCYCLE_CARGROUP_BALLAS,
    POPCYCLE_CARGROUP_GROVE,
    POPCYCLE_CARGROUP_VAGOS,
    POPCYCLE_CARGROUP_SF_RIFA,
    POPCYCLE_CARGROUP_DA_NANG_BOYS,
    POPCYCLE_CARGROUP_ITALIAN_MAFIA,
    POPCYCLE_CARGROUP_TRIADS,
    POPCYCLE_CARGROUP_VARRIO_LOS_AZTECAZ,
    POPCYCLE_CARGROUP_DEALERS = 28,
    POPCYCLE_CARGROUP_BOATS,
    POPCYCLE_CARGROUP_CHEAT1,
    POPCYCLE_CARGROUP_CHEAT2,
    POPCYCLE_CARGROUP_CHEAT3,
    POPCYCLE_CARGROUP_CHEAT4,
    POPCYCLE_TOTAL_CARGROUPS
};

class CPopCycle {
public:
    static float&      m_NumOther_Cars;
    static float&      m_NumCops_Cars;
    static float&      m_NumGangs_Cars;
    static float&      m_NumDealers_Cars;
    static float&      m_NumOther_Peds;
    static float&      m_NumCops_Peds;
    static float&      m_NumGangs_Peds;
    static float&      m_fPercOther;
    static float&      m_fPercCops;
    static float&      m_fPercGangs;
    static float&      m_fPercDealers;
    static bool&       m_bCurrentZoneIsGangArea;
    static float&      m_fCurrentZoneDodgyness;
    static CZone*&     m_pCurrZone;
    static CZoneInfo*& m_pCurrZoneInfo;
    static int32&      m_nCurrentZoneType;
    static int32&      m_nCurrentTimeOfWeek;
    static int32&      m_nCurrentTimeIndex;
    static char*       m_nPercTypeGroup; // char m_nPercTypeGroup[8640]; // see ePopcycleGroupPerc
    static uint8*      m_nPercOther;     // uint8 m_nPercOther[480];
    static uint8*      m_nPercCops;      // uint8 m_nPercCops[480];
    static uint8*      m_nPercGang;      // uint8 m_nPercGang[480];
    static uint8*      m_nPercDealers;   // uint8 m_nPercDealers[480];
    static uint8*      m_nMaxNumCars;    // uint8 m_nMaxNumCars[480];
    static uint8*      m_nMaxNumPeds;    // uint8 m_nMaxNumPeds[480];
    static float&      m_NumDealers_Peds;

    static bool  FindNewPedType(ePedType* arg1, int32* modelIndex, bool arg3, bool arg4);
    static float GetCurrentPercOther_Peds();
    static void  Initialise();
    static bool  IsPedAppropriateForCurrentZone(int32 modelIndex);
    static bool  IsPedInGroup(int32 modelIndex, int32 PopCycle_Group);
    static bool  PedIsAcceptableInCurrentZone(int32 modelIndex);
    static int32 PickARandomGroupOfOtherPeds();
    static int32 PickPedMIToStreamInForCurrentZone();
    static void  PlayerKilledADealer();
    static void  Update();
    static void  UpdateAreaDodgyness();
    static void  UpdateDealerStrengths();
    static void  UpdatePercentages();
    static char  GetCurrentPercTypeGroup(int32 groupId, uint8 zonePopulationType) {
        return m_nPercTypeGroup[720 * m_nCurrentTimeIndex + 360 * m_nCurrentTimeOfWeek + 18 * zonePopulationType + groupId];
    }

    static bool IsPedInGroupTheseGroups(int32 modelIndex, std::initializer_list<ePopcycleGroup> groups) {
        return rng::any_of(groups, [=](auto grp) { return IsPedInGroup(modelIndex, grp); });
    }
};
