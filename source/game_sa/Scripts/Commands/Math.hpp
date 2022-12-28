#pragma once
#include "CommandParser/Parser.hpp"

/*!
* Various utility commands
*/

auto GetDistanceBetweenCoords2d(CVector2D a, CVector2D b) {
    return DistanceBetweenPoints2D(a, b);
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D, GetDistanceBetweenCoords2d);

auto GetDistanceBetweenCoords3d(CVector a, CVector b) {
    return DistanceBetweenPoints(a, b);
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D, GetDistanceBetweenCoords3d);

auto GenerateRandomInt(int32& var) {
    var = CGeneral::GetRandomNumber();
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT, GenerateRandomInt);

auto GenerateRandomIntInRange(int32 a, int32 b) {
    return CGeneral::GetRandomNumberInRange(a, b);
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT_IN_RANGE, GenerateRandomIntInRange);

auto GenerateRandomFloatInRange(float a, float b) {
    return CGeneral::GetRandomNumberInRange(a, b);
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE, GenerateRandomFloatInRange);

auto Sin(float deg) {
    return std::sinf(DegreesToRadians(deg));
}
REGISTER_COMMAND_HANDLER(COMMAND_SIN, Sin);

auto Cos(float deg) {
    return std::cosf(DegreesToRadians(deg));
}
REGISTER_COMMAND_HANDLER(COMMAND_COS, Cos);
