#pragma once

#include "ePedType.h"

class CPedType {
public:
    static CAcquaintance*& ms_apPedTypes;

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void LoadPedData();
    static void Load();
    static void Save();

    static ePedType FindPedType(const char* pedTypeName);
    static uint32 GetPedFlag(ePedType pedType);
    static CAcquaintance* GetPedTypeAcquaintances(ePedType pedType);
    static CAcquaintance* GetPedTypeAcquaintances(AcquaintanceId id, ePedType pedType);
    static void SetPedTypeAsAcquaintance(AcquaintanceId id, ePedType pedType, int32 pedTypeBitNum);
    static void ClearPedTypeAcquaintances(AcquaintanceId id);
    static void ClearPedTypeAsAcquaintance(AcquaintanceId id, ePedType pedType, int32 pedTypeBitNum);

    static bool PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType);
};
