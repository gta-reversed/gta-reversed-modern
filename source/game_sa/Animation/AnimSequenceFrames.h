#pragma once

#include "Quaternion.h"

#include "FixedVector.hpp"
#include "FixedQuat.hpp"


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
};

struct KeyFrameTrans : KeyFrame {
    CVector Trans;
};

struct KeyFrameCompressed {
    FixedQuat<int16, 4096.f> Rot;
    FixedFloat<int16, 60.f>  DeltaTime;

    void GetRotation(CQuaternion* quat) const {
        *quat = Rot;
    }

    void SetRotation(const CQuaternion& quat) {
        Rot = quat;
    }

    [[nodiscard]] float GetDeltaTime() const {
        return DeltaTime;
    }

    void SetTime(float compressedTime) {
        DeltaTime.Set(compressedTime, true); // NOTE/TODO: I don't really think rounding upwards matters that much, but thats how the code was
    }
};

struct KeyFrameTransCompressed : KeyFrameCompressed {
    FixedVector<int16, 1024.f> Trans;

    void GetTranslation(CVector* vec) const {
        *vec = Trans;
    }

    CVector GetTranslation() const {
        return Trans;
    }

    void SetTranslation(const CVector& vec) {
        Trans = vec;
    }
};

VALIDATE_SIZE(KeyFrameCompressed, 0xA);
VALIDATE_SIZE(KeyFrameTransCompressed, 0x10);
VALIDATE_SIZE(KeyFrame, 0x14);
VALIDATE_SIZE(KeyFrameTrans, 0x20);
