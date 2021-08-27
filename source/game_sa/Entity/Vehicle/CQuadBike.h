/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CAutomobile.h"
#include "CRideAnimData.h"

enum eQuadBikeNodes {
    QUAD_NODE_NONE = 0,
    QUAD_CHASSIS = 1,
    QUAD_WHEEL_RF = 2,
    QUAD_WHEEL_RM = 3,
    QUAD_WHEEL_RB = 4,
    QUAD_WHEEL_LF = 5,
    QUAD_WHEEL_LM = 6,
    QUAD_WHEEL_LB = 7,
    QUAD_DOOR_RF = 8,
    QUAD_DOOR_RR = 9,
    QUAD_DOOR_LF = 10,
    QUAD_DOOR_LR = 11,
    QUAD_BODY_FRONT = 12,
    QUAD_BODY_REAR = 13,
    QUAD_SUSPENSION_RF = 14,
    QUAD_SUSPENSION_LF = 15,
    QUAD_REAR_AXLE = 16,
    QUAD_HANDLEBARS = 17,
    QUAD_MISC_A = 18,
    QUAD_MISC_B = 19,
    QUAD_NUM_NODES
};

class CQuadBike : public CAutomobile {
protected:
    CQuadBike(plugin::dummy_func_t) : CAutomobile(plugin::dummy) {}
public:
    void*          m_pHandling;
    CRideAnimData  m_sRideAnimData;
    float          field_9A8;
    int            field_9AC;
    int            field_9B0;
    int            field_9B4;
    unsigned char  m_nQuadFlags;
    char           _pad1[3];

public:
    static void InjectHooks();

    CQuadBike(int modelIndex, eVehicleCreatedBy createdBy);

    ~CQuadBike() override;

    void Fix() override;
    CRideAnimData* GetRideAnimData() override;
    void PreRender() override;
    bool ProcessAI(unsigned int& extraHandlingFlags) override;
    void ProcessControl() override;
    void ProcessControlInputs(unsigned char playerNum) override;
    void ProcessDrivingAnims(CPed* driver, unsigned char bBlend) override;
    void ProcessSuspension() override;
    void ResetSuspension() override;
    void SetupDamageAfterLoad() override;
    void SetupSuspensionLines() override;

private:
    void Fix_Reversed();
    CRideAnimData* GetRideAnimData_Reversed();
    void PreRender_Reversed();
    bool ProcessAI_Reversed(unsigned int& extraHandlingFlags);
    void ProcessControl_Reversed();
    void ProcessControlInputs_Reversed(unsigned char playerNum);
    void ProcessDrivingAnims_Reversed(CPed* driver, unsigned char bBlend);
    void ProcessSuspension_Reversed();
    void ResetSuspension_Reversed();
    void SetupDamageAfterLoad_Reversed();
    void SetupSuspensionLines_Reversed();
};

VALIDATE_SIZE(CQuadBike, 0x9BC);

extern bool& bDoQuadDamping; // true 0x8D3450
extern float& QUAD_HBSTEER_ANIM_MULT; // -0.4f 0x8D3454
extern CVector& vecQuadResistance; // { 0.995f, 0.995f, 1.0f } // 0x8D3458