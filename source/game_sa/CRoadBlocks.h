#pragma once

#include "CVector.h"
#include "CVehicle.h"
#include "CPed.h"
#include "CNodeAddress.h"

class CRoadBlocks {
public:
    static void InjectHooks();

    static void Init(char const* datFile);
    static void ClearScriptRoadBlocks();
    static void ClearSpaceForRoadBlockObject(CVector a1, CVector a2);
    static void CreateRoadBlockBetween2Points(CVector a1, CVector a2, uint32 a3);
    static void GenerateRoadBlockPedsForCar(CVehicle* a1, int32 a2, ePedType pedType);
    static void GenerateRoadBlocks();
    static bool GetRoadBlockNodeInfo(CNodeAddress a1, float& a2, CVector& a3);
    static void RegisterScriptRoadBlock(CVector a1, CVector a2, bool a3);
};
