#include "StdInc.h"

#include "PedType.h"

constexpr uint32 PED_TYPES_COUNT = 32;

CAcquaintance*& CPedType::ms_apPedTypes = *(CAcquaintance**)0xC0BBE8;

// 0x8D23B8
constexpr const char* aPedTypeNames[PED_TYPES_COUNT] = {
    "PLAYER1",    "PLAYER2", "PLAYER_NETWORK", "PLAYER_UNUSED", "CIVMALE",  "CIVFEMALE", "COP",      "GANG1",    "GANG2",    "GANG3",    "GANG4",
    "GANG5",      "GANG6",   "GANG7",          "GANG8",         "GANG9",    "GANG10",    "DEALER",   "MEDIC",    "FIREMAN",  "CRIMINAL", "BUM",
    "PROSTITUTE", "SPECIAL", "MISSION1",       "MISSION2",      "MISSION3", "MISSION4",  "MISSION5", "MISSION6", "MISSION7", "MISSION8",
};

void CPedType::InjectHooks() {
    RH_ScopedClass(CPedType);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x608E40);
    RH_ScopedInstall(Shutdown, 0x608B00);
    RH_ScopedInstall(Save, 0x5D3CD0);
    RH_ScopedInstall(Load, 0x5D3D10);
    RH_ScopedInstall(LoadPedData, 0x608B30);
    RH_ScopedInstall(FindPedType, 0x608790);
    RH_ScopedInstall(GetPedFlag, 0x608830);
    RH_ScopedOverloadedInstall(GetPedTypeAcquaintances, "1", 0x6089B0, CAcquaintance*(*)(ePedType));
    // RH_ScopedOverloadedInstall(GetPedTypeAcquaintances, "2", 0x6089D0, CAcquaintance*(*)(AcquaintanceId, ePedType));  // todo: breaks ReversibleHooks
    RH_ScopedInstall(SetPedTypeAsAcquaintance, 0x608E20);
    RH_ScopedInstall(ClearPedTypeAcquaintances, 0x608A20);
    RH_ScopedInstall(ClearPedTypeAsAcquaintance, 0x6089F0);
    RH_ScopedInstall(PoliceDontCareAboutCrimesAgainstPedType, 0x608A40);
}

// 0x608E40
void CPedType::Initialise() {
    ms_apPedTypes = new CAcquaintance[PED_TYPES_COUNT]();
    LoadPedData();
}

// 0x608B00
void CPedType::Shutdown() {
    delete[] ms_apPedTypes;
}

// 0x608B30
void CPedType::LoadPedData() {
    ePedType pedType = PED_TYPE_MISSION8;
    auto file = CFileMgr::OpenFile("DATA\\PED.DAT", "r");
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

// 0x5D3D10
void CPedType::Load() {
    for (uint32 i = 0; i < PED_TYPES_COUNT; ++i ) {
        for (auto id = 0; id < 5; ++id) {
            uint32 value;
            CGenericGameStorage::LoadDataFromWorkBuffer(&value, sizeof(uint32));
            ms_apPedTypes[i].SetAcquaintances(id, value);
        }
    }
}

// 0x5D3CD0
void CPedType::Save() {
    for (uint32 i = 0; i < PED_TYPES_COUNT; ++i ) {
        for (auto id = 0; id < 5; ++id) {
            uint32 value = ms_apPedTypes[i].GetAcquaintances(id);
            CGenericGameStorage::SaveDataToWorkBuffer(&value, 4);
        }
    }
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
CAcquaintance* CPedType::GetPedTypeAcquaintances(ePedType pedType) {
    return &ms_apPedTypes[static_cast<int32>(pedType)];
}

// 0x6089D0
CAcquaintance* CPedType::GetPedTypeAcquaintances(AcquaintanceId id, ePedType pedType) {
    return plugin::CallAndReturn<CAcquaintance*, 0x6089D0, AcquaintanceId, ePedType>(id, pedType);
}

// 0x608E20
void CPedType::SetPedTypeAsAcquaintance(AcquaintanceId id, ePedType pedType, int32 pedTypeBitNum) {
    GetPedTypeAcquaintances(pedType)->SetAsAcquaintance(id, pedTypeBitNum);
}

// 0x608A20
void CPedType::ClearPedTypeAcquaintances(AcquaintanceId id) {
    auto pedType = ms_apPedTypes[id];
    pedType.ClearAcquaintances(id);
}

// 0x6089F0
void CPedType::ClearPedTypeAsAcquaintance(AcquaintanceId id, ePedType pedType, int32 pedTypeBitNum) {
    ms_apPedTypes[pedType].ClearAsAcquaintance(id, pedTypeBitNum);
}

// 0x608A40
bool CPedType::PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType) {
    return pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10 || pedType == PED_TYPE_CRIMINAL || pedType == PED_TYPE_DEALER;
}
