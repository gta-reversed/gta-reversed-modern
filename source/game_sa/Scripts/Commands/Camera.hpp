#pragma once

/*!
* Various utility commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_POINT_ON_SCREEN>() { // 0x0C2
    CollectParameters(4);
    CVector pos = CTheScripts::ReadCVectorFromScript(0);
    if (pos.z <= MAP_Z_LOW_LIMIT)
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

    UpdateCompareFlag(TheCamera.IsSphereVisible(&pos, ScriptParams[3].fParam));
    return OR_CONTINUE;
}


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SHAKE_CAM>() { // 0x003 
    CollectParameters(1);
    CamShakeNoPos(&TheCamera, ScriptParams[0].fParam / 1000.0f);
    return OR_CONTINUE;
}

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
REGISTER_PARSED_COMMAND(COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_VEHICLE, AttachCameraToVehicleLookAtVehicle)
