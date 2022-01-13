#pragma once


// Helper class for CGenericGameStorage

class C_PcSave {
public:
    enum class eErrorCode {
        NONE = 0,

        FAILED_TO_OPEN = 4,
        FAILED_TO_READ = 5,
        FAILED_TO_CLOSE = 6,
        SLOT_INVALID = 7,
        FAILED_TO_WRITE = 11,
    };
    
public:
    // Eg.: C:/Users/user/Documents/GTA San Andreas User Files/GTASAsf
    static inline char(&SaveFilePathWithName)[MAX_PATH] = *(char(*)[MAX_PATH])0xC16F18;

    static void InjectHooks();

    static void SetSaveDirectory(const char* path);
    static void PopulateSlotInfo();
    static void SaveSlot(int32 slot);
    static bool DeleteSlot(int32 slot);

    // Kinda NOTSA - They didn't use templates
    template<size_t N>
    static void GenerateGameFilename(int32 slot, char (&out)[N]) {
        sprintf_s(out, "%s%i%s", SaveFilePathWithName, slot + 1, ".b");
    }
    
public:
    eErrorCode error;
};
static inline C_PcSave& s_PcSaveHelper = *(C_PcSave*)0xC17034;
