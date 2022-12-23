#pragma once

#include "CommandParser/Parser.hpp"
using namespace notsa::script;
/*!
* Various camera commands
*/

bool IsPointOnScreen(CVector pos, float radius) {
    if (pos.z <= MAP_Z_LOW_LIMIT) {
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
    }
    return TheCamera.IsSphereVisible(&pos, radius);
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_POINT_ON_SCREEN, IsPointOnScreen);

void ShakeCam(float strength) {
    CamShakeNoPos(&TheCamera, strength / 1000.0f);
}
REGISTER_COMMAND_HANDLER(COMMAND_SHAKE_CAM, ShakeCam);

void AttachCameraToVehicleLookAtVehicle(CVehicle& attachTo, CVector offset, CVehicle& lookAt, float tilt, eSwitchType switchType) {
    CVector zero{};
    TheCamera.TakeControlAttachToEntity(
        &lookAt,
        &attachTo,
        &offset,
        &zero,
        tilt,
        switchType,
        1
    );
}
REGISTER_COMMAND_HANDLER(COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_VEHICLE, AttachCameraToVehicleLookAtVehicle);
