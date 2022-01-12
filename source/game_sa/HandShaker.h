#pragma once

class CHandShaker {
public:
    CVector vec;
    CVector vec1;
    CVector vec2;
    CVector vec3;
    CVector vec4;
    CMatrix matrix;
    float   f84;
    float   f88;
    int32   n8C;
    float   f90;

public:
    static void InjectHooks();

    CHandShaker() { SetDefaults(); } // 0x517740
    ~CHandShaker() = default;        // 0x509810

    void SetDefaults();
    void Reset();
    void Process(float a1);
};

VALIDATE_SIZE(CHandShaker, 0x94);

extern CHandShaker*& gHandShaker;