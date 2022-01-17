#include "StdInc.h"

#include "DamageManager.h"

void CDamageManager::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CDamageManager", "Init", 0x6A0520, &CDamageManager::Init);
    Install("CDamageManager", "ResetDamageStatusAndWheelDamage", 0x6A04E0, &CDamageManager::ResetDamageStatusAndWheelDamage);
    Install("CDamageManager", "FuckCarCompletely", 0x6C25D0, &CDamageManager::FuckCarCompletely); 
    Install("CDamageManager", "ApplyDamage", 0x6C24B0, &CDamageManager::ApplyDamage); 
    Install("CDamageManager", "ProgressAeroplaneDamage", 0x6C2460, &CDamageManager::ProgressAeroplaneDamage); 
    Install("CDamageManager", "ProgressWheelDamage", 0x6C2440, &CDamageManager::ProgressWheelDamage); 
    Install("CDamageManager", "ProgressPanelDamage", 0x6C23C0, &CDamageManager::ProgressPanelDamage); 
    Install("CDamageManager", "ProgressEngineDamage", 0x6C23B0, &CDamageManager::ProgressEngineDamage); 
    Install("CDamageManager", "ProgressDoorDamage", 0x6C2320, &CDamageManager::ProgressDoorDamage); 
    Install("CDamageManager", "GetAeroplaneCompStatus", 0x6C2300, &CDamageManager::GetAeroplaneCompStatus); 
    Install("CDamageManager", "SetAeroplaneCompStatus", 0x6C22D0, &CDamageManager::SetAeroplaneCompStatus); 
    Install("CDamageManager", "GetEngineStatus", 0x6C22C0, &CDamageManager::GetEngineStatus); 
    Install("CDamageManager", "SetEngineStatus", 0x6C22A0, &CDamageManager::SetEngineStatus); 
    Install("CDamageManager", "GetCarNodeIndexFromPanel", 0x6C26A0, &CDamageManager::GetCarNodeIndexFromPanel); 
    Install("CDamageManager", "GetDoorStatus_Component", 0x6C2250, &CDamageManager::GetDoorStatus_Component); 
    Install("CDamageManager", "GetDoorStatus", 0x6C2230, &CDamageManager::GetDoorStatus); 
    Install("CDamageManager", "SetDoorStatus_Component", 0x6C21E0, &CDamageManager::SetDoorStatus_Component); 
    Install("CDamageManager", "SetDoorStatus", 0x6C21C0, &CDamageManager::SetDoorStatus); 
    Install("CDamageManager", "GetWheelStatus", 0x6C21B0, &CDamageManager::GetWheelStatus); 
    Install("CDamageManager", "SetWheelStatus", 0x6C21A0, &CDamageManager::SetWheelStatus); 
    Install("CDamageManager", "GetPanelStatus", 0x6C2180, &CDamageManager::GetPanelStatus); 
    Install("CDamageManager", "SetPanelStatus", 0x6C2150, &CDamageManager::SetPanelStatus); 
    Install("CDamageManager", "GetLightStatus", 0x6C2130, &CDamageManager::GetLightStatus); 
    Install("CDamageManager", "SetLightStatus", 0x6C2100, &CDamageManager::SetLightStatus); 
    Install("CDamageManager", "ResetDamageStatus", 0x6C20E0, &CDamageManager::ResetDamageStatus); 
    Install("CDamageManager", "GetComponentGroup", 0x6C2040, &CDamageManager::GetComponentGroup); 
    Install("CDamageManager", "GetCarNodeIndexFromDoor", 0x6C26F0, &CDamageManager::GetCarNodeIndexFromDoor);
}

// 0x6A0520
void CDamageManager::Init() {
    m_fWheelDamageEffect = 0.0f;
    ResetDamageStatus(); /* R* used memset here, but let's be a more elegant than that. */
}

// 0x6A04E0
void CDamageManager::ResetDamageStatusAndWheelDamage() {
    ResetDamageStatus();
    m_fWheelDamageEffect = 0.5f;
}

// 0x6C25D0
void CDamageManager::FuckCarCompletely(bool bDontDetachWheel) {
    if (!bDontDetachWheel)
        SetWheelStatus((eCarWheel)CGeneral::GetRandomNumberInRange(0, eCarWheel::MAX_CARWHEELS), eCarWheelStatus::WHEEL_STATUS_MISSING);

    for (size_t i = 0; i < eDoors::MAX_DOORS; i++)
        SetDoorStatus((eDoors)i, eDoorStatus::DAMSTATE_NOTPRESENT);

    for (size_t i = 0; i < 3; i++) {
        ProgressPanelDamage(ePanels::FRONT_BUMPER);
        ProgressPanelDamage(ePanels::REAR_BUMPER);
    }

    for (size_t i = 0; i < eLights::MAX_LIGHTS; i++)
        SetLightStatus((eLights)i, eLightsState::VEHICLE_LIGHT_OK);

    for (size_t i = 0; i < ePanels::MAX_PANELS; i++)
        SetPanelStatus((ePanels)i, ePanelDamageState::DAMSTATE_OK);

    SetEngineStatus(250u);
}

// 0x6C24B0
bool CDamageManager::ApplyDamage(CAutomobile* vehicle, tComponent compId, float fIntensity, float fColDmgMult) {
    if (!vehicle->npcFlags.bTakePanelDamage)
        return false;

    tComponentGroup group{};
    uint8 relCompIdx{};
    GetComponentGroup(compId, group, relCompIdx);

    static constexpr float afPanelDamageMultByGroup[] = { 2.5, 1.25, 3.2, 1.4, 2.5, 2.8, 0.5, 1.2, 0.87, 0.2 };
    fIntensity *= afPanelDamageMultByGroup[(size_t)group];
    if (compId == tComponent::COMPONENT_WINDSCREEN)
        fIntensity *= 0.6f;

    if (fIntensity <= 150.0f)
        return false;

    switch (group) {
    case tComponentGroup::COMPGROUP_PANEL: {
        if (ProgressPanelDamage((ePanels)relCompIdx))
            vehicle->SetBumperDamage((ePanels)relCompIdx, false);
        return true;
    }
    case tComponentGroup::COMPGROUP_WHEEL: {
        ProgressWheelDamage((eCarWheel)relCompIdx);
        break;
    }
    case tComponentGroup::COMPGROUP_DOOR:
    case tComponentGroup::COMPGROUP_BONNET:
    case tComponentGroup::COMPGROUP_BOOT: {
        if (ProgressDoorDamage((eDoors)relCompIdx, vehicle))
            vehicle->SetDoorDamage((eDoors)relCompIdx, false);
        return true;
    }
    case tComponentGroup::COMPGROUP_LIGHT: {
        SetLightStatus((eLights)relCompIdx, eLightsState::VEHICLE_LIGHT_SMASHED);
        if (ProgressPanelDamage((ePanels)relCompIdx))
            vehicle->SetPanelDamage((ePanels)relCompIdx, false);
        return true;
    }
    default:
        return true;
    }
}

// 0x6C2460
bool CDamageManager::ProgressAeroplaneDamage(uint8 nFrameId) {
    const auto current = (ePanelDamageState)GetAeroplaneCompStatus(nFrameId);
    if (current == ePanelDamageState::DAMSTATE_DAMAGED)
        return false;
    SetAeroplaneCompStatus(nFrameId, (ePanelDamageState)((unsigned)current + 1));
    return true;
}

// 0x6C2440
bool CDamageManager::ProgressWheelDamage(eCarWheel wheel) {
    const eCarWheelStatus current = GetWheelStatus(wheel);
    if (current == eCarWheelStatus::WHEEL_STATUS_MISSING)
        return false;
    SetWheelStatus(wheel, (eCarWheelStatus)((unsigned)current + 1));
}

// 0x6C23C0
bool CDamageManager::ProgressPanelDamage(ePanels panel) {
    switch (GetPanelStatus(panel)) {
    case ePanelDamageState::DAMSTATE_DAMAGED:
    {
        switch (panel) {
        case ePanels::WINDSCREEN_PANEL: {
            if (CGeneral::GetRandomNumberInRange(0, 2))
                return false;
            break;
        }
        default: {
            if (CGeneral::GetRandomNumberInRange(0, 8))
                return false;
            break;
        }
        }
        SetPanelStatus(panel, ePanelDamageState::DAMSTATE_OPENED_DAMAGED);
        return true;
    }
    case ePanelDamageState::DAMSTATE_OPENED_DAMAGED: {
        return false;
    }
    }
    SetPanelStatus(panel, (ePanelDamageState)((int)GetPanelStatus(panel) + 1));
    return true;
}

// 0x6C23B0
void CDamageManager::ProgressEngineDamage() {
    /* empty */
}

// 0x6C2320
bool CDamageManager::ProgressDoorDamage(eDoors door, CAutomobile* pAuto) {
    if ((unsigned)door >= (unsigned)eDoors::MAX_DOORS)
        return false;

    switch (GetDoorStatus(door)) {
    case eDoorStatus::DAMSTATE_OK:
    case eDoorStatus::DAMSTATE_OPENED: {
        pAuto->GetDoor(door).Open(0.0f);
        SetDoorStatus(door, eDoorStatus::DAMSTATE_DAMAGED);
        break;
    }
    case eDoorStatus::DAMSTATE_DAMAGED: {
        SetDoorStatus(door, eDoorStatus::DAMSTATE_OPENED_DAMAGED);
        break;
    }
    case eDoorStatus::DAMSTATE_OPENED_DAMAGED: {
        if (CGeneral::GetRandomNumberInRange(0, 8))
            return false;
        SetDoorStatus(door, eDoorStatus::DAMSTATE_NOTPRESENT);
        break;
    }
    case eDoorStatus::DAMSTATE_NOTPRESENT:
        return false;
    }

    /* this original code replaced by SetDoorStatus in upper switch
    if (door < 6u)
        m_aDoorsStatus[door] = status;
    */

    return true;
}

// 0x6C2300
uint8 CDamageManager::GetAeroplaneCompStatus(uint8 frame) {
    return m_nPanelsStatus >> (2 * (m_nPanelsStatus - 12)) & 3;
}

// 0x6C22D0
void CDamageManager::SetAeroplaneCompStatus(uint8 frame, ePanelDamageState status) {
    const auto component = frame - 12;
    m_nPanelsStatus = (status << (2 * component)) | m_nPanelsStatus & ~(3 << (2 * component));
}

// 0x6C22C0
uint8 CDamageManager::GetEngineStatus() {
    return m_nEngineStatus;
}

// 0x6C22A0
void CDamageManager::SetEngineStatus(uint8 status) {
    m_nEngineStatus = std::min<uint8>(status, 250u);
}

// 0x6C26A0
eCarNodes CDamageManager::GetCarNodeIndexFromPanel(ePanels panel) {
    switch (panel) {
    case ePanels::FRONT_LEFT_PANEL:
        return eCarNodes::CAR_WING_LF;
    case ePanels::FRONT_RIGHT_PANEL:
        return eCarNodes::CAR_WING_RF;
    case ePanels::WINDSCREEN_PANEL:
        return eCarNodes::CAR_WINDSCREEN;
    case ePanels::FRONT_BUMPER:
        return eCarNodes::CAR_BUMP_FRONT;
    case ePanels::REAR_BUMPER:
        return eCarNodes::CAR_BUMP_REAR;
    default:
        return (eCarNodes)-1;
    }
}

// 0x6C2250
eDoorStatus CDamageManager::GetDoorStatus_Component(tComponent doorComp) {
    /* Enums don't seem to match up... */
    switch (doorComp) {
    case tComponent::COMPONENT_DOOR_RF:
        return GetDoorStatus(eDoors::DOOR_RIGHT_FRONT);
    case tComponent::COMPONENT_DOOR_LR:
        return GetDoorStatus(eDoors::DOOR_RIGHT_REAR);
    case tComponent::COMPONENT_DOOR_RR:
        return GetDoorStatus(eDoors::DOOR_LEFT_FRONT);
    case tComponent::COMPONENT_WING_LF:
        return GetDoorStatus(eDoors::DOOR_LEFT_REAR);
    default:
        return eDoorStatus::DAMSTATE_NOTPRESENT;
    }
}

// 0x6C21E0
void CDamageManager::SetDoorStatus_Component(tComponent doorComp, eDoorStatus status) {
    switch (doorComp) {
    case tComponent::COMPONENT_DOOR_RF:
        SetDoorStatus(eDoors::DOOR_RIGHT_FRONT, status);
        break;
    case tComponent::COMPONENT_DOOR_LR:
        SetDoorStatus(eDoors::DOOR_RIGHT_REAR, status);
        break;
    case tComponent::COMPONENT_DOOR_RR:
        SetDoorStatus(eDoors::DOOR_LEFT_FRONT, status);
        break;
    case tComponent::COMPONENT_WING_LF:
        SetDoorStatus(eDoors::DOOR_LEFT_REAR, status);
        break;
    }
}

// 0x6C21C0
void CDamageManager::SetDoorStatus(eDoors door, eDoorStatus status) {
    switch (door) {
    case eDoors::DOOR_BONNET:
    case eDoors::DOOR_BOOT:
    case eDoors::DOOR_LEFT_FRONT:
    case eDoors::DOOR_RIGHT_FRONT:
    case eDoors::DOOR_LEFT_REAR:
    case eDoors::DOOR_RIGHT_REAR:
        m_aDoorsStatus[(unsigned)door] = status;
        break;
    }
}

// 0x6C21B0
eCarWheelStatus CDamageManager::GetWheelStatus(eCarWheel wheel) {
    return m_anWheelsStatus[(unsigned)wheel];
}

// 0x6C21A0
void CDamageManager::SetWheelStatus(eCarWheel wheel, eCarWheelStatus status) {
    m_anWheelsStatus[(unsigned)wheel] = status;
}

// 0x6C2180
ePanelDamageState CDamageManager::GetPanelStatus(ePanels panel) {
    return (ePanelDamageState)((m_nPanelsStatus >> (4 * (unsigned)panel)) & 0xF);
}

// 0x6C2150
void CDamageManager::SetPanelStatus(ePanels panel, ePanelDamageState status) {
    m_nPanelsStatus = (status << (4 * (unsigned)panel)) | m_nPanelsStatus & ~(15 << (4 * (unsigned)panel));
}

// 0x6C2130
eLightsState CDamageManager::GetLightStatus(eLights light) {
    return (eLightsState)((m_nLightsStatus >> (2 * (unsigned)light)) & 3);
}

// 0x6C2100
void CDamageManager::SetLightStatus(eLights light, eLightsState status) {
    m_nLightsStatus = ((unsigned)status << (2 * (unsigned)light)) | m_nLightsStatus & ~(3 << (2 * (unsigned)light));
}

// 0x6C20E0
void CDamageManager::ResetDamageStatus() {
    SetEngineStatus(0);

    for (size_t i = 0; i < eCarWheel::MAX_CARWHEELS; i++)
        SetWheelStatus((eCarWheel)i, eCarWheelStatus::WHEEL_STATUS_OK);

    for (size_t i = 0; i < eDoors::MAX_DOORS; i++)
        SetDoorStatus((eDoors)i, eDoorStatus::DAMSTATE_OK);

    for (size_t i = 0; i < eLights::MAX_LIGHTS; i++)
        SetLightStatus((eLights)i, eLightsState::VEHICLE_LIGHT_OK);

    for (size_t i = 0; i < ePanels::MAX_PANELS; i++)
        SetPanelStatus((ePanels)i, ePanelDamageState::DAMSTATE_OK);
}

// 0x6C2040
bool CDamageManager::GetComponentGroup(tComponent nComp, tComponentGroup& outCompGroup, uint8& outComponentRelativeIdx) {
    outComponentRelativeIdx = (uint8)-2;
    switch (nComp) {
    case tComponent::COMPONENT_WHEEL_LF:
    case tComponent::COMPONENT_WHEEL_RF:
    case tComponent::COMPONENT_WHEEL_LR:
    case tComponent::COMPONENT_WHEEL_RR: {
        outCompGroup = tComponentGroup::COMPGROUP_WHEEL;
        outComponentRelativeIdx = (uint8)nComp - 1;
        return true;
    }
    case tComponent::COMPONENT_BONNET: {
        outCompGroup = tComponentGroup::COMPGROUP_BONNET;
        outComponentRelativeIdx = (uint8)eDoors::DOOR_BONNET;
        return true;
    }
    case tComponent::COMPONENT_BOOT: {
        outCompGroup = tComponentGroup::COMPGROUP_BOOT;
        outComponentRelativeIdx = (uint8)eDoors::DOOR_BOOT;
        return true;
    }
    case tComponent::COMPONENT_DOOR_LF:
    case tComponent::COMPONENT_DOOR_RF:
    case tComponent::COMPONENT_DOOR_LR:
    case tComponent::COMPONENT_DOOR_RR: {
        outCompGroup = tComponentGroup::COMPGROUP_DOOR;
        outComponentRelativeIdx = (uint8)nComp - (uint8)tComponent::COMPONENT_BONNET;
        return true;
    }
    case tComponent::COMPONENT_WING_LF:
    case tComponent::COMPONENT_WING_RF:
    case tComponent::COMPONENT_WING_LR:
    case tComponent::COMPONENT_WING_RR: 
    case tComponent::COMPONENT_WINDSCREEN: {
        outCompGroup = tComponentGroup::COMPGROUP_LIGHT;
        outComponentRelativeIdx = (uint8)nComp - (uint8)tComponent::COMPONENT_WING_LF;
        return true;
    }
    case tComponent::COMPONENT_BUMP_FRONT:
    case tComponent::COMPONENT_BUMP_REAR: {
        outCompGroup = tComponentGroup::COMPGROUP_PANEL;
        outComponentRelativeIdx = (uint8)nComp - (uint8)tComponent::COMPONENT_WING_LF;
        return true;
    }
    case tComponent::COMPONENT_NA: {
        outCompGroup = tComponentGroup::COMPGROUP_NA;
        outComponentRelativeIdx = 0;
        return true;
    }
    }
    return false;
}

// 0x6C2230
eDoorStatus CDamageManager::GetDoorStatus(eDoors nDoorIdx) {
    switch (nDoorIdx) {
    case eDoors::DOOR_BONNET:
    case eDoors::DOOR_BOOT:
    case eDoors::DOOR_LEFT_FRONT:
    case eDoors::DOOR_RIGHT_FRONT:
    case eDoors::DOOR_LEFT_REAR:
    case eDoors::DOOR_RIGHT_REAR:
        return m_aDoorsStatus[(unsigned)nDoorIdx];
    default:
        return eDoorStatus::DAMSTATE_NOTPRESENT;
    }
}

// 0x6C26F0
eCarNodes CDamageManager::GetCarNodeIndexFromDoor(eDoors door) {
    switch (door) {
    case eDoors::DOOR_BONNET:
        return eCarNodes::CAR_BONNET;
    case eDoors::DOOR_BOOT:
        return eCarNodes::CAR_BOOT;
    case eDoors::DOOR_LEFT_FRONT:
        return eCarNodes::CAR_DOOR_LF;
    case eDoors::DOOR_RIGHT_FRONT:
        return eCarNodes::CAR_DOOR_RF;
    case eDoors::DOOR_LEFT_REAR:
        return eCarNodes::CAR_DOOR_LR;
    case eDoors::DOOR_RIGHT_REAR:
        return eCarNodes::CAR_DOOR_RR;
    default:
        return (eCarNodes)-1;
    }
}
