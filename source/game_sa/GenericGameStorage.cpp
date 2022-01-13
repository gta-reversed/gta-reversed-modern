#include "StdInc.h"
#include "GenericGameStorage.h"

void CGenericGameStorage::InjectHooks() {
    using namespace ReversibleHooks;
    // Static functions (19x)
    // Install("CGenericGameStorage", "ReportError", 0x5D08C0, &CGenericGameStorage::ReportError);
    // Install("CGenericGameStorage", "DoGameSpecificStuffAfterSucessLoad", 0x618E90, &CGenericGameStorage::DoGameSpecificStuffAfterSucessLoad);
    // Install("CGenericGameStorage", "InitRadioStationPositionList", 0x618E70, &CGenericGameStorage::InitRadioStationPositionList);
    // Install("CGenericGameStorage", "GetSavedGameDateAndTime", 0x618D00, &CGenericGameStorage::GetSavedGameDateAndTime);
    // Install("CGenericGameStorage", "GenericLoad", 0x5D17B0, &CGenericGameStorage::GenericLoad);
    // Install("CGenericGameStorage", "GenericSave", 0x5D13E0, &CGenericGameStorage::GenericSave);
    // Install("CGenericGameStorage", "CheckSlotDataValid", 0x5D1380, &CGenericGameStorage::CheckSlotDataValid);
    // Install("CGenericGameStorage", "LoadDataFromWorkBuffer", 0x5D1300, &CGenericGameStorage::LoadDataFromWorkBuffer);
    // Install("CGenericGameStorage", "DoGameSpecificStuffBeforeSave", 0x618F50, &CGenericGameStorage::DoGameSpecificStuffBeforeSave);
    // Install("CGenericGameStorage", "SaveDataToWorkBuffer", 0x5D1270, &CGenericGameStorage::SaveDataToWorkBuffer);
    // Install("CGenericGameStorage", "LoadWorkBuffer", 0x5D10B0, &CGenericGameStorage::LoadWorkBuffer);
    // Install("CGenericGameStorage", "SaveWorkBuffer", 0x5D0F80, &CGenericGameStorage::SaveWorkBuffer);
    // Install("CGenericGameStorage", "GetCurrentVersionNumber", 0x5D0F50, &CGenericGameStorage::GetCurrentVersionNumber);
    // Install("CGenericGameStorage", "MakeValidSaveName", 0x5D0E90, &CGenericGameStorage::MakeValidSaveName);
    // Install("CGenericGameStorage", "CloseFile", 0x5D0E30, &CGenericGameStorage::CloseFile);
    // Install("CGenericGameStorage", "OpenFileForWriting", 0x5D0DD0, &CGenericGameStorage::OpenFileForWriting_void_);
    // Install("CGenericGameStorage", "OpenFileForReading", 0x5D0D20, &CGenericGameStorage::OpenFileForReading);
    // Install("CGenericGameStorage", "CheckDataNotCorrupt", 0x5D1170, &CGenericGameStorage::CheckDataNotCorrupt);
    // Install("CGenericGameStorage", "RestoreForStartLoad", 0x619000, &CGenericGameStorage::RestoreForStartLoad);
}


// Static functions
// 0x5D08C0
void CGenericGameStorage::ReportError(eBlocks nBlock, eSaveLoadError nError) {
    plugin::Call<0x5D08C0>(nBlock, nError);
}

// 0x618E90
void CGenericGameStorage::DoGameSpecificStuffAfterSucessLoad() {
    plugin::Call<0x618E90>();
}

// 0x618E70
void CGenericGameStorage::InitRadioStationPositionList() {
    plugin::Call<0x618E70>();
}

// 0x618D00
const char* CGenericGameStorage::GetSavedGameDateAndTime(int32 slot) {
    return plugin::CallAndReturn<char*, 0x618D00, int32>(slot);
}

// 0x5D17B0
bool CGenericGameStorage::GenericLoad(bool& out_bVariablesLoaded) {
    return plugin::CallAndReturn<bool, 0x5D17B0>(out_bVariablesLoaded);
}

// 0x5D13E0
bool CGenericGameStorage::GenericSave() {
    return plugin::CallAndReturn<bool, 0x5D13E0>();
}

// 0x5D1380
bool CGenericGameStorage::CheckSlotDataValid(int32 slot) {
    return plugin::CallAndReturn<bool, 0x5D1380>(slot);
}

// 0x5D1300
bool CGenericGameStorage::LoadDataFromWorkBuffer(void* data, int32 size) {
    return plugin::CallAndReturn<bool, 0x5D1300, void*, int32>(data, size);
}

// 0x618F50
void CGenericGameStorage::DoGameSpecificStuffBeforeSave() {
    plugin::Call<0x618F50>();
}

// 0x5D1270
int32 CGenericGameStorage::SaveDataToWorkBuffer(void* data, int32 Size) {
    return plugin::CallAndReturn<int32, 0x5D1270, void*, int32>(data, Size);
}

// 0x5D10B0
bool CGenericGameStorage::LoadWorkBuffer() {
    return plugin::CallAndReturn<bool, 0x5D10B0>();
}

// 0x5D0F80
bool CGenericGameStorage::SaveWorkBuffer(bool bIncludeChecksum) {
    return plugin::CallAndReturn<bool, 0x5D0F80, bool>(bIncludeChecksum);
}

// 0x5D0F50
uint32 CGenericGameStorage::GetCurrentVersionNumber() {
    return plugin::CallAndReturn<uint32, 0x5D0F50>();
}

// 0x5D0E90
char* CGenericGameStorage::MakeValidSaveName(int32 saveNum) {
    return plugin::CallAndReturn<char*, 0x5D0E90, int32>(saveNum);
}

// 0x5D0E30
bool CGenericGameStorage::CloseFile() {
    return plugin::CallAndReturn<bool, 0x5D0E30>();
}

// 0x5D0DD0
bool CGenericGameStorage::OpenFileForWriting() {
    return plugin::CallAndReturn<bool, 0x5D0DD0>();
}

// 0x5D0D20
bool CGenericGameStorage::OpenFileForReading(int32 slot, const char* fileName) {
    return plugin::CallAndReturn<bool, 0x5D0D20>(slot, fileName);
}

// 0x5D1170
bool CGenericGameStorage::CheckDataNotCorrupt(int32 slot, const char* fileName) {
    return plugin::CallAndReturn<bool, 0x5D1170>(slot, fileName);
}

// 0x619000
bool CGenericGameStorage::RestoreForStartLoad() {
    return plugin::CallAndReturn<bool, 0x619000>();
}
