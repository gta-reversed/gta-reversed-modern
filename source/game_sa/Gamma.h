/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CGamma {
public:
    uint32 field_0;
    float  field_4;
    float  field_8;
    float  field_C;

public:
    static void InjectHooks();

    void Init();
    void SetGamma(float arg1, bool arg2);
};

VALIDATE_SIZE(CGamma, 0x10);

extern CGamma& gamma;
