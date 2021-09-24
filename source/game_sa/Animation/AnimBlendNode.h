/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Quaternion.h"

class CAnimBlendNode {
public:
    // by Github.com / jte
    float                  m_theta0; // angle between two quaternions
    float                  m_theta1; // 1 / sin(m_theta0), used in slerp calculation
    int16                  m_endKeyFrameId;
    int16                  m_startKeyFrameId;
    float                  m_timeDelta;
    CAnimBlendSequence*    m_pAnimSequence;
    CAnimBlendAssociation* m_pAnimBlendAssociation;

public:
    void CalcDeltas();
    void CalcDeltasCompressed();
    bool FindKeyFrame(float arg1);
    void GetCurrentTranslation(CVector& Vector, float arg2);
    void GetCurrentTranslationCompressed(CVector& Vector, float arg2);
    void GetEndTranslation(CVector& Vector, float arg2);
    void GetEndTranslationCompressed(CVector& Vector, float arg2);
    void Init();
    bool NextKeyFrame();
    bool NextKeyFrameCompressed();
    bool NextKeyFrameNoCalc();
    bool SetupKeyFrameCompressed();
    bool Update(CVector& Vector, CQuaternion& Qauternion, float arg3);
    bool UpdateCompressed(CVector& Vector, CQuaternion& Quaternion, float arg3);
};

VALIDATE_SIZE(CAnimBlendNode, 0x18);
