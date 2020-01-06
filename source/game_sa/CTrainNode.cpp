/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// Converted from thiscall void CTrainNode::CTrainNode(void) 0x6F5370
CTrainNode::CTrainNode() {
    ((void(__thiscall*)(CTrainNode*))0x6F5370)(this);
}

// Converted from thiscall void CTrainNode::SetX(float X) 0x6F5380
void CTrainNode::SetX(float X) {
    ((void(__thiscall*)(CTrainNode*, float))0x6F5380)(this, X);
}

// Converted from thiscall void CTrainNode::SetY(float Y) 0x6F53A0
void CTrainNode::SetY(float Y) {
    ((void(__thiscall*)(CTrainNode*, float))0x6F53A0)(this, Y);
}

// Converted from thiscall void CTrainNode::SetZ(float Z) 0x6F53C0
void CTrainNode::SetZ(float Z) {
    ((void(__thiscall*)(CTrainNode*, float))0x6F53C0)(this, Z);
}

// Converted from thiscall float CTrainNode::GetX(void) 0x6F53E0
float CTrainNode::GetX() {
    return ((float(__thiscall*)(CTrainNode*))0x6F53E0)(this);
}

// Converted from thiscall float CTrainNode::GetY(void) 0x6F5400
float CTrainNode::GetY() {
    return ((float(__thiscall*)(CTrainNode*))0x6F5400)(this);
}

// Converted from thiscall float CTrainNode::GetZ(void) 0x6F5420
float CTrainNode::GetZ() {
    return ((float(__thiscall*)(CTrainNode*))0x6F5420)(this);
}

// Converted from thiscall CVector CTrainNode::GetPosn(void) 0x6F5440
CVector CTrainNode::GetPosn() {
    CVector result;
    ((void(__thiscall*)(CTrainNode*, CVector*))0x6F5440)(this, &result);
    return result;
}

// Converted from thiscall void CTrainNode::SetDistanceFromStart(float dist) 0x6F5490
void CTrainNode::SetDistanceFromStart(float dist) {
    ((void(__thiscall*)(CTrainNode*, float))0x6F5490)(this, dist);
}

// Converted from thiscall float CTrainNode::GetDistanceFromStart(void) 0x6F54B0
float CTrainNode::GetDistanceFromStart() {
    return ((float(__thiscall*)(CTrainNode*))0x6F54B0)(this);
}

// Converted from thiscall uchar CTrainNode::GetLightingFromCollision(void) 0x6F5F80
unsigned char CTrainNode::GetLightingFromCollision() {
    return ((unsigned char(__thiscall*)(CTrainNode*))0x6F5F80)(this);
}