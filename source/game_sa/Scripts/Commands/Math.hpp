#pragma once
#include "CommandParser/Parser.hpp"

/*!
* Various utility commands
*/

REGISTER_COMMAND_HANDLER(COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D, [](CVector2D a, CVector2D b) { return DistanceBetweenPoints2D(a, b); });

REGISTER_COMMAND_HANDLER(COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D, [](CVector a, CVector b) { return DistanceBetweenPoints(a, b); });

REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT, [](int32& var) { var = CGeneral::GetRandomNumber(); });

REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT_IN_RANGE, [](int32 a, int32 b) { return CGeneral::GetRandomNumberInRange(a, b); });

REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE, [](float a, float b) { return CGeneral::GetRandomNumberInRange(a, b); });

REGISTER_COMMAND_HANDLER(COMMAND_SIN, [](float deg) { return std::sinf(DegreesToRadians(deg)); });

REGISTER_COMMAND_HANDLER(COMMAND_COS, [](float deg) { return std::cosf(DegreesToRadians(deg)); });
