#pragma once

#include "Base.h"

class Furniture_c : public ListItem_c {
public:
    int16 m_nModelId;
    int16 m_nId;
    int8  m_nWidthX;
    int8  m_nWidthY;
    int8  m_nWealthMin;
    int8  m_nWealthMax;
    bool  m_bCanPlaceInFrontOfWindow;
    bool  m_bIsTall;
    bool  m_bCanSteal;
    int8  m_nMaxAng;

public:
    static void InjectHooks();

    Furniture_c() = default;  // 0x590EC0
    ~Furniture_c() = default; // 0x590ED0
};
VALIDATE_SIZE(Furniture_c, 0x14);
