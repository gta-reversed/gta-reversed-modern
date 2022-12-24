/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Automobile.h"

enum eTrailerNodes {
    TRAILER_NODE_NONE  = 0,
    TRAILER_CHASSIS    = 1,
    TRAILER_WHEEL_RF   = 2,
    TRAILER_WHEEL_RM   = 3,
    TRAILER_WHEEL_RB   = 4,
    TRAILER_WHEEL_LF   = 5,
    TRAILER_WHEEL_LM   = 6,
    TRAILER_WHEEL_LB   = 7,
    TRAILER_DOOR_RF    = 8,
    TRAILER_DOOR_RR    = 9,
    TRAILER_DOOR_LF    = 10,
    TRAILER_DOOR_LR    = 11,
    TRAILER_BUMP_FRONT = 12,
    TRAILER_BUMP_REAR  = 13,
    TRAILER_WING_RF    = 14,
    TRAILER_WING_LF    = 15,
    TRAILER_BONNET     = 16,
    TRAILER_BOOT       = 17,
    TRAILER_WINDSCREEN = 18,
    TRAILER_EXHAUST    = 19,
    TRAILER_MISC_A     = 20,
    TRAILER_MISC_B     = 21,
    TRAILER_MISC_C     = 22,

    TRAILER_NUM_NODES
};

class CTrailer : public CAutomobile {
public:
    CColPoint m_aTrailerColPoints[2];
    float     m_fTrailerColPointValue1;
    float     m_fTrailerColPointValue2;
    float     m_fHeight; // 0x6CF3DC, 0x6CFC11
    float     m_fTrailerTowedRatio;
    float     m_fTrailerTowedRatio2;

    static constexpr auto Type = VEHICLE_TYPE_TRAILER;

public:
    CTrailer(int32 modelIndex, eVehicleCreatedBy createdBy);
    ~CTrailer() override = default; // 0x6CED10

    bool SetTowLink(CVehicle* tractor, bool setMyPosToTowBar) override;
    void ScanForTowLink();

    void SetupSuspensionLines() override;
    void ResetSuspension() override;
    void ProcessSuspension() override;

    int32 ProcessEntityCollision(CEntity* entity, CColPoint* colPoint) override;
    void  ProcessControl() override;
    bool  ProcessAI(uint32& extraHandlingFlags) override;

    void  PreRender() override;

    bool  GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) override;
    bool  GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) override;
    bool  BreakTowLink() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTrailer* Constructor(int32 modelIndex, eVehicleCreatedBy createdBy) { this->CTrailer::CTrailer(modelIndex, createdBy); return this; }
    bool SetTowLink_Reversed(CVehicle* targetVehicle, bool arg1) { return CTrailer::SetTowLink(targetVehicle, arg1); }
    void SetupSuspensionLines_Reversed() { CTrailer::SetupSuspensionLines(); }
    void ResetSuspension_Reversed() { CTrailer::ResetSuspension(); }
    void ProcessSuspension_Reversed() { CTrailer::ProcessSuspension(); }
    void ProcessControl_Reversed() { CTrailer::ProcessControl(); }
    bool ProcessAI_Reversed(uint32& extraHandlingFlags) { return CTrailer::ProcessAI(extraHandlingFlags); }
    void PreRender_Reversed() { CTrailer::PreRender(); }
    bool GetTowHitchPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) { return CTrailer::GetTowHitchPos(outPos, bCheckModelInfo, vehicle); }
    bool GetTowBarPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) { return CTrailer::GetTowBarPos(outPos, bCheckModelInfo, vehicle); }
    bool BreakTowLink_Reversed() { return CTrailer::BreakTowLink(); }

};

VALIDATE_SIZE(CTrailer, 0x9F4);
