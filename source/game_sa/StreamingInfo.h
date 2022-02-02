/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
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
    // Model isn't loaded
    LOADSTATE_NOT_LOADED = 0,

    // Model is loaded
    LOADSTATE_LOADED = 1,

    // Model in request list, but not yet in loading channel (TODO: Verify this)
    LOADSTATE_REQUESTED = 2,

    // Model is being read
    LOADSTATE_READING = 3,

    // If the model is a `big` one this state is used to indicate
    // that the model's first half has been loaded and is yet to be
    // finished by loading the second half.
    // When it has been loaded the state is set to `LOADED`
    LOADSTATE_FINISHING = 4 
};

constexpr auto STREAMING_SECTOR_SIZE = 2048u;

class CStreamingInfo {
public:
    int16 m_nNextIndex;     // ms_pArrayBase array index
    int16 m_nPrevIndex;     // ms_pArrayBase array index
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
    uint8  m_nImgId;        // Index into CStreaming::ms_files
    uint32 m_nCdPosn;       // Position in directory (in sectors)
    uint32 m_nCdSize;       // Size of resource (in sectors); m_nCdSize * STREAMING_BLOCK_SIZE = actual size in bytes
    uint32 m_nLoadState;    // See eStreamingLoadState

    static CStreamingInfo*& ms_pArrayBase;

public:
    static void InjectHooks();

    void Init();
    void AddToList(CStreamingInfo* listStart);
    uint32 GetCdPosn();
    void SetCdPosnAndSize(uint32 CdPosn, uint32 CdSize);
    bool GetCdPosnAndSize(uint32& CdPosn, uint32& CdSize);
    bool HasCdPosnAndSize() const noexcept { return m_nCdSize != 0; }
    uint32 GetCdSize() { return m_nCdSize; }
    CStreamingInfo* GetNext() { return m_nNextIndex == -1 ? nullptr : &ms_pArrayBase[m_nNextIndex]; }
    CStreamingInfo* GetPrev() { return m_nPrevIndex == -1 ? nullptr : &ms_pArrayBase[m_nPrevIndex]; }
    bool InList();
    void RemoveFromList();

    void SetFlags(uint32 flags) { m_nFlags |= flags; }
    void ClearFlags(uint32 flags) { m_nFlags &= ~flags; }
    auto GetFlags() const noexcept { return m_nFlags; }
    void ClearAllFlags() noexcept { m_nFlags = 0; } // Clears all flags
    bool AreAnyFlagsSetOutOf(uint32 flags) const noexcept { return GetFlags() & flags; } // Checks if any flags in `flags` are set

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
    bool IsRequested() const { return m_nLoadState == eStreamingLoadState::LOADSTATE_REQUESTED; }
    bool IsBeingRead() const { return m_nLoadState == eStreamingLoadState::LOADSTATE_READING; }
    bool IsLoadingFinishing() const { return m_nLoadState == eStreamingLoadState::LOADSTATE_FINISHING; }

    bool DontRemoveInLoadScene() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_DONTREMOVE_IN_LOADSCENE; }
    bool IsGameRequired() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_GAME_REQUIRED; }
    bool IsMissionRequired() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_MISSION_REQUIRED; }
    bool DoKeepInMemory() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_KEEP_IN_MEMORY; }
    bool IsPriorityRequest() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_PRIORITY_REQUEST; }
    bool IsLoadingScene() const noexcept { return m_nFlags & eStreamingFlags::STREAMING_LOADING_SCENE; }
    bool IsMissionOrGameRequired() const noexcept { return IsMissionRequired() || IsGameRequired(); }
    bool IsRequiredToBeKept() const noexcept { return IsMissionOrGameRequired() || DoKeepInMemory(); } // GameRequired || MissionRequired || KeepInMemory
};
VALIDATE_SIZE(CStreamingInfo, 0x14);
