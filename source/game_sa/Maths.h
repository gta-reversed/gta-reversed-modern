#pragma once

class CMaths {
public:
    static float* ms_SinTable;

    static void InjectHooks();

    static void InitMathsTables();
};
