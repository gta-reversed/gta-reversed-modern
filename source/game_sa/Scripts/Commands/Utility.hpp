#pragma once

/*!
* Various utility commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GENERATE_RANDOM_INT>() { // 0x099
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->iParam = CGeneral::GetRandomNumber();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_CAR_DRIVING_STYLE>() { // 0x0AE
    CollectParameters(2);
    auto* vehicle = GetVehiclePool()->GetAtRef(ScriptParams[0].iParam);
    assert(vehicle);
    vehicle->m_autoPilot.m_nCarDrivingStyle = static_cast<eCarDrivingStyle>(ScriptParams[1].u8Param);
    return OR_CONTINUE;
}
