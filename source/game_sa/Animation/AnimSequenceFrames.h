#pragma once

#include "Quaternion.h"

#include <extensions/FixedVector.hpp>
#include <extensions/FixedQuat.hpp>

union Quat16 { // 4096
    struct {
        int16 m_wQuatX;
        int16 m_wQuatY;
        int16 m_wQuatZ;
        int16 m_wQuatW;
    };
    int16 rot[4];
};

union Vec16 { // 1024
    struct {
        int16 m_wTranslationX;
        int16 m_wTranslationY;
        int16 m_wTranslationZ;
    };
    int16 trans[3];
};

/*
 * KeyFrame -> CAnimSequenceChildFrameUncompressed
 * KeyFrameTrans -> CAnimSequenceRootFrameUncompressed
 *
 * KeyFrameCompressed -> CAnimSequenceChildFrameCompressed
 * KeyFrameTransCompressed -> CAnimSequenceRootFrameCompressed
 * */

struct KeyFrame {
    CQuaternion Rot;
    float       DeltaTime; //< Relative to previous key frame

    void SetDeltaTime(float t) { DeltaTime = t; }
};

struct KeyFrameTrans : KeyFrame {
    CVector Trans;
};

struct KeyFrameCompressed {
    FixedQuat<int16, 4096.f> Rot;
    FixedFloat<int16, 60.f>  DeltaTime;

    void SetDeltaTime(float compressedTime) { DeltaTime.Set(compressedTime, true); }
};

struct KeyFrameTransCompressed : KeyFrameCompressed {
    FixedVector<int16, 1024.f> Trans;
};

VALIDATE_SIZE(KeyFrameCompressed, 0xA);
VALIDATE_SIZE(KeyFrameTransCompressed, 0x10);
VALIDATE_SIZE(KeyFrame, 0x14);
VALIDATE_SIZE(KeyFrameTrans, 0x20);
