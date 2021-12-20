/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum eStreamingFlags {
    STREAMING_UNKNOWN_1 = 0x1,
    STREAMING_GAME_REQUIRED = 0x2,
    STREAMING_MISSION_REQUIRED = 0x4,
    STREAMING_KEEP_IN_MEMORY = 0x8,
    STREAMING_PRIORITY_REQUEST = 0x10,
    STREAMING_LOADING_SCENE = 0x20,
    STREAMING_DONTREMOVE_IN_LOADSCENE = STREAMING_LOADING_SCENE | STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED | STREAMING_GAME_REQUIRED,
};

enum eStreamingLoadState {
    LOADSTATE_NOT_LOADED = 0, // Channel has nothing to do
    LOADSTATE_LOADED = 1,     // `RequestModelStream` was called, and there are models to be read
    LOADSTATE_REQUESTED = 2,
    LOADSTATE_READING = 3,
    LOADSTATE_FINISHING = 4
};

const uint32 STREAMING_SECTOR_SIZE = 2048;

class CStreamingInfo {
public:
    int16 m_nNextIndex; // ms_pArrayBase array index
    int16 m_nPrevIndex; // ms_pArrayBase array index
    int16 m_nNextIndexOnCd; // ModelId after this file in the containing image file
    union {
        uint8 m_nFlags; // see eStreamingFlags
        struct {
            uint8 bUnkn0x1 : 1;
            uint8 bGameRequired : 1;
            uint8 bMissionRequired : 1;
            uint8 bKeepInMemory : 1;
            uint8 bPriorityRequest : 1;
            uint8 bLoadingScene : 1;
        };
    };
    uint8  m_nImgId;
    uint32 m_nCdPosn;
    uint32 m_nCdSize;    // number of blocks/sectors; m_nCdSize * STREAMING_BLOCK_SIZE = actual size in bytes
    uint8  m_nLoadState; // see eStreamingLoadState
    char   __pad[3];

    static CStreamingInfo*& ms_pArrayBase;

public:
    static void InjectHooks();

    void Init();
    void AddToList(CStreamingInfo* listStart);
    uint32 GetCdPosn();
    void SetCdPosnAndSize(uint32 CdPosn, uint32 CdSize);
    bool GetCdPosnAndSize(uint32& CdPosn, uint32& CdSize);
    uint32 GetCdSize() { return m_nCdSize; }
    CStreamingInfo* GetNext() { return m_nNextIndex == -1 ? nullptr : &ms_pArrayBase[m_nNextIndex]; }
    CStreamingInfo* GetPrev() { return m_nPrevIndex == -1 ? nullptr : &ms_pArrayBase[m_nPrevIndex]; }
    bool InList();
    void RemoveFromList();

    bool IsLoadedOrBeingRead() const noexcept {
        switch (m_nLoadState) {
        case eStreamingLoadState::LOADSTATE_LOADED:
        case eStreamingLoadState::LOADSTATE_READING:
            return true;
        default:
            return false;
        }
    }
    bool IsLoaded() const { return m_nLoadState == eStreamingLoadState::LOADSTATE_LOADED; }

    bool DontRemoveInLoadScene() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_DONTREMOVE_IN_LOADSCENE; }
    bool IsGameRequired() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_GAME_REQUIRED; }
    bool IsMissionRequired() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_MISSION_REQUIRED; }
    bool DoKeepInMemory() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_KEEP_IN_MEMORY; }
    bool IsPriorityRequest() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_PRIORITY_REQUEST; }
    bool IsLoadingScene() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_LOADING_SCENE; }
    bool IsRequiredToBeKept() const noexcept { return IsGameRequired() || IsMissionRequired() || DoKeepInMemory(); } // GameRequired || MissionRequired || KeepInMemory
    bool IsMissionOrGameRequired() const noexcept { return IsGameRequired() || IsGameRequired(); }
};
VALIDATE_SIZE(CStreamingInfo, 0x14);
