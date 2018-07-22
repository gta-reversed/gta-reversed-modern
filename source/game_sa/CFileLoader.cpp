/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

bool CFileLoader::LoadAtomicFile(RwStream *stream, unsigned int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, RwStream *, unsigned int>(0x5371F0, stream, modelIndex);
}

void CFileLoader::LoadAtomicFile(char const *filename) {
    plugin::CallDynGlobal<char const *>(0x5B39D0, filename);
}

RpClump *CFileLoader::LoadAtomicFile2Return(char const *filename) {
    return plugin::CallAndReturnDynGlobal<RpClump *, char const *>(0x537060, filename);
}

void CFileLoader::LoadCarPathNode(char const *line, int objModelIndex, int pathEntryIndex, bool a4) {
    plugin::CallDynGlobal<char const *, int, int, bool>(0x5B4380, line, objModelIndex, pathEntryIndex, a4);
}

bool CFileLoader::LoadClumpFile(RwStream *stream, unsigned int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, RwStream *, unsigned int>(0x5372D0, stream, modelIndex);
}

void CFileLoader::LoadClumpFile(char const *filename) {
    plugin::CallDynGlobal<char const *>(0x5B3A30, filename);
}

int CFileLoader::LoadClumpObject(char const *line) {
    return plugin::CallAndReturnDynGlobal<int, char const *>(0x5B4040, line);
}

bool CFileLoader::LoadCollisionFile(unsigned char *data, unsigned int dataSize, unsigned char colId) {
    return plugin::CallAndReturnDynGlobal<bool, unsigned char *, unsigned int, unsigned char>(0x538440, data, dataSize, colId);
}
