#include "StdInc.h"

constexpr uint32 PED_TYPES_COUNT = 32;

// 0xC0BBE8
CPedAcquaintance* CPedType::ms_apPedTypes = {};

// 0x8D23B8
constexpr const char* aPedTypeNames[PED_TYPES_COUNT] = {
    "PLAYER1",    "PLAYER2", "PLAYER_NETWORK", "PLAYER_UNUSED", "CIVMALE",  "CIVFEMALE", "COP",      "GANG1",    "GANG2",    "GANG3",    "GANG4",
    "GANG5",      "GANG6",   "GANG7",          "GANG8",         "GANG9",    "GANG10",    "DEALER",   "MEDIC",    "FIREMAN",  "CRIMINAL", "BUM",
    "PROSTITUTE", "SPECIAL", "MISSION1",       "MISSION2",      "MISSION3", "MISSION4",  "MISSION5", "MISSION6", "MISSION7", "MISSION8",
};

void CPedType::InjectHooks() {
    ReversibleHooks::Install("CPedType", "Initialise", 0x608E40, &CPedType::Initialise);
    ReversibleHooks::Install("CPedType", "Shutdown", 0x608B00, &CPedType::Shutdown);
    ReversibleHooks::Install("CPedType", "Save", 0x5D3CD0, &CPedType::Save);
    ReversibleHooks::Install("CPedType", "Load", 0x5D3D10, &CPedType::Load);
    ReversibleHooks::Install("CPedType", "LoadPedData", 0x608B30, &CPedType::LoadPedData);
    ReversibleHooks::Install("CPedType", "FindPedType", 0x608790, &CPedType::FindPedType);
    ReversibleHooks::Install("CPedType", "GetPedFlag", 0x608830, &CPedType::GetPedFlag);
    ReversibleHooks::Install("CPedType", "GetPedTypeAcquaintances_1", 0x6089B0, static_cast<CPedAcquaintance*(*)(ePedType)>(&CPedType::GetPedTypeAcquaintances));
    ReversibleHooks::Install("CPedType", "GetPedTypeAcquaintances_2", 0x6089D0, static_cast<CPedAcquaintance*(*)(int32, ePedType)>(&CPedType::GetPedTypeAcquaintances));
    ReversibleHooks::Install("CPedType", "SetPedTypeAsAcquaintance", 0x608E20, &CPedType::SetPedTypeAsAcquaintance);
    ReversibleHooks::Install("CPedType", "ClearPedTypeAcquaintances", 0x608A20, &CPedType::ClearPedTypeAcquaintances);
    ReversibleHooks::Install("CPedType", "ClearPedTypeAsAcquaintance", 0x6089F0, &CPedType::ClearPedTypeAsAcquaintance);
    ReversibleHooks::Install("CPedType", "PoliceDontCareAboutCrimesAgainstPedType", 0x608A40, &CPedType::PoliceDontCareAboutCrimesAgainstPedType);
}

// 0x608E40
void CPedType::Initialise() {
    ms_apPedTypes = new CPedAcquaintance[PED_TYPES_COUNT]();
    LoadPedData();
}

// 0x608B00
void CPedType::Shutdown() {
    delete[] ms_apPedTypes;
}

// 0x5D3CD0
void CPedType::Save() {
    for (uint32 i = 0; i < PED_TYPES_COUNT; ++i ) {
        for (uint32 acquaintanceId = 0; acquaintanceId < 5; ++acquaintanceId) {
            uint32 pSource = ms_apPedTypes[i].GetAcquaintances(acquaintanceId);
            CGenericGameStorage::SaveDataToWorkBuffer(&pSource, 4);
        }
    }
}

// 0x5D3D10
void CPedType::Load(int32 a2) {
    for (uint32 i = 0; i < PED_TYPES_COUNT; ++i ) {
        for (uint32 acquaintanceId = 0; acquaintanceId < 5; ++acquaintanceId) {
            uint32 value;
            CGenericGameStorage::LoadDataFromWorkBuffer(&value, sizeof(int32));
            ms_apPedTypes[i].SetAcquaintances(acquaintanceId, value);
        }
    }
}

// 0x608B30
void CPedType::LoadPedData() {
    ePedType pedType = PED_TYPE_MISSION8;
    FILESTREAM file = CFileMgr::OpenFile("DATA\\PED.DAT", "r");
    for (char* line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file)) {
        if (*line == '#' || !*line)
            continue;

        char buf[32];
        sscanf(line, "%s", buf);
        if (!strcmp(buf, "Hate")) {
            uint32 hate = 0;
            strtok(line, " ,\t");
            for (const char* pedTypeName = strtok(nullptr, " ,\t"); pedTypeName; pedTypeName = strtok(nullptr, " ,\t")) {
                hate |= GetPedFlag(FindPedType(pedTypeName));
            }
            ms_apPedTypes[pedType].m_nHate = hate;
        } else if (!strcmp(buf, "Dislike")) {
            uint32 dislike = 0;
            strtok(line, " ,\t");
            for (const char* pedTypeName = strtok(nullptr, " ,\t"); pedTypeName; pedTypeName = strtok(nullptr, " ,\t")) {
                dislike |= GetPedFlag(FindPedType(pedTypeName));
            }
            ms_apPedTypes[pedType].m_nDislike = dislike;
        } else if (!strcmp(buf, "Like")) {
            uint32 like = 0;
            strtok(line, " ,\t");
            for (const char* pedTypeName = strtok(nullptr, " ,\t"); pedTypeName; pedTypeName = strtok(nullptr, " ,\t")) {
                like |= GetPedFlag(FindPedType(pedTypeName));
            }
            ms_apPedTypes[pedType].m_nLike = like;
        } else if (!strcmp(buf, "Respect")) {
            uint32 respect = 0;
            strtok(line, " ,\t");
            for (const char* pedTypeName = strtok(nullptr, " ,\t"); pedTypeName; pedTypeName = strtok(nullptr, " ,\t")) {
                respect |= GetPedFlag(FindPedType(pedTypeName));
            }
            ms_apPedTypes[pedType].m_nRespect = respect;
        } else {
            pedType = FindPedType(buf);
        }
    }
    CFileMgr::CloseFile(file);
}

// 0x608790
ePedType CPedType::FindPedType(const char* pedTypeName) {
    for (int16 pedType = 0; pedType < PED_TYPES_COUNT; pedType++) {
        if (strcmp(pedTypeName, aPedTypeNames[pedType]) != 0)
            continue;

        return static_cast<ePedType>(pedType);
    }

    if (strcmp(pedTypeName, "PLAYER_NETWORK") == 0) {
        return PED_TYPE_PLAYER_NETWORK;
    } else if (strcmp(pedTypeName, "PLAYER_UNUSED") == 0) {
        return PED_TYPE_PLAYER_UNUSED;
    } else {
        return PED_TYPE_MISSION8;
    }
}

// 0x608830
uint32 CPedType::GetPedFlag(ePedType pedType) {
    if (pedType >= PED_TYPE_MISSION8) {
        return PED_TYPE_PLAYER1;
    } else {
        return PED_TYPE_PLAYER2 << pedType;
    }
}

// 0x6089B0
CPedAcquaintance* CPedType::GetPedTypeAcquaintances(ePedType pedType) {
    return &ms_apPedTypes[static_cast<int32>(pedType)];
}

// 0x6089D0
CPedAcquaintance* CPedType::GetPedTypeAcquaintances(int32 acquaintanceId, ePedType pedType) {
    auto index = acquaintanceId + static_cast<int32>(pedType);
    return &ms_apPedTypes[index];
}

// 0x608E20
void CPedType::SetPedTypeAsAcquaintance(int32 acquaintanceId, ePedType pedType, int32 pedTypeBitNum) {
    ms_apPedTypes[pedType].SetAsAcquaintance(acquaintanceId, pedTypeBitNum);
}

// 0x608A20
void CPedType::ClearPedTypeAcquaintances(int32 acquaintanceId) {
    auto pedType = ms_apPedTypes[acquaintanceId];
    pedType.ClearAcquaintances(acquaintanceId);
}

// 0x6089F0
void CPedType::ClearPedTypeAsAcquaintance(int32 acquaintanceId, ePedType pedType, int32 pedTypeBitNum) {
    ms_apPedTypes[pedType].ClearAsAcquaintance(acquaintanceId, pedTypeBitNum);
}

// 0x608A40
bool CPedType::PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType) {
    return pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10 || pedType == PED_TYPE_CRIMINAL || pedType == PED_TYPE_DEALER;
}
