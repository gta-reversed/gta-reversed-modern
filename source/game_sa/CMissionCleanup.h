/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#define FUNC_CMissionCleanup__Init 0x4637A0
#define FUNC_CMissionCleanup__Process 0x468560
#define FUNC_CMissionCleanup__FindFree 0x4637C0
#define FUNC_CMissionCleanup__AddEntityToList 0x4637E0
#define FUNC_CMissionCleanup__RemoveEntityFromList 0x4654B0
#define FUNC_CMissionCleanup__CheckIfCollisionHasLoadedForMissionObjects 0x4652D0
constexpr int32 NUM_MISSION_CLEANUP_OBJECTS = 75;

enum MissionCleanUpEntityType : uint8 {
    MISSION_CLEANUP_ENTITY_TYPE_EMPTY          = 0, // free slot

    MISSION_CLEANUP_ENTITY_TYPE_VEHICLE        = 1,
    MISSION_CLEANUP_ENTITY_TYPE_PED            = 2,
    MISSION_CLEANUP_ENTITY_TYPE_OBJECT         = 3,
    MISSION_CLEANUP_ENTITY_TYPE_PARTICLE       = 4,
    MISSION_CLEANUP_ENTITY_TYPE_GROUP          = 5,
    MISSION_CLEANUP_ENTITY_TYPE_PED_QUEUE      = 7,
    MISSION_CLEANUP_ENTITY_TYPE_TASK_SEQUENCE  = 8,
    MISSION_CLEANUP_ENTITY_TYPE_DECISION_MAKER = 9,
    // type 10 does not exist
    MISSION_CLEANUP_ENTITY_TYPE_SEARCHLIGHT    = 11,
    MISSION_CLEANUP_ENTITY_TYPE_CHECKPOINT     = 12,
    MISSION_CLEANUP_ENTITY_TYPE_TXD            = 13
};

struct tMissionCleanupEntity {
    char  type;
    char  _pad[3];
    int32 handle;
};
VALIDATE_SIZE(tMissionCleanupEntity, 0x8);

class CMissionCleanup {
public:
    tMissionCleanupEntity m_Objects[75];
    char                  m_Count;
    char                  _pad[3];

public:
    // Default constructor
    CMissionCleanup();

    // Initializes data
    void Init();

    // Performs a clean-up
    void Process();

    // Finds a free entity, returns NULL if no free entity can be found.
    tMissionCleanupEntity* FindFree();

    // Adds entity to list
    void AddEntityToList(int32 handle, MissionCleanUpEntityType type);

    // Remotes entity from list
    void RemoveEntityFromList(int32 handle, MissionCleanUpEntityType type);

    // Checks if collision has loaded for mission objects
    void CheckIfCollisionHasLoadedForMissionObjects();
};

VALIDATE_SIZE(CMissionCleanup, 0x25C);
