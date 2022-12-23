#pragma once

#include "Radar.h"
#include "MenuManager.h"
#include "CommandParser/Parser.hpp"

/*!
* Various CLEO world commands
*/

CVector GetCheckpointBlipCoords() {
    // TODO: original CLEO library also sets the result flag, do it.
    const auto blipIdx = CRadar::GetActualBlipArrayIndex(FrontEndMenuManager.m_nTargetBlipIndex);
    if (blipIdx == -1)
        return {};

    if (const auto& trace = CRadar::ms_RadarTrace[blipIdx]; trace.m_nBlipDisplayFlag != BLIP_DISPLAY_NEITHER) {
        return trace.m_vPosition;
    }

    return {};
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_TARGET_BLIP_COORDS, GetCheckpointBlipCoords);
