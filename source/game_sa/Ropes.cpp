/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CRope (&CRopes::aRopes)[MAX_NUM_ROPES] = *(CRope(*)[MAX_NUM_ROPES])0xB768B8;
uint8& CRopes::m_nNumRopes = *(uint8*)0xB7851D;
int32& CRopes::PlayerControlsCrane = *(int32*)0xB76898;
uint32& CRopes::m_nRopeIdCreationCounter = *(uint32*)0xB781F8;

void CRopes::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CRopes", "Init", 0x555DC0, &CRopes::Init);
    Install("CRopes", "Shutdown", 0x556B10, &CRopes::Shutdown);
    Install("CRopes", "CreateRopeForSwatPed", 0x556B10, &CRopes::CreateRopeForSwatPed);
    Install("CRopes", "FindPickupHeight", 0x556760, &CRopes::FindPickupHeight);
    Install("CRopes", "FindRope", 0x556000, &CRopes::FindRope);
    Install("CRopes", "IsCarriedByRope", 0x555F80, &CRopes::IsCarriedByRope);
    // Install("CRopes", "RegisterRope", 0x556B40, &CRopes::RegisterRope);
    Install("CRopes", "Render", 0x556AE0, &CRopes::Render);
    Install("CRopes", "SetSpeedOfTopNode", 0x555DF0, &CRopes::SetSpeedOfTopNode);
    Install("CRopes", "Update", 0x558D70, &CRopes::Update);
}

// 0x555DC0
void CRopes::Init() {
    for (auto ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        aRopes[ropeId];
    }
    PlayerControlsCrane = false;
}

// 0x556B10
void CRopes::Shutdown() {
    for (auto ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        auto rope = aRopes[ropeId];
        if (rope.m_nType != eRopeType::NONE) {
            rope.Remove();
        }
    }
}

// 0x558D10
int CRopes::CreateRopeForSwatPed(const CVector& startPos) {
//    auto mi = ModelIndices[1];
    int32 newRopeId = m_nRopeIdCreationCounter + 100;
//    bool ropeCreated = RegisterRope(newRopeId, 8, startPos, true, 0, 0, nullptr, 4000);
//    if (!ropeCreated) {
//        return -1;
//    }

    m_nRopeIdCreationCounter += 1;
    return newRopeId;
}

//0x556760
float CRopes::FindPickupHeight(CEntity* entity) {
    return CModelInfo::GetModelInfo(entity->m_nModelIndex)->GetColModel()->m_boundBox.m_vecMax.z;
}

// 0x556000
int CRopes::FindRope(uint32 id) {
    for (auto ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        if (aRopes[ropeId].m_nId == id) {
            return ropeId;
        }
    }

    return -1;
}

// 0x555F80
bool CRopes::IsCarriedByRope(CEntity* entity) {
    if (!entity) {
        return false;
    }

    for (auto ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        if (aRopes[ropeId].m_pAttachedEntity == entity) {
            return true;
        }
    }

    return false;
}

bool CRopes::RegisterRope(CEntity* ropeObj, uint32 ropeType, CVector startPos, bool bExpires, uint8 segmentCount, uint8 flags, CEntity* holder, uint32 timeExpire) {
    return ((bool(__cdecl*)(CEntity*, uint32, CVector, bool, uint8, uint8, CEntity*, uint32))0x556B40)(ropeObj, ropeType, startPos, bExpires, segmentCount, flags, holder, timeExpire);
}

// 0x556AE0
void CRopes::Render() {
    for (auto ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        aRopes[ropeId].Render();
    }
}

// 0x555DF0
void CRopes::SetSpeedOfTopNode(uint32 ropeId, CVector dirSpeed) {
  for (auto ropeIndex = 0; auto& rope : aRopes) {
      if (rope.m_nType == eRopeType::CRANE_MAGNET1 || rope.m_nId != ropeId)
          continue;

      aRopes[ropeIndex].m_aSegmentsReleased[0] = dirSpeed;
  }
}

// 0x558D70
void CRopes::Update() {
    if (CReplay::Mode == REPLAY_MODE_1) {
        return;
    }

    for (auto ropeId = 0u; ropeId < m_nNumRopes; ropeId++) {
        aRopes[ropeId].Update();
    }
}

bool CRopes::FindCoorsAlongRope(uint32 ropeId, float fCoorAlongRope, CVector* posn, CVector* arg4) {
    return plugin::CallAndReturn<bool, 0x555E40, uint32, float, CVector*, CVector*>(ropeId, fCoorAlongRope, posn, arg4);
}
