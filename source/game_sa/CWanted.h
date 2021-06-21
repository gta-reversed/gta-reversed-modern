/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CCrimeBeingQd.h"
#include "CAEPoliceScannerAudioEntity.h"

#include "eCrimeType.h"

class CPed;
class CCopPed;

class  CWanted {
public:
    unsigned int   m_nChaosLevel;
    unsigned int   m_nChaosLevelBeforeParole;
    unsigned int   m_nLastTimeWantedDecreased;
    unsigned int   m_nLastTimeWantedLevelChanged;
    unsigned int   m_nTimeOfParole;
    float          m_fMultiplier;                     // New crimes have their wanted level contribution multiplied by this
    unsigned char  m_nCopsInPursuit;
    unsigned char  m_nMaxCopsInPursuit;
    unsigned char  m_nMaxCopCarsInPursuit;
    unsigned char  m_nCopsBeatingSuspect;
    unsigned short m_nChanceOnRoadBlock;

    union {
        struct {
            unsigned char m_bPoliceBackOff : 1;       // If this is set the police will leave player alone (for cut-scenes)
            unsigned char m_bPoliceBackOffGarage : 1; // If this is set the police will leave player alone (for garages)
            unsigned char m_bEverybodyBackOff : 1;    // If this is set then everybody (including police) will leave the player alone (for cut-scenes)
            unsigned char m_bSwatRequired : 1;        // These three booleans are needed so that the
            unsigned char m_bFbiRequired : 1;         // streaming required vehicle stuff can be overrided
            unsigned char m_bArmyRequired : 1;
            // unsigned char m_b6 : 1;
            // unsigned char m_b7 : 1;
            // unsigned char m_b8 : 1;
        };
        unsigned char m_nFlags;
    };

    char            _pad1F;

    unsigned int    m_nCurrentChaseTime;
    unsigned int    m_nCurrentChaseTimeCounter;
    unsigned int    m_nTimeCounting;
    unsigned int    m_nWantedLevel;
    unsigned int    m_nWantedLevelBeforeParole;
    CCrimeBeingQd   m_CrimesBeingQd[16];
    CCopPed*        m_pCopsInPursuit[10];
    CAEPoliceScannerAudioEntity m_PoliceScannerAudio;
    bool            m_bLeavePlayerAlone;
    char            _pad299[3];

    static unsigned int &MaximumWantedLevel; // default 6
    static unsigned int &nMaximumWantedLevel; // default 9200
    static bool &bUseNewsHeliInAdditionToPolice;

public:
    static void InjectHooks();

    void Initialise();
    void Reset();
    static void InitialiseStaticVariables();

    void UpdateWantedLevel();
    static void SetMaximumWantedLevel(int level);
    bool AreMiamiViceRequired();
    bool AreSwatRequired() const;
    bool AreFbiRequired() const;
    bool AreArmyRequired() const;
    int NumOfHelisRequired();
    // dummy function
    static void ResetPolicePursuit();
    void ClearQdCrimes();
    bool AddCrimeToQ(eCrimeType crimeType, int crimeId, const CVector& posn, bool bAlreadyReported, bool bPoliceDontReallyCare);
    void ReportCrimeNow(eCrimeType crimeType, const CVector& posn, bool bPoliceDontReallyCare);
    static void RemovePursuitCop(CCopPed* cop, CCopPed** copsArray, unsigned char& copsCounter);
    bool IsInPursuit(CCopPed* cop);
    static void UpdateEachFrame();
    void RegisterCrime(eCrimeType crimeType, const CVector& posn, CPed* ped, bool bPoliceDontReallyCare);
    void RegisterCrime_Immediately(eCrimeType crimeType, const CVector& posn, CPed* ped, bool bPoliceDontReallyCare);
    void SetWantedLevel(int level);
    void CheatWantedLevel(int level);
    void SetWantedLevelNoDrop(int level);
    void ClearWantedLevelAndGoOnParole();
    static int WorkOutPolicePresence(CVector posn, float radius);
    void UpdateCrimesQ();
    bool IsClosestCop(CPed* ped, int numCopsToCheck);
    static CCopPed* ComputePursuitCopToDisplace(CCopPed* cop, CCopPed** copsArray);
    void RemovePursuitCop(CCopPed* cop);
    void RemoveExcessPursuitCops();
    void Update();
    static bool CanCopJoinPursuit(CCopPed* target, unsigned char maxCopsCount, CCopPed** copsArray, unsigned char& copsCounter);
    bool CanCopJoinPursuit(CCopPed* cop);
    bool SetPursuitCop(CCopPed* cop);
};

VALIDATE_SIZE(CWanted, 0x29C);
