#pragma once

class CMouseControllerState {
public:
    unsigned char lmb;
    unsigned char rmb;
    unsigned char mmb;
    unsigned char wheelUp;
    unsigned char wheelDown;
    unsigned char bmx1;
    unsigned char bmx2;
    char __align;
    float Z;
    float X;
    float Y;

public:
    static void InjectHooks();

    CMouseControllerState();
    CMouseControllerState* Constructor();

    void Clear();
    bool CheckForInput();
};

VALIDATE_SIZE(CMouseControllerState, 0x14);
