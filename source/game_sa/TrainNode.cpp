/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "TrainNode.h"

// 0x6F5370
CTrainNode::CTrainNode() {
    m_bSurfLightingFound = false;
}

// 0x6F5380
void CTrainNode::SetX(float X) {
    x = int16(X * 8.0f);
}

// 0x6F53A0
void CTrainNode::SetY(float Y) {
    y = int16(Y * 8.0f);
}

// 0x6F53C0
void CTrainNode::SetZ(float Z) {
    z = int16(Z * 8.0f);
}

// 0x6F53E0
float CTrainNode::GetX() const {
    return (float)x * 0.125f;
}

// 0x6F5400
float CTrainNode::GetY() const {
    return (float)y * 0.125f;
}

// 0x6F5420
float CTrainNode::GetZ() const {
    return (float)z * 0.125f;
}

// 0x6F5440
CVector CTrainNode::GetPosn() const {
    return { GetX(), GetY(), GetZ() };
}

// 0x6F5490
void CTrainNode::SetDistanceFromStart(float dist) {
    m_nDistanceFromStart = int16(dist * 3.0f);
}

// 0x6F54B0
float CTrainNode::GetDistanceFromStart() const {
    return (float)m_nDistanceFromStart / 3.0f;
}

// 0x6F5F80
tColLighting CTrainNode::GetLightingFromCollision() {
    if ( m_bSurfLightingFound ) {
        return m_nSurfaceLighting;
    }

    CColPoint cp{};
    CEntity* entity{};
    auto pos = GetPosn();
    pos.z += 1.0f;
    if (!CWorld::ProcessVerticalLine(pos, -1000.0f, cp, entity, true)) {
        return tColLighting{ 0x48 };
    }
    m_nSurfaceLighting = {};
    m_bSurfLightingFound = true;
    return {};
}
