#pragma once

#include "Pad.h"

class CPad;

// Set values to 128 unless otherwise specified
class CControllerState {
public:
    int16 LeftStickX; // move/steer left (-128?)/right (+128)
    int16 LeftStickY; // move back(+128)/forwards(-128?)
    int16 RightStickX; // numpad 6(+128)/numpad 4(-128?)
    int16 RightStickY;

    int16 LeftShoulder1;
    int16 LeftShoulder2;
    int16 RightShoulder1; // target / hand brake
    int16 RightShoulder2;

    int16 DPadUp; // radio change up           Next radio station / Call gang forward/Recruit gang member
    int16 DPadDown; // radio change down       Previous radio station / Gang stay back/Release gang (hold)
    int16 DPadLeft; //                         Skip trip/Action / Negative talk reply
    int16 DPadRight; //                        Next user MP3 track / Positive talk reply

    int16 Start;                             //Pause
    int16 Select;                            //Camera modes

    int16 ButtonSquare; // jump / reverse      Break/Reverse / Jump/Climb
    int16 ButtonTriangle; // get in/out        Exit vehicle / Enter veihcle
    int16 ButtonCross; // sprint / accelerate  Accelerate / Sprint/Swim
    int16 ButtonCircle; // fire                Fire weapon

    int16 ShockButtonL;
    int16 ShockButtonR; // look behind

    int16 m_bChatIndicated;
    int16 m_bPedWalk;
    int16 m_bVehicleMouseLook;
    int16 m_bRadioTrackSkip;

public:
    static void InjectHooks();

    void Clear();
    bool CheckForInput();
};

VALIDATE_SIZE(CControllerState, 0x30);
