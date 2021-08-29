/*
    Plugin-SDK (Grand Theft Auto) SHARED header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct RwRGBA;

class CRGBA {
public:
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;

    CRGBA(uint8 red, uint8 green, uint8 blue);
    CRGBA(uint8 red, uint8 green, uint8 blue, uint8 alpha);
    CRGBA(CRGBA const& rhs);
    CRGBA(uint32 intValue);
    CRGBA(RwRGBA const& rhs);
    CRGBA();

    void Set(uint8 red, uint8 green, uint8 blue);
    void Set(uint8 red, uint8 green, uint8 blue, uint8 alpha);
    void Set(uint32 intValue);
    void Set(CRGBA const& rhs);
    void Set(CRGBA const& rhs, uint8 alpha);
    void Set(RwRGBA const& rwcolor);

    CRGBA ToRGB() const;
    uint32 ToInt() const;
    uint32 ToIntARGB() const;
    RwRGBA ToRwRGBA() const;

    void FromRwRGBA(RwRGBA const& rwcolor);
    void FromARGB(uint32 intValue);

    void Invert();
    CRGBA Inverted() const;

    bool operator==(CRGBA const& rhs) const;
    CRGBA& operator=(CRGBA const& rhs);

    CRGBA operator*(float mult) {
        return {
            (uint8_t)((float)r * mult),
            (uint8_t)((float)g * mult),
            (uint8_t)((float)b * mult),
            (uint8_t)((float)a * mult)
        };
    }

    CRGBA operator*(float mult) const {
        return {
            (uint8_t)((float)r * mult),
            (uint8_t)((float)g * mult),
            (uint8_t)((float)b * mult),
            (uint8_t)((float)a * mult)
        };
    }

    CRGBA operator/(float divisor) {
        return *this * (1 / divisor);
    }
};
