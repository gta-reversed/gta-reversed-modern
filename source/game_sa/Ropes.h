/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Rope.h"

class CRopes {
public:
    static constexpr uint8 MAX_NUM_ROPES = 255;

	static CRope   (&aRopes)[MAX_NUM_ROPES]; // Access using CRopes::GetRope()
	static uint8&  m_nNumRopes;
	static int32&  PlayerControlsCrane;
	static uint32& m_nRopeIdCreationCounter;

public:
	static void InjectHooks();

	static int32 CreateRopeForSwatPed(const CVector& startPos);
	static float FindPickupHeight(CEntity* entity);

	static int32 FindRope(uint32 id);
	static void Init();
	static bool IsCarriedByRope(CEntity* entity);

	static bool RegisterRope(CEntity* ropeObj, uint32 ropeType, CVector startPos, bool bExpires, uint8 segmentCount, uint8, CEntity* holder, uint32 timeExpire);
	static void Render();
	static void SetSpeedOfTopNode(uint32 ropeId, CVector dirSpeed);
	static void Shutdown();
	static void Update();
    static bool FindCoorsAlongRope(uint32 ropeId, float fCoorAlongRope, CVector* posn, CVector* arg4);

public:
    static inline CRope& GetRope(int32 index) { return aRopes[index]; }
};
