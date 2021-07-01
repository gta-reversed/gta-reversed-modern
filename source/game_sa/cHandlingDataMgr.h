/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
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
    tHandlingData       m_aVehicleHandling[210];
    tBikeHandlingData   m_aBikeHandling[13];
    tFlyingHandlingData m_aFlyingHandling[24];
    tBoatHandlingData   m_aBoatHandling[12];

public:
    static void InjectHooks();

    cHandlingDataMgr();

    void Initialise();
    // process handling.cfg
    void LoadHandlingData();
    // get vehicle number id in names table
    int FindExactWord(char* line, char* nameTable, int entrySize, int entryCount);
    bool HasFrontWheelDrive(unsigned char handlingId);
    bool HasRearWheelDrive(unsigned char handlingId);
    int GetHandlingId(char* name);
    void ConvertDataToWorldUnits(tHandlingData* handling);
    void ConvertDataToGameUnits(tHandlingData* handling);
    void ConvertBikeDataToWorldUnits(tBikeHandlingData* bikeHandling);
    void ConvertBikeDataToGameUnits(tBikeHandlingData* bikeHandling);
    // get flying handling by id
    tFlyingHandlingData* GetFlyingPointer(unsigned char handlingId);
    // get boat handling by id
    tBoatHandlingData* GetBoatPointer(unsigned char handlingId);
    tHandlingData* GetVehiclePointer(uint32_t handlingId) { return &m_aVehicleHandling[handlingId]; };
};

VALIDATE_SIZE(cHandlingDataMgr, 0xC624);

extern cHandlingDataMgr& gHandlingDataMgr;
