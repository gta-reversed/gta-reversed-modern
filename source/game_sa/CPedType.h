#pragma once

enum ePedType : uint32;

class CPedType {
public:
    static CPedAcquaintance* ms_apPedTypes;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void Save();
    static void Load(int32 a2);
    static void LoadPedData();

    static ePedType FindPedType(const char* pedTypeName);
    static uint32 GetPedFlag(ePedType pedType);
    static CPedAcquaintance* GetPedTypeAcquaintances(ePedType pedType);
    static CPedAcquaintance* GetPedTypeAcquaintances(int32 acquaintanceId, ePedType pedType);
    static void SetPedTypeAsAcquaintance(int32 acquaintanceId, ePedType pedType, int32 pedTypeBitNum);
    static void ClearPedTypeAcquaintances(int32 acquaintanceId);
    static void ClearPedTypeAsAcquaintance(int32 acquaintanceId, ePedType pedType, int32 pedTypeBitNum);

    static bool PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType);
};
