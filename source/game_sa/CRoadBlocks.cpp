#include "StdInc.h"

void CRoadBlocks::InjectHooks() {
//    ReversibleHooks::Install("CRoadBlocks", "Init", 0x461100, &CRoadBlocks::Init);
//    ReversibleHooks::Install("CRoadBlocks", "ClearScriptRoadBlocks", 0x460EC0, &CRoadBlocks::ClearScriptRoadBlocks);
//    ReversibleHooks::Install("CRoadBlocks", "ClearSpaceForRoadBlockObject", 0x461020, &CRoadBlocks::ClearSpaceForRoadBlockObject);
//    ReversibleHooks::Install("CRoadBlocks", "CreateRoadBlockBetween2Points", 0x4619C0, &CRoadBlocks::CreateRoadBlockBetween2Points);
//    ReversibleHooks::Install("CRoadBlocks", "GenerateRoadBlockPedsForCar", 0x461170, &CRoadBlocks::GenerateRoadBlockPedsForCar);
//    ReversibleHooks::Install("CRoadBlocks", "GenerateRoadBlocks", 0x4629E0, &CRoadBlocks::GenerateRoadBlocks);
//    ReversibleHooks::Install("CRoadBlocks", "GetRoadBlockNodeInfo", 0x460EE0, &CRoadBlocks::GetRoadBlockNodeInfo);
//    ReversibleHooks::Install("CRoadBlocks", "RegisterScriptRoadBlock", 0x460DF0, &CRoadBlocks::RegisterScriptRoadBlock);
}

// 0x461100
void CRoadBlocks::Init(char const* datFile) {
    plugin::Call<0x461100, char const*>(datFile);
}

// 0x460EC0
void CRoadBlocks::ClearScriptRoadBlocks() {
    plugin::Call<0x460EC0>();
}

// 0x461020
void CRoadBlocks::ClearSpaceForRoadBlockObject(CVector a1, CVector a2) {
    plugin::Call<0x461020, CVector, CVector>(a1, a2);
}

// 0x4619C0
void CRoadBlocks::CreateRoadBlockBetween2Points(CVector a1, CVector a2, unsigned int a3) {
    plugin::Call<0x4619C0, CVector, CVector, unsigned int>(a1, a2, a3);
}

// 0x461170
void CRoadBlocks::GenerateRoadBlockPedsForCar(CVehicle* a1, int a2, ePedType pedType) {
    plugin::Call<0x461170, CVehicle*, int, ePedType>(a1, a2, pedType);
}

// 0x4629E0
void CRoadBlocks::GenerateRoadBlocks() {
    plugin::Call<0x4629E0>();
}

// 0x460EE0
bool CRoadBlocks::GetRoadBlockNodeInfo(CNodeAddress a1, float& a2, CVector& a3) {
    return plugin::CallAndReturn<bool, 0x460EE0, CNodeAddress, float, CVector>(a1, a2, a3);
}

// 0x460DF0
void CRoadBlocks::RegisterScriptRoadBlock(CVector a1, CVector a2, bool a3) {
    plugin::Call<0x460DF0, CVector, CVector, bool>(a1, a2, a3);
}
