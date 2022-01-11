#pragma once

#include "Vector.h"
#include "Vehicle.h"
#include "Ped.h"
#include "NodeAddress.h"

class CRoadBlocks {
public:
    static void InjectHooks();

    static void Init();
    static void ClearScriptRoadBlocks();
    static void ClearSpaceForRoadBlockObject(CVector a1, CVector a2);
    static void CreateRoadBlockBetween2Points(CVector a1, CVector a2, uint32 a3);
    static void GenerateRoadBlockCopsForCar(CVehicle* vehicle, int32 a2, ePedType pedType);
    static void GenerateRoadBlocks();
    static bool GetRoadBlockNodeInfo(CNodeAddress a1, float& a2, CVector& a3);
    static void RegisterScriptRoadBlock(CVector a1, CVector a2, bool a3);
};
