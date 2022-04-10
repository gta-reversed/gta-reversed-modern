#pragma once

#include "ListItem_c.h"
#include "Vector.h"

class FxSystem_c;

struct Particle_c : public ListItem_c {
    int           field_8;
    int           field_C;
    CVector       f10;
    int           field_1C;
    int           field_20;
    int           field_24;
    FxSystem_c*   m_System;
};
VALIDATE_SIZE(Particle_c, 0x2C);
