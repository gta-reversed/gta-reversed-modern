#pragma once

enum ePedType : unsigned int;

class CPedType {
public:
    static CPedAcquaintance* ms_apPedTypes;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void Save();
    static void Load(int a2);
    static void LoadPedData();

    static ePedType FindPedType(const char* pedTypeName);
    static unsigned int GetPedFlag(ePedType pedType);
    static CPedAcquaintance* GetPedTypeAcquaintances(ePedType pedType);
    static CPedAcquaintance* GetPedTypeAcquaintances(int acquaintanceId, ePedType pedType);
    static void SetPedTypeAsAcquaintance(int acquaintanceId, ePedType pedType, int pedTypeBitNum);
    static void ClearPedTypeAcquaintances(int acquaintanceId);
    static void ClearPedTypeAsAcquaintance(int acquaintanceId, ePedType pedType, int pedTypeBitNum);

    static bool PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType);
};
