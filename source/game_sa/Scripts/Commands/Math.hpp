#pragma once
#include "CommandParser/Parser.hpp"

/*!
* Various utility commands
*/

float GetDistanceBetweenCoords2D(CVector2D a, CVector2D b) {
    return DistanceBetweenPoints2D(a, b);
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D, GetDistanceBetweenCoords2D);

float GetDistanceBetweenCoords3D(CVector a, CVector b) {
    return DistanceBetweenPoints(a, b);
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D, GetDistanceBetweenCoords3D);

void GenerateRandomInt(CRunningScript* S) {
    S->GetPointerToScriptVariable(VAR_GLOBAL)->iParam = CGeneral::GetRandomNumber();
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT, GenerateRandomInt);

// NOTSA: Originally returns uint32
int32 GenerateRandomIntInRange(int32 min, int32 max) {
    return CGeneral::GetRandomNumberInRange(min, max);
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT_IN_RANGE, GenerateRandomIntInRange);

float GenerateRandomFloatInRange(float min, float max) {
    return CGeneral::GetRandomNumberInRange(min, max);
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE, GenerateRandomFloatInRange);

float Sin(float deg) {
    return std::sinf(DegreesToRadians(deg));
}
REGISTER_COMMAND_HANDLER(COMMAND_SIN, Sin);

float Cos(float deg) {
    return std::cosf(DegreesToRadians(deg));
}
REGISTER_COMMAND_HANDLER(COMMAND_COS, Cos);
