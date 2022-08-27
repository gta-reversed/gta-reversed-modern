/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "tHandlingData.h"
#include "tBikeHandlingData.h"
#include "tFlyingHandlingData.h"
#include "tBoatHandlingData.h"

class cHandlingDataMgr {
public:
    float               field_0;
    float               fWheelFriction;
    float               field_8;
    float               field_C;
    float               field_10;

    std::array<tHandlingData, 210>      m_aVehicleHandling;
    std::array<tBikeHandlingData, 13>   m_aBikeHandling;
    std::array<tFlyingHandlingData, 24> m_aFlyingHandling;
    std::array<tBoatHandlingData, 12>   m_aBoatHandling;

public:
    static void InjectHooks();

    cHandlingDataMgr();

    void Initialise();
    // process handling.cfg
    void LoadHandlingData();
    // get vehicle number id in names table
    int32 FindExactWord(char* line, char* nameTable, int32 entrySize, int32 entryCount);
    bool HasFrontWheelDrive(uint8 handlingId);
    bool HasRearWheelDrive(uint8 handlingId);
    int32 GetHandlingId(const char* name);
    void ConvertDataToWorldUnits(tHandlingData* handling);
    void ConvertDataToGameUnits(tHandlingData* handling);
    void ConvertBikeDataToWorldUnits(tBikeHandlingData* bikeHandling);
    void ConvertBikeDataToGameUnits(tBikeHandlingData* bikeHandling);
    // get flying handling by id
    tFlyingHandlingData* GetFlyingPointer(uint8 handlingId);
    // get boat handling by id
    tBoatHandlingData* GetBoatPointer(uint8 handlingId);
    tHandlingData* GetVehiclePointer(uint32 handlingId) { return &m_aVehicleHandling[handlingId]; };
    tBikeHandlingData* GetBikeHandlingPointer(uint32 handlingId) { return &m_aBikeHandling[handlingId >= 162 ? handlingId - 162 : handlingId]; } // NOTE: 162 = VT_BIKE
};

VALIDATE_SIZE(cHandlingDataMgr, 0xC624);

// If you're searching for `mod_HandlingManager`, you can use this:
static inline cHandlingDataMgr& gHandlingDataMgr = *(cHandlingDataMgr*)0xC2B9C8;
