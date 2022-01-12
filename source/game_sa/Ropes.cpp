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
    for (uint8 ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        aRopes[ropeId];
    }
    PlayerControlsCrane = false;
}

// 0x556B10
void CRopes::Shutdown() {
    for (uint8 ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        auto rope = aRopes[ropeId];
        if (rope.m_nRopeType) {
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
    return CModelInfo::ms_modelInfoPtrs[entity->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMax.z;
}

// 0x556000
int CRopes::FindRope(unsigned int id) {
    for (uint8 ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
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

    for (uint8 ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        if (aRopes[ropeId].m_pAttachedEntity == entity) {
            return true;
        }
    }

    return false;
}

bool CRopes::RegisterRope(CEntity* ropeObj, unsigned int ropeType, CVector startPos, bool bExpires, uint8 segmentCount, uint8 flags, CEntity* holder, unsigned int timeExpire) {
    return ((bool(__cdecl*)(CEntity*, unsigned int, CVector, bool, uint8, uint8, CEntity*, unsigned int))0x556B40)(ropeObj, ropeType, startPos, bExpires, segmentCount, flags, holder, timeExpire);
}

// 0x556AE0
void CRopes::Render() {
    for (uint8 ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        aRopes[ropeId].Render();
    }
}

// 0x555DF0
void CRopes::SetSpeedOfTopNode(unsigned int ropeId, CVector dirSpeed) {
  uint8 ropeIndex = 0;
  for (CRope* rope = aRopes; !rope->m_nRopeType || rope->m_nId != ropeId; ++rope ) {
    if (++ropeIndex == MAX_NUM_ROPES)
      return;
  }
  aRopes[ropeIndex].m_avecRopeSegmentsReleased[0] = dirSpeed;
}

// 0x558D70
void CRopes::Update() {
    if (CReplay::Mode == REPLAY_MODE_1) {
        return;
    }

    for (uint8 ropeId = 0; ropeId < m_nNumRopes; ropeId++) {
        aRopes[ropeId].Update();
    }
}

bool CRopes::FindCoorsAlongRope(uint32 ropeId, float fCoorAlongRope, CVector* pVecPosition, CVector* arg4)
{
    return plugin::CallAndReturn<bool, 0x555E40, uint32, float, CVector*, CVector*>(ropeId, fCoorAlongRope, pVecPosition, arg4);
}
