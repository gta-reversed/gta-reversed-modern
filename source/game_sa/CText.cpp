#include "StdInc.h"

CText(&TheText) = *reinterpret_cast<CText*>(0xC1B340);

void CText::InjectHooks() {

}

CText::CText() {
// 0x0x6A00F0
}

CText* CText::Constructor() {
    return plugin::CallMethodAndReturnDynGlobal<CText*>(0x6A00F0, this);
}

CText::~CText() {
// 0x0x6A0140
}

CText* CText::Destructor() {
    return plugin::CallMethodAndReturnDynGlobal<CText*>(0x6A0140, this);
}

char* CText::Get(char* key) {
    return plugin::CallMethodAndReturnDynGlobal<char*, CText*>(0x6A0050, this, key);
}

void CText::ReadTag(char* buf, FILE* file, int* pFileOffset, bool dontRead) {

}

void CText::LoadMissionTable(const char* tableName) {

}

void CText::LoadMissionPackText() {
// 0x69F9A0
}

void CText::Load() {
// 0x6A01A0
}

void CText::Unload(bool bUnloadMissionData) {
// 0x69FF20
}

void CText::GetMissionTableName(char* outStr) {

}

CText__Tabl::CText__Tabl() {

}

CText__Tabl::~CText__Tabl() {

}

void CText__Tabl::Read(size_t TABLblockSize, FILE* file, int* pFileOffset, int maxReadSize) {

}

CText__TKey::CText__TKey() {

}

CText__TKey::~CText__TKey() {

}

bool CText__TKey::Read(size_t TKEYblockSize, FILE* file, int* pFileOffset, bool skipReading) {
    return false;
}

void CText__TKey::PatchOffsets(int posOffsetMovement) {

}

tGXT_VERSION_2_TKEY_item* CText__TKey::BinarySearch(unsigned int key, tGXT_VERSION_2_TKEY_item* data, short firstIndex, short lastIndex) {
    return nullptr;
}

const char *CText__TKey::GetTextByLabel(const char* keyName, bool* bFound) {
    return nullptr;
}

bool CText__TDat::Read(size_t TABLblockSize, FILE* file, int* pFileOffset, bool skipRead) {
    return false;
}
