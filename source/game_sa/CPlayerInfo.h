/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include "CPlayerData.h"
#include "CVector.h"
#include "CPlayerPed.h"

enum  ePlayerState {
    PLAYERSTATE_PLAYING,
    PLAYERSTATE_HASDIED,
    PLAYERSTATE_HASBEENARRESTED,
    PLAYERSTATE_FAILEDMISSION,
    PLAYERSTATE_LEFTGAME
};

class CPed;
class CVehicle;

class  CPlayerInfo {
public:
    CPlayerPed *m_pPed;                           // Pointer to the player ped (should always be set)
    CPlayerData m_PlayerData;               // instance of player variables
    CVehicle *m_pRemoteVehicle;             // Pointer to vehicle player is driving remotely at the moment.(NULL if on foot)
    CVehicle *m_pSpecCar;                   // which car is using the special collision model
    int m_nMoney;                           // Points for this player
    int m_nDisplayMoney;                    // Points as they would be displayed
    unsigned int m_nCollectablesPickedUp;   // How many bags of sugar do we have
    unsigned int m_nTotalNumCollectables;   // How many bags of sugar are there to be had in the game
    unsigned int m_nLastBumpPlayerCarTimer; // Keeps track of when the last ped bumped into the player car
    unsigned int m_nTaxiTimer;              // Keeps track of how long the player has been in a taxi with a passenger (in msecs)
    unsigned int m_nVehicleTimeCounter;     // keeps track of how long player has been in car for driving skill
    bool m_bTaxiTimerScore;                 // If TRUE then add 1 to score for each second that the player is driving a taxi
    bool m_bTryingToExitCar;                // if player holds exit car button, want to trigger getout once car slowed enough with a passenger
private:
    char _pad0[2];
public:
    CVehicle *m_pLastTargetVehicle;         // Last vehicle player tried to enter.
    unsigned char m_nPlayerState;           // see ePlayerState
    bool m_bAfterRemoteVehicleExplosion;
    bool m_bCreateRemoteVehicleExplosion;
    bool m_bFadeAfterRemoteVehicleExplosion;
    unsigned int m_nTimeOfRemoteVehicleExplosion;
    unsigned int m_nLastTimeEnergyLost;      // To make numbers flash on the HUD;
    unsigned int m_nLastTimeArmourLost;
    unsigned int m_nLastTimeBigGunFired;    // Tank guns etc
    unsigned int m_nTimesUpsideDownInARow;  // Make car blow up if car upside down
    unsigned int m_nTimesStuckInARow;       // Make car blow up if player cannot get out.
    unsigned int m_nCarTwoWheelCounter;     // how long has player's car been on two wheels
    float m_fCarTwoWheelDist;               // Make car blow up if player cannot get out.
    unsigned int m_nCarLess3WheelCounter;   // how long has player's car been on less than 3 wheels
    unsigned int m_nBikeRearWheelCounter;   // how long has player's bike been on rear wheel only
    float m_fBikeRearWheelDist;
    unsigned int m_nBikeFrontWheelCounter;  // how long has player's bike been on front wheel only
    float m_fBikeFrontWheelDist;
    unsigned int m_nTempBufferCounter;      // so wheels can leave the ground for a few frames without stopping above counters
    unsigned int m_nBestCarTwoWheelsTimeMs;
    float m_fBestCarTwoWheelsDistM;
    unsigned int m_nBestBikeWheelieTimeMs;
    float m_fBestBikeWheelieDistM;
    unsigned int m_nBestBikeStoppieTimeMs;
    float m_fBestBikeStoppieDistM;
    unsigned short m_nCarDensityForCurrentZone;
private:
    char _pad1[2];
public:
    float m_fRoadDensityAroundPlayer;       // 1.0f for an average city.
    unsigned int m_nTimeOfLastCarExplosionCaused;
    unsigned int m_nExplosionMultiplier;
    unsigned int m_nHavocCaused;            // A counter going up when the player does bad stuff.
    unsigned short m_nNumHoursDidntEat;
private:
    char _pad2[2];
public:
    float m_fCurrentChaseValue;             // How 'ill' is the chase at the moment
    bool m_bDoesNotGetTired;
    bool m_bFastReload;
    bool m_bFireProof;
    unsigned char m_nMaxHealth;
    unsigned char m_nMaxArmour;
    bool m_bGetOutOfJailFree;               // Player doesn't lose money/weapons next time arrested
    bool m_bFreeHealthCare;                 // Player doesn't lose money nexed time patched up at hospital
    bool m_bCanDoDriveBy;
    unsigned char m_nBustedAudioStatus;
private:
    char _pad3;
public:
    unsigned short m_nLastBustMessageNumber;
    unsigned int m_nCrosshairActivated;
    CVector2D m_vecCrosshairTarget;         // -1 ... 1 on screen
    char m_szSkinName[32];
    RwTexture *m_pSkinTexture;
    bool m_bParachuteReferenced;
private:
    char _pad4[3];
public:
    unsigned int m_nRequireParachuteTimer;
};

VALIDATE_SIZE(CPlayerInfo, 0x190);
