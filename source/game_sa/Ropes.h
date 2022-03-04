/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CRope;

class CRopes {
public:
    static constexpr auto MAX_NUM_ROPES{ 8u };

    static CRope (&aRopes)[MAX_NUM_ROPES]; // Access using CRopes::GetRope()
    static int32& PlayerControlsCrane;
    static uint32& m_nRopeIdCreationCounter;

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void Update();
    static void Render();

    static bool RegisterRope(CEntity* ropeObj, uint32 ropeType, CVector startPos, bool bExpires, uint8 segmentCount, uint8, CPhysical* holder, uint32 timeExpire);

    static float FindPickupHeight(CEntity* entity);
    static int32 FindRope(uint32 id);
    static bool  FindCoorsAlongRope(uint32 ropeId, float fCoorAlongRope, CVector* outPosn, CVector* a4);

    static int32 CreateRopeForSwatPed(const CVector& startPos);
    static bool IsCarriedByRope(CPhysical* entity);
    static void SetSpeedOfTopNode(uint32 ropeId, CVector dirSpeed);

public:
    static inline CRope& GetRope(int32 index) { assert(index >= 0); return aRopes[index]; }
};
