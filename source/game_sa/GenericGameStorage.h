/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum eSaveLoadBlocks {
    BLOCK_SIMPLE_VARIABLES = 0,
    BLOCK_SCRIPTS = 0x1,
    BLOCK_POOLS = 0x2,
    BLOCK_GARAGES = 0x3,
    BLOCK_GAMELOGIC = 0x4,
    BLOCK_PATHS = 0x5,
    BLOCK_PICKUPS = 0x6,
    BLOCK_PHONEINFO = 0x7,
    BLOCK_RESTART = 0x8,
    BLOCK_RADAR = 0x9,
    BLOCK_ZONES = 0xA,
    BLOCK_GANGS = 0xB,
    BLOCK_CAR_GENERATORS = 0xC,
    BLOCK_PED_GENERATORS = 0xD,
    BLOCK_AUDIO_SCRIPT_OBJECT = 0xE,
    BLOCK_PLAYERINFO = 0xF,
    BLOCK_STATS = 0x10,
    BLOCK_SET_PIECES = 0x11,
    BLOCK_STREAMING = 0x12,
    BLOCK_PED_TYPES = 0x13,
    BLOCK_TAGS = 0x14,
    BLOCK_IPLS = 0x15,
    BLOCK_SHOPPING = 0x16,
    BLOCK_GANGWARS = 0x17,
    BLOCK_STUNTJUMPS = 0x18,
    BLOCK_USER3DMARKERS = 0x1B
};

enum eSaveLoadError {
    LOADING_SYNC_ERROR = 0,
    LOADING_ERROR = 0x1,
    SAVING_ERROR = 0x2
};

struct tSlotSaveDate {
    char m_sSavedGameDateAndTime[70];
};

struct tSlotFileName {
    char m_sSavedGameName[260];
};

VALIDATE_SIZE(tSlotSaveDate, 0x46);
VALIDATE_SIZE(tSlotFileName, 0x104);

class CGenericGameStorage {
public:
     static char *ms_LoadFileNameWithPath; // static char ms_LoadFileNameWithPath[104]
     static char *ms_LoadFileName; // static char ms_LoadFileName[104]
     static char *ms_SaveFileNameJustSaved; // static char ms_SaveFileNameJustSaved[260]
     static int32 &ms_CheckSum;
     static tSlotSaveDate *ms_SlotSaveDate; // static tSlotSaveDate ms_SlotSaveDate[8]
     static tSlotFileName *ms_SlotFileName; // static tSlotFileName ms_SlotFileName[8]
     static char *ms_ValidSaveName; // static char ms_ValidSaveName[256]
     static int32 *ms_Slots; // static int32 ms_Slots[9]
     static void *&ms_WorkBuffer;
     static int32 &ms_WorkBufferPos;
     static FILE *&ms_FileHandle;
     static int32 &ms_FilePos;
     static int32 &ms_FileSize;
     static bool &ms_bFailed;
     static bool &ms_bLoading;

     static bool CheckDataNotCorrupt(int32 saveID, char *saveGameFilename);
     static bool CheckSlotDataValid(int32 saveID, bool unused);
     static void DoGameSpecificStuffAfterSucessLoad();
     static void DoGameSpecificStuffBeforeSave();
     static bool GenericLoad(bool *arg1);
     static bool GenericSave(int32 unused);
     static int32 GetCurrentVersionNumber();
     static char *GetNameOfSavedGame(int32 saveID);
    //! unused
     static char *GetNameOfSavedGame_Alt(int32 saveID);
    //! unused
    //! does nothing (return 0)
     static int32 GetSavedRadioStationPosition();
    //! unused
    //! does nothing (NOP)
     static void InitNewSettingsAfterLoad();
    //! does nothing (NOP)
     static void InitRadioStationPositionList();
     static bool LoadWorkBuffer();
     static void MakeValidSaveName(int32 saveNum);
     static bool OpenFileForReading(char *saveGameFilename, uint32 *saveID);
     static bool OpenFileForWriting();
     static void ReportError(eSaveLoadBlocks block, eSaveLoadError errorType);
    //! does nothing (return 0)
     static char RestoreForStartLoad();
     static bool SaveWorkBuffer(bool a1);
     static bool LoadDataFromWorkBuffer(void *pData, int32 size);
     static bool SaveDataToWorkBuffer(void *pData, int32 Size);
};
