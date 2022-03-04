/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

struct tTransmissionGear {
    float m_maxVelocity;
    float m_changeUpVelocity;   // max velocity needed to change the current gear to higher
    float m_changeDownVelocity; // min velocity needed to change the current gear to lower
};

VALIDATE_SIZE(tTransmissionGear, 0xC);
