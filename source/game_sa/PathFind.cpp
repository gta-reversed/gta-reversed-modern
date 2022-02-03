/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "PathFind.h"

CPathFind &ThePaths = *(CPathFind *)(0x96F050);

void CPathFind::InjectHooks()
{
    RH_ScopedClass(CPathFind);
    RH_ScopedCategoryGlobal();


}

CVector CPathNode::GetNodeCoors()
{
    CVector result;
    ((void(__thiscall *)(CPathNode *, CVector *))0x420A10)(this, &result);
    return result;
}

void CPathFind::Init()
{
    plugin::CallMethod<0x44D080, CPathFind*>(this);
}

// 0x450950
void CPathFind::Shutdown() {
    plugin::CallMethod<0x450950, CPathFind*>(this);
}

bool CPathFind::TestCrossesRoad(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress)
{
    return plugin::CallMethodAndReturn<bool, 0x44D790, CPathFind*, CNodeAddress, CNodeAddress>
        (this, startNodeAddress, targetNodeAddress);
}

bool CPathFind::TestForPedTrafficLight(CNodeAddress startNodeAddress, CNodeAddress targetNodeAddress)
{
    return plugin::CallMethodAndReturn<bool, 0x44D480, CPathFind*, CNodeAddress, CNodeAddress>
        (this, startNodeAddress, targetNodeAddress);
}

CVector* CPathFind::TakeWidthIntoAccountForWandering(CVector* outPosition, CNodeAddress nodeAddress, uint16 randomSeed)
{
    return plugin::CallMethodAndReturn<CVector*, 0x4509A0, CPathFind*, CVector*, CNodeAddress, uint16>
        (this, outPosition, nodeAddress, randomSeed);
}

void CPathFind::FindNextNodeWandering(int32 pathType, float x, float y, float z, CNodeAddress* startNodeAddress,
                                      CNodeAddress* targetNodeAddress, uint32 dir, int8* outDir)
{
    plugin::CallMethod <0x451B70, CPathFind*, int32, float, float, float, CNodeAddress*, CNodeAddress*, uint32, int8*>
        (this, pathType, x, y, z, startNodeAddress, targetNodeAddress, dir, outDir);
}

void CPathFind::DoPathSearch(uint8 pathType, CVector origin, CNodeAddress originAddr,
    CVector target, CNodeAddress *pResultNodes, int16 *pNodesCount, int32 maxNodesToFind, float *pDistance,
    float maxSearchDistance, CNodeAddress *targetAddr, float maxUnkLimit, bool oneSideOnly,
    CNodeAddress forbiddenNodeAddr, bool includeNodesWithoutLinks, bool waterPath)
{
    ((void(__thiscall *)(CPathFind *, uint8, CVector, CNodeAddress, CVector, CNodeAddress *,
        int16 *, int32, float *, float, CNodeAddress *, float, bool, CNodeAddress, bool, bool))0x4515D0)(
            this, pathType, origin, originAddr, target, pResultNodes, pNodesCount, maxNodesToFind, pDistance,
            maxSearchDistance, targetAddr, maxUnkLimit, oneSideOnly, forbiddenNodeAddr, includeNodesWithoutLinks,
            waterPath);
}

void CPathFind::SetLinksBridgeLights(float fXMin, float fXMax, float fYMin, float fYMax, bool bTrainCrossing)
{
    return plugin::CallMethod<0x44D960, CPathFind*, float, float, float, float, bool>(this, fXMin, fXMax, fYMin, fYMax, bTrainCrossing);
}

CPathNode *CPathFind::GetPathNode(CNodeAddress address)
{
    return ((CPathNode *(__thiscall *)(CPathFind *, CNodeAddress))0x420AC0)(this, address);
}

int32 CPathFind::LoadPathFindData(RwStream *stream, int32 index)
{
    return plugin::CallMethodAndReturn<int32, 0x4529F0, CPathFind*, RwStream *, int32>(this, stream, index);
}

void CPathFind::UnLoadPathFindData(int32 index)
{
    return plugin::CallMethod<0x44D0F0, CPathFind*, int32>(this, index);
}

int32 CPathFind::LoadSceneForPathNodes(CVector point)
{
    return plugin::CallMethodAndReturn<int32, 0x44DE00, CPathFind*, CVector>(this, point);
}

bool CPathFind::IsWaterNodeNearby(CVector position, float radius)
{
    return plugin::CallMethodAndReturn<bool, 0x450DE0, CPathFind*, CVector, float>(this, position, radius);
}

CNodeAddress* CPathFind::FindNodeClosestToCoors(CNodeAddress* pathLink, float X, float Y, float Z, int32 _nodeType, float maxDistance,
    uint16 unk2, int32 unk3, uint16 unk4, uint16 bBoatsOnly, int32 unk6)
{
    return plugin::CallMethodAndReturn<CNodeAddress*, 0x44F460, CPathFind*, CNodeAddress*, float, float, float, int32, float,
        uint16, int32, uint16, uint16, int32>(this, pathLink, X, Y, Z, _nodeType, maxDistance, unk2, unk3, unk4, bBoatsOnly, unk6);
}

// 0x44D2B0
void CPathFind::AllocatePathFindInfoMem() {
    // NOP
}

// 0x44D0E0
void CPathFind::PreparePathData() {
    // NOP
}

// 0x5D3500
bool CPathFind::Load() {
    return plugin::CallMethodAndReturn<bool, 0x5D3500>(this);
}

// 0x5D1502
bool CPathFind::Save() {
    return plugin::CallMethodAndReturn<bool, 0x5D1502>(this);
}

// 0x450A60
void CPathFind::UpdateStreaming(bool a1) {
    return plugin::CallMethod<0x450A60, CPathFind*, bool>(this, a1);
}
