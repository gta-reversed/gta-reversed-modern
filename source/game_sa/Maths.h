#pragma once

class CMaths {
public:
    static float (&ms_SinTable)[256];

    static void InjectHooks();

    static void InitMathsTables();
};
