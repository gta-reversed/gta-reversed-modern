#include "StdInc.h"

void CControllerState::InjectHooks() {
    Install("CControllerState", "Clear", 0x53EF80, &CControllerState::Clear);
    Install("CControllerState", "CheckForInput", 0x53EFF0, &CControllerState::CheckForInput);
}

// 0x53EF80
void CControllerState::Clear() {
    RightStickY = 0;
    RightStickX = 0;
    LeftStickY = 0;
    LeftStickX = 0;
    RightShoulder2 = 0;
    RightShoulder1 = 0;
    LeftShoulder2 = 0;
    LeftShoulder1 = 0;
    DPadRight = 0;
    DPadLeft = 0;
    DPadDown = 0;
    DPadUp = 0;
    Select = 0;
    Start = 0;
    ButtonCircle = 0;
    ButtonCross = 0;
    ButtonTriangle = 0;
    ButtonSquare = 0;
    ShockButtonR = 0;
    ShockButtonL = 0;
    m_bChatIndicated = 0;
    m_bPedWalk = 0;
    m_bVehicleMouseLook = 0;
    m_bRadioTrackSkip = 0;
}

// 0x53EFF0
bool CControllerState::CheckForInput() {
    return (
        RightStickX
        || RightStickY
        || LeftStickX
        || LeftStickY
        || DPadUp
        || DPadDown
        || DPadLeft
        || DPadRight
        || ButtonTriangle
        || ButtonCross
        || ButtonCircle
        || ButtonSquare
        || Start
        || Select
        || LeftShoulder1
        || LeftShoulder2
        || RightShoulder1
        || RightShoulder2
        || ShockButtonL
        || ShockButtonR
    );
}
