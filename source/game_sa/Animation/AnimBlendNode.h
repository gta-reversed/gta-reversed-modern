/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
// by Github.com / jte
#pragma once

#include "Quaternion.h"

class CAnimBlendNode {
public:
    float m_fTheta0; // angle between two quaternions
    float m_fTheta1; // 1 / sin(m_theta0), used in slerp calculation

    // indices into array in sequence
    int16 m_nNextKeyFrameId;
    int16 m_PreviousKeyFrameId;

    float m_fRemainingTime; // time until frames have to advance

    CAnimBlendSequence*    m_pAnimSequence;
    CAnimBlendAssociation* m_pAnimBlendAssociation;

public:
    static void InjectHooks();

    void Init();

    void CalcTheta(float angle);
    void CalcDeltas();
    void CalcDeltasCompressed();

    bool FindKeyFrame(float time);

    void GetCurrentTranslation(CVector& trans, float weight);
    void GetCurrentTranslationCompressed(CVector& trans, float weight);

    void GetEndTranslation(CVector& trans, float weight);
    void GetEndTranslationCompressed(CVector& trans, float weight);

    bool NextKeyFrame();
    bool NextKeyFrameCompressed();

    bool NextKeyFrameNoCalc();
    bool SetupKeyFrameCompressed();

    bool Update(CVector& trans, CQuaternion& rot, float weight);
    bool UpdateCompressed(CVector& trans, CQuaternion& rot, float weight);

    bool UpdateTime();
};

VALIDATE_SIZE(CAnimBlendNode, 0x18);
