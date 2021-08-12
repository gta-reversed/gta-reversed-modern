/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CAutomobile;

enum eDamageState {
    DAMSTATE_OK = 0,
    DAMSTATE_OPENED = 1,
    DAMSTATE_DAMAGED = 2,
    DAMSTATE_OPENED_DAMAGED = 3,
    DAMSTATE_NOTPRESENT = 4
};

enum tComponent {
    COMPONENT_WHEEL_LF = 1,
    COMPONENT_WHEEL_RF = 2,
    COMPONENT_WHEEL_LR = 3,
    COMPONENT_WHEEL_RR = 4,
    COMPONENT_BONNET = 5,
    COMPONENT_BOOT = 6,
    COMPONENT_DOOR_LF = 7,
    COMPONENT_DOOR_RF = 8,
    COMPONENT_DOOR_LR = 9,
    COMPONENT_DOOR_RR = 10,
    COMPONENT_WING_LF = 11,
    COMPONENT_WING_RF = 12,
    COMPONENT_WING_LR = 13,
    COMPONENT_WING_RR = 14,
    COMPONENT_WINDSCREEN = 15,
    COMPONENT_BUMP_FRONT = 16,
    COMPONENT_BUMP_REAR = 17
};

enum tComponentGroup {
    COMPGROUP_PANEL = 0,
    COMPGROUP_WHEEL = 1,
    COMPGROUP_DOOR = 2,
    COMPGROUP_BONNET = 3,
    COMPGROUP_BOOT = 4,
    COMPGROUP_LIGHT = 5,
    COMPGROUP_NA = 6
};

enum eWheelStatus {
    WHEEL_STATUS_OK = 0,
    WHEEL_STATUS_BURST,
    WHEEL_STATUS_MISSING,
    WHEEL_STATUS_3,
    WHEEL_STATUS_4
};

enum ePanels {
    WING_FRONT_LEFT = 0,
    WING_FRONT_RIGHT = 1,
    WINDSCREEN = 4,
    BUMP_FRONT = 5,
    BUMP_REAR = 6
};

enum eDoors {
    DOOR_BONNET = 0,
    DOOR_BOOT,
    DOOR_LEFT_FRONT,
    DOOR_RIGHT_FRONT,
    DOOR_LEFT_REAR,
    DOOR_RIGHT_REAR,
};

enum eLights {
    LIGHT_FRONT_LEFT = 0,
    LIGHT_FRONT_RIGHT = 1,
    LIGHT_REAR_RIGHT = 2,
    LIGHT_REAR_LEFT = 3
};

class CDamageManager {
public:
    float m_fWheelDamageEffect;
    uint8 m_nEngineStatus;
    union {
        uint8 m_anWheelsStatus[4]; // see eWheelStatus
    };
    union {
        uint8 m_anDoorsStatus[6];
        struct {
            uint8 m_nBonnetStatus;
            uint8 m_nBootStatus;
            uint8 m_nLeftFrontDoorStatus;
            uint8 m_nRightFrontDoorStatus;
            uint8 m_nLeftRearDoorStatus;
            uint8 m_nRightRearDoorStatus;
        };
    };
    union {
        uint32 m_nLightsStatus;
        struct {
            uint32 m_nLeftFrontLightStatus : 2;
            uint32 m_nRightFrontLightStatus : 2;
            uint32 m_nRightRearLightStatus : 2;
            uint32 m_nLeftRearLightStatus : 2;
        };
    };
    uint32 m_nPanelsStatus;

public:
    // damageCompId - eLights/ePanel/... id for this component
    bool GetComponentGroup(tComponent component, tComponentGroup* group, uint8* damageCompId);
    void ResetDamageStatus();
    void SetLightStatus(eLights light, uint32 status);
    uint32 GetLightStatus(eLights light);
    void SetPanelStatus(int32 panel, uint32 status);
    uint32 GetPanelStatus(int32 arg0);
    void SetWheelStatus(int32 wheel, uint32 status) {
        m_anWheelsStatus[wheel] = status;
    }
    uint32 GetWheelStatus(int32 wheel);
    void SetDoorStatus(eDoors door, uint32 status) {
        if (door >= 0 && door < 6)
            m_anDoorsStatus[door] = status;
    }
    uint32 GetDoorStatus(int32 doorNodeIndex);
    uint32 GetDoorStatus(eDoors door);
    // Status is a value between 0-250
    void SetEngineStatus(uint32 status);
    // Status is a value between 0-250
    uint32 GetEngineStatus();
    void SetAeroplaneCompStatus(int32 component, uint32 status);
    uint32 GetAeroplaneCompStatus(int32 component);
    // damageCompId - eLights/ePanel/... id for this component
    bool ProgressDoorDamage(uint8 damageCompId, CAutomobile* car);
    // Empty function
    bool ProgressEngineDamage(float arg0);
    // Set next level of damage to panel
    bool ProgressPanelDamage(uint8 panel);
    // Set next level of damage to panel
    bool ProgressWheelDamage(uint8 wheel);
    // Set next level of damage to aeroplane component
    bool ProgressAeroplaneDamage(uint8 component);
    bool ApplyDamage(CAutomobile* car, tComponent component, float intensity, float arg3);
    void FuckCarCompletely(bool skipWheels);
    // returns -1 if no node for this panel
    int32 GetCarNodeIndexFromPanel(ePanels panel);
    // returns -1 if no node for this door
    int32 GetCarNodeIndexFromDoor(eDoors door);
    void Reset();
};

VALIDATE_SIZE(CDamageManager, 0x18);
