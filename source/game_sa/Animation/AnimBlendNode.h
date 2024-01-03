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
    float m_Theta;       // angle between two quaternions
    float m_InvSinTheta; // 1 / sin(m_Theta), used in slerp calculation

    // Indices into array in sequence
    int16 m_KeyFrameA; // Next key frame
    int16 m_KeyFrameB; // Previous key frame

    float m_RemainingTime; // Time until frames have to advance

    CAnimBlendSequence*    m_BlendSeq;
    CAnimBlendAssociation* m_BlendAssoc;

public:
    static void InjectHooks();

    void Init();

    void CalcTheta(float angle);
    void CalcDeltas();
    void CalcDeltasCompressed();

    bool FindKeyFrame(float time);

    //! @addr 0x4CFC50
    void GetCurrentTranslation(CVector& trans, float weight) { I_GetCurrentTranslation<false>(trans, weight); }

    //! @addr 0x4CFE60
    void GetCurrentTranslationCompressed(CVector& trans, float weight) { I_GetCurrentTranslation<true>(trans, weight); }

    void GetEndTranslation(CVector& trans, float weight);
    void GetEndTranslationCompressed(CVector& trans, float weight);

    bool NextKeyFrame();
    bool NextKeyFrameCompressed();

    bool NextKeyFrameNoCalc();
    bool SetupKeyFrameCompressed();

    bool Update(CVector& trans, CQuaternion& rot, float weight);
    bool UpdateCompressed(CVector& trans, CQuaternion& rot, float weight);

    bool UpdateTime();

private: // Generic implementations
    template<bool IsCompressed>
    NOTSA_FORCEINLINE void I_GetCurrentTranslation(CVector& trans, float weight) {
        trans = CVector{0.0f, 0.0f, 0.0f};

        const auto blend = m_BlendAssoc->GetBlendAmount(weight);
        if (blend <= 0.0f) {
            return;
        }

        const auto kfA = m_BlendSeq->GetKeyFrame<IsCompressed>(m_KeyFrameA),
                   kfB = m_BlendSeq->GetKeyFrame<IsCompressed>(m_KeyFrameB);

        const auto t = (kfA->DeltaTime - m_RemainingTime) / kfA->DeltaTime;

        if (m_BlendSeq->m_bHasTranslation) {
            trans = kfB->Trans + t * (kfA->Trans - kfB->Trans);
            trans *= blend;
        }
    }

};

VALIDATE_SIZE(CAnimBlendNode, 0x18);
