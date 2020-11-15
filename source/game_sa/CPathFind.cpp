/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

CPathFind &ThePaths = **(CPathFind **)(0x40CA27);

CVector CPathNode::GetNodeCoors()
{
    CVector result;
    ((void(__thiscall *)(CPathNode *, CVector *))0x420A10)(this, &result);
    return result;
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

CVector* CPathFind::TakeWidthIntoAccountForWandering(CVector* outPosition, CNodeAddress nodeAddress, unsigned short randomSeed)
{
    return plugin::CallMethodAndReturn<CVector*, 0x4509A0, CPathFind*, CVector*, CNodeAddress, unsigned short>
        (this, outPosition, nodeAddress, randomSeed);
}

void CPathFind::FindNextNodeWandering(int pathType, float x, float y, float z, CNodeAddress* startNodeAddress, 
                                      CNodeAddress* targetNodeAddress, unsigned int dir, int8_t* outDir)
{
    plugin::CallMethod <0x451B70, CPathFind*, int, float, float, float, CNodeAddress*, CNodeAddress*, unsigned int, int8_t*>
        (this, pathType, x, y, z, startNodeAddress, targetNodeAddress, dir, outDir);
}

void CPathFind::DoPathSearch(unsigned char pathType, CVector origin, CNodeAddress originAddr,
    CVector target, CNodeAddress *pResultNodes, short *pNodesCount, int maxNodesToFind, float *pDistance,
    float maxSearchDistance, CNodeAddress *targetAddr, float maxUnkLimit, bool oneSideOnly,
    CNodeAddress forbiddenNodeAddr, bool includeNodesWithoutLinks, bool waterPath)
{
    ((void(__thiscall *)(CPathFind *, unsigned char, CVector, CNodeAddress, CVector, CNodeAddress *,
        short *, int, float *, float, CNodeAddress *, float, bool, CNodeAddress, bool, bool))0x4515D0)(
            this, pathType, origin, originAddr, target, pResultNodes, pNodesCount, maxNodesToFind, pDistance,
            maxSearchDistance, targetAddr, maxUnkLimit, oneSideOnly, forbiddenNodeAddr, includeNodesWithoutLinks,
            waterPath);
}

CPathNode *CPathFind::GetPathNode(CNodeAddress address)
{
    return ((CPathNode *(__thiscall *)(CPathFind *, CNodeAddress))0x420AC0)(this, address);
}

int CPathFind::LoadPathFindData(RwStream *stream, int index)
{
    return plugin::CallMethodAndReturn<int, 0x4529F0, CPathFind*, RwStream *, int>(this, stream, index);
}

void CPathFind::UnLoadPathFindData(int index)
{
    return plugin::CallMethod<0x44D0F0, CPathFind*, int>(this, index);
}

std::int32_t CPathFind::LoadSceneForPathNodes(CVector point)
{
    return plugin::CallMethodAndReturn<std::int32_t, 0x44DE00, CPathFind*, CVector>(this, point);
}

bool CPathFind::IsWaterNodeNearby(CVector position, float radius)
{
    return plugin::CallMethodAndReturn<bool, 0x450DE0, CPathFind*, CVector, float>(this, position, radius);
}

CNodeAddress* CPathFind::FindNodeClosestToCoors(CNodeAddress* pathLink, float X, float Y, float Z, int _nodeType, float maxDistance,
    unsigned short unk2, int unk3, unsigned short unk4, unsigned short bBoatsOnly, int unk6)
{
    return plugin::CallMethodAndReturn<CNodeAddress*, 0x44F460, CPathFind*, CNodeAddress*, float, float, float, int, float,
        unsigned short, int, unsigned short, unsigned short, int>(this, pathLink, X, Y, Z, _nodeType, maxDistance, unk2, unk3, unk4, bBoatsOnly, unk6);
}

