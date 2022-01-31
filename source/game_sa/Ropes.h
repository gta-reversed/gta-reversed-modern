/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CRope;

class CRopes {
public:
    static constexpr int32 MAX_NUM_ROPES = 8;
    static CRope (&aRopes)[MAX_NUM_ROPES]; // Access using CRopes::GetRope()
    static int32& PlayerControlsCrane;

    static void  CreateRopeForSwatPed(CVector const& startPos);
    static float FindPickupHeight(CEntity* entity);

    // Returns id to array
    static int32 FindRope(uint32 id);
    static void  Init();
    static bool  IsCarriedByRope(CEntity* entity);

    // Must be used in loop to make attached to holder
    static bool RegisterRope(CEntity* ropeId, uint32 ropeType, CVector startPos, bool bExpires, uint8 segmentCount, uint8 flags, CEntity* holder, uint32 timeExpire);
    static void Render();
    static void SetSpeedOfTopNode(uint32 ropeId, CVector dirSpeed);
    static void Shutdown();
    static void Update();
    static bool FindCoorsAlongRope(uint32 ropeId, float fCoordAlongRope, CVector* pVecPosition, CVector* arg4);

public:
    static inline CRope& GetRope(int32 index) { return aRopes[index]; }
};
