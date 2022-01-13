#pragma once

class CGenericGameStorage {
    using tSlotSaveDate = char[70];
    using tSlotFileName = char[260];

    enum class eBlocks {
        SIMPLE_VARIABLES,
        SCRIPTS,
        POOLS,
        GARAGES,
        GAMELOGIC,
        PATHS,
        PICKUPS,
        PHONEINFO,
        RESTART,
        RADAR,
        ZONES,
        GANGS,
        CAR_GENERATORS,
        PED_GENERATORS,
        AUDIO_SCRIPT_OBJECT,
        PLAYERINFO,
        STATS,
        SET_PIECES,
        STREAMING,
        PED_TYPES,
        TAGS,
        IPLS,
        SHOPPING,
        GANGWARS,
        STUNTJUMPS,
        ENTRY_EXITS,
        RADIOTRACKS,
        USER3DMARKERS,

        TOTAL,
    };

    enum class eSaveLoadError {
        SYNC,
        LOADING,
        SAVING
    };
public:
    enum class eSlotState {
        IN_USE,
        EMPTY,
        CORRUPT
    };
        
public:
    static inline uint32& ms_WorkBufferSize = *(uint32*)0x8D2BE0;
    static inline char(&ms_SaveFileNameJustSaved)[260] = *(char(*)[260])0xC16030;
    static inline uint32& ms_CheckSum = *(uint32*)0xC16134;
    static inline tSlotSaveDate(&ms_SlotSaveDate)[8] = *(tSlotSaveDate(*)[8])0xC16138;
    static inline tSlotFileName(&ms_SlotFileName)[8] = *(tSlotFileName(*)[8])0xC16368;
    static inline uint8*& ms_WorkBuffer = *(uint8**)0xC16EE8;
    static inline int32& ms_WorkBufferPos = *(int32*)0xC16EEC;
    static inline FILE*& ms_FileHandle = *(FILE**)0xC16EF0;
    static inline uint32& ms_FilePos = *(uint32*)0xC16EF4;
    static inline uint32& ms_FileSize = *(uint32*)0xC16EF8;
    static inline bool& ms_bFailed = *(bool*)0xC16EFC;
    static inline eSlotState(&ms_Slots)[8] = *(eSlotState(*)[8])0xC16EBC;
    static inline const char ms_BlockTagName[] =  "BLOCK" ;

public:
    static void InjectHooks();

    static void ReportError(eBlocks nBlock, eSaveLoadError nError);
    static void DoGameSpecificStuffAfterSucessLoad();
    static void InitRadioStationPositionList();
    static const char* GetSavedGameDateAndTime(int32 slot);
    static bool GenericLoad(bool& outbVariablesLoaded);
    static bool GenericSave();
    static bool CheckSlotDataValid(int32 slot);
    static bool LoadDataFromWorkBuffer(void* data, int32 size);
    static void DoGameSpecificStuffBeforeSave();
    static int32 SaveDataToWorkBuffer(void* data, int32 Size);
    static bool LoadWorkBuffer();
    static bool SaveWorkBuffer(bool bIncludeChecksum);
    static uint32 GetCurrentVersionNumber();
    static char* MakeValidSaveName(int32 saveNum);
    static bool CloseFile();
    static bool OpenFileForWriting();
    static bool OpenFileForReading(int32 slot, const char* fileName);
    static bool CheckDataNotCorrupt(int32 slot, const char* fileName);
    static bool RestoreForStartLoad();
};
