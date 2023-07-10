#pragma once

#include "Quaternion.h"


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
    CQuaternion rotation;
    float deltaTime; // relative to previous key frame
};

struct KeyFrameTrans : KeyFrame {
    CVector translation;
};

struct KeyFrameCompressed {
    int16 rot[4];    // 4096
    int16 deltaTime; // 60

    void GetRotation(CQuaternion* quat) {
        float scale = 1.0f / 4096.0f;
        quat->x = float(rot[0]) * scale;
        quat->y = float(rot[1]) * scale;
        quat->z = float(rot[2]) * scale;
        quat->w = float(rot[3]) * scale;
    }

    void SetRotation(const CQuaternion& quat) {
        rot[0] = int16(quat.x * 4096.0f);
        rot[1] = int16(quat.y * 4096.0f);
        rot[2] = int16(quat.z * 4096.0f);
        rot[3] = int16(quat.w * 4096.0f);
    }

    [[nodiscard]] float GetDeltaTime() const {
        return (float)deltaTime / 60.0f;
    }

    void SetTime(float time) {
        deltaTime = int16(time * 60.0f + 0.5f);
    }
};

struct KeyFrameTransCompressed : KeyFrameCompressed {
    int16 trans[3]; // 1024

    void GetTranslation(CVector* vec) {
        float scale = 1.0f / 1024.0f;
        vec->x = float(trans[0]) * scale;
        vec->y = float(trans[1]) * scale;
        vec->z = float(trans[2]) * scale;
    }

    CVector GetTranslation() {
        CVector out;
        GetTranslation(&out);
        return out;
    }

    void SetTranslation(const CVector& vec) {
        trans[0] = int16(vec.x * 1024.0f);
        trans[1] = int16(vec.y * 1024.0f);
        trans[2] = int16(vec.z * 1024.0f);
    }
};

VALIDATE_SIZE(KeyFrameCompressed, 0xA);
VALIDATE_SIZE(KeyFrameTransCompressed, 0x10);
VALIDATE_SIZE(KeyFrame, 0x14);
VALIDATE_SIZE(KeyFrameTrans, 0x20);
