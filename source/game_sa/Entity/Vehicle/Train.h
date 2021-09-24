/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"
#include "Door.h"
#include "TrainNode.h"

enum eTrainNodes {
    TRAIN_NODE_NONE = 0,
    TRAIN_DOOR_LF = 1,
    TRAIN_DOOR_RF = 2,
    TRAIN_WHEEL_RF1 = 3,
    TRAIN_WHEEL_RF2 = 4,
    TRAIN_WHEEL_RF3 = 5,
    TRAIN_WHEEL_RB1 = 6,
    TRAIN_WHEEL_RB2 = 7,
    TRAIN_WHEEL_RB3 = 8,
    TRAIN_WHEEL_LF1 = 9,
    TRAIN_WHEEL_LF2 = 10,
    TRAIN_WHEEL_LF3 = 11,
    TRAIN_WHEEL_LB1 = 12,
    TRAIN_WHEEL_LB2 = 13,
    TRAIN_WHEEL_LB3 = 14,
    TRAIN_BOGIE_FRONT = 15,
    TRAIN_BOGIE_REAR = 16,
    TRAIN_NUM_NODES
};

enum eTrainPassengersGenerationState {
    TRAIN_PASSENGERS_QUERY_NUM_PASSENGERS_TO_LEAVE = 0,
    TRAIN_PASSENGERS_TELL_PASSENGERS_TO_LEAVE = 1,
    TRAIN_PASSENGERS_QUERY_NUM_PASSENGERS_TO_ENTER = 2,
    TRAIN_PASSENGERS_TELL_PASSENGERS_TO_ENTER = 3,
    TRAIN_PASSENGERS_GENERATION_FINISHED = 4
};

class CTrain : public CVehicle {
protected:
    CTrain(plugin::dummy_func_t) : CVehicle(plugin::dummy) {}
public:
    int16    m_nNodeIndex;
    char     _pad1[2];
    float    m_fTrainSpeed; // 1.0 - train derails
    float    m_fCurrentRailDistance;
    float    m_fLength;
    float    m_fTrainGas;   // gas pedal pressed: 255.0, moving forward: 0.0, moving back: -255.0
    float    m_fTrainBrake; // 255.0 - braking
    union {
        struct {
            uint16 b01 : 1; // initialised with 1
            uint16 bStoppedAtStation : 1;
            uint16 bPassengersCanEnterAndLeave : 1;
            uint16 bIsFrontCarriage : 1;
            uint16 bIsLastCarriage : 1;
            uint16 bMissionTrain : 1;
            uint16 bClockwiseDirection : 1;
            uint16 bStopsAtStations : 1;

            uint16 bNotOnARailRoad : 1;
            uint16 bForceSlowDown : 1;
            uint16 bIsStreakModel : 1;
        } trainFlags;
        uint16 m_nTrainFlags;
    };
    char     _pad5BA[2];
    int32    m_nTimeWhenStoppedAtStation;
    char     m_nTrackId;
    char     _pad5C1[3];
    int32    m_nTimeWhenCreated;
    int16    field_5C8;                    // initialized with 0, not referenced
    uint8    m_nPassengersGenerationState; // see eTrainPassengersGenerationState
    uint8    m_nNumPassengersToLeave : 4;  // 0 to 4
    uint8    m_nNumPassengersToEnter : 4;  // 0 to 4
    CPed*    m_pTemporaryPassenger;        // we tell peds to enter train and then delete them
    CTrain*  m_pPrevCarriage;
    CTrain*  m_pNextCarriage;
    CDoor    m_aDoors[6];
    RwFrame* m_aTrainNodes[TRAIN_NUM_NODES];

    static uint32& GenTrain_Track;
    static uint32& GenTrain_TrainConfig;
    static uint8& GenTrain_Direction;
    static uint32& GenTrain_GenerationNode;
    static uint32& GenTrain_Status;
    static bool& bDisableRandomTrains;

    static CVector *aStationCoors; // { 1741.0, -1954.0, 15.0
                                   //   1297.0, -1898.0, 3.0
                                   //   -1945.0, 128.0, 29.0
                                   //   1434.0, 2632.0, 13.0
                                   //   2783.0, 1758.0, 12.0
                                   //   2865.0, 1281.0, 12.0 }

    static void InjectHooks();

    // virtual functions
    void ProcessControl() override;

    // reversed virtual functions
    void ProcessControl_Reversed();

    CTrain(int32 modelIndex, eVehicleCreatedBy createdBy);

    bool FindMaximumSpeedToStopAtStations(float* speed);
    uint32 FindNumCarriagesPulled();
    void OpenTrainDoor(float state); // dummy function
    void AddPassenger(CPed* ped); // dummy function
    void RemovePassenger(CPed* ped); // dummy function
    bool FindSideStationIsOn(); 
    bool IsInTunnel();
    void RemoveRandomPassenger();
    void FindPositionOnTrackFromCoors();
    void AddNearbyPedAsRandomPassenger();

    static void ReadAndInterpretTrackFile(char* filename, CTrainNode** nodes, int32* lineCount, float* totalDist, int32 skipStations);
    static void Shutdown();
    static void UpdateTrains(); // dummy function
    static void FindCoorsFromPositionOnTrack(float railDistance, int32 trackId, CVector* outCoors); // dummy function
    static void DisableRandomTrains(bool disable);
    static void RemoveOneMissionTrain(CTrain* train);
    static void ReleaseOneMissionTrain(CTrain* train);
    static void SetTrainSpeed(CTrain* train, float speed);
    static void SetTrainCruiseSpeed(CTrain* arg0, float cruiseSpeed);
    static CTrain* FindCaboose(CTrain* train);
    static CTrain* FindEngine(CTrain* train);
    static CTrain* FindCarriage(CTrain* train, uint8 carriage);
    static void FindNextStationPositionInDirection(bool clockwiseDirection, float distance, float* distanceToStation, int32* numStations);
    static void RemoveMissionTrains();
    static void RemoveAllTrains();
    static void ReleaseMissionTrains();
    static int32 FindClosestTrackNode(CVector posn, int32* outTrackId);
    static CTrain* FindNearestTrain(CVector posn, bool mustBeMainTrain);
    static void SetNewTrainPosition(CTrain* train, CVector posn);
    static bool IsNextStationAllowed(CTrain* train);
    static void SkipToNextAllowedStation(CTrain* train);
    static void InitTrains();
    static void CreateMissionTrain(CVector posn, bool clockwiseDirection, uint32 trainType, CTrain**outFirstCarriage, CTrain**outLastCarriage, int32 nodeIndex, int32 trackId, bool isMissionTrain);
    static void DoTrainGenerationAndRemoval();
};

VALIDATE_SIZE(CTrain, 0x6AC);

extern uint32 *NumTrackNodes; // uint32 NumTrackNodes[4]
extern float* arrTotalTrackLength; // float arrTotalTrackLength[4]
extern CTrainNode **pTrackNodes; // CTrainNode *pTrackNodes[4]
extern float *StationDist; // float StationDist[6]

void ProcessTrainAnnouncements(); // dummy function
void PlayAnnouncement(uint8 arg0, uint8 arg1);
void TrainHitStuff(CPtrList& ptrList, CEntity* entity);
void MarkSurroundingEntitiesForCollisionWithTrain(CVector arg0, float arg1, CEntity* arg2, bool bOnlyVehicles);