#pragma once

class CVector;

class CWaterCannons
{
public:
    static void Init();
    static void UpdateOne(uint32_t id, CVector* start, CVector* end);
};
