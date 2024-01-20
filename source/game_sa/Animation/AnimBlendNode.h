/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
// by Github.com / jte
#pragma once

#include "Quaternion.h"

//! Animation of a single node (bone)
class CAnimBlendNode {
public:
    static void InjectHooks();

    void Init();

    void CalcTheta(float angle);

    //! @addr 0x4D0190
    void CalcDeltas();

    //! @addr 0x4D0350
    void CalcDeltasCompressed();


    //! @addr 0x4CFC50
    void GetCurrentTranslation(CVector& trans, float weight) { return I_GetCurrentTranslation<false>(trans, weight); }

    //! @addr 0x4CFE60
    void GetCurrentTranslationCompressed(CVector& trans, float weight) { return I_GetCurrentTranslation<true>(trans, weight); }


    //! @addr 0x4CFD90 
    void GetEndTranslation(CVector& trans, float weight) { return I_GetEndTranslation<false>(trans, weight); }

    //! @addr 0x4D0000
    void GetEndTranslationCompressed(CVector& trans, float weight) { return I_GetEndTranslation<true>(trans, weight); }


    //! @addr 0x4D04A0
    bool NextKeyFrame() { return I_NextKeyFrame<false>(); }

    //! @addr 0x4D0570
    bool NextKeyFrameCompressed() { return I_NextKeyFrame<true>(); } 

    //! @addr 0x4CFB90
    bool NextKeyFrameNoCalc();


    //! @addr 0x4D06C0
    bool Update(CVector& trans, CQuaternion& rot, float weight) { return I_Update<false>(trans, rot, weight); }

    //! @addr 0x4D08D0
    bool UpdateCompressed(CVector& trans, CQuaternion& rot, float weight) { return I_Update<true>(trans, rot, weight); }

    bool UpdateTime(); // Unused
    bool SetupKeyFrameCompressed();
    bool FindKeyFrame(float time);

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

        const auto t = kfA->DeltaTime != 0.f
            ? (kfA->DeltaTime - m_RemainingTime) / kfA->DeltaTime
            : 0.f;

        if (m_BlendSeq->m_bHasTranslation) {
            trans = lerp<CVector>(kfB->Trans, kfA->Trans, t) * blend;
        }
    }

    template<bool IsCompressed>
    NOTSA_FORCEINLINE void I_GetEndTranslation(CVector& trans, float weight) {
        trans = CVector{ 0.0f, 0.0f, 0.0f };

        float blend = m_BlendAssoc->GetBlendAmount(weight);
        if (blend <= 0.0f) {
            return;
        }

        const auto kf = m_BlendSeq->GetKeyFrame<IsCompressed>(m_BlendSeq->m_FramesNum - 1);
        if (m_BlendSeq->m_bHasTranslation) {
            trans = kf->Trans;
            trans *= blend;
        }
    }

    template<bool IsCompressed>
    NOTSA_FORCEINLINE bool I_NextKeyFrame() {
        if (m_BlendSeq->m_FramesNum <= 1) {
            return false;
        }

        // Store old KF
        m_KeyFrameB = m_KeyFrameA;

        // Advance as long as we have to
        bool looped = false;
        while (m_RemainingTime <= 0.0f) {
            m_KeyFrameA++;

            if (m_KeyFrameA >= m_BlendSeq->m_FramesNum) {
                if (!m_BlendAssoc->IsRepeating()) { // Reached end of animation
                    m_KeyFrameA--;
                    m_RemainingTime = 0.0f;
                    return false;
                }
                looped      = true;
                m_KeyFrameA = 0;
            }

            m_RemainingTime += m_BlendSeq->GetKeyFrame<IsCompressed>(m_KeyFrameA)->DeltaTime;
        }

        m_KeyFrameB = m_KeyFrameA - 1;
        if (m_KeyFrameB < 0) {
            m_KeyFrameB += m_BlendSeq->m_FramesNum;
        }

        if constexpr (IsCompressed) {
            CalcDeltasCompressed();
        } else {
            CalcDeltas();
        }

        return looped;
    }

    template<bool IsCompressed>
    NOTSA_FORCEINLINE bool I_Update(CVector& trans, CQuaternion& rot, float weight) {
        bool looped = false;

        trans = CVector{0.0f, 0.0f, 0.0f};
        rot   = CQuaternion{0.0f, 0.0f, 0.0f, 0.0f};

        if (m_BlendAssoc->IsRunning()) {
            m_RemainingTime -= m_BlendAssoc->m_TimeStep;
            if (m_RemainingTime <= 0.0f) {
                looped = I_NextKeyFrame<IsCompressed>();
            }
        }
        
        float blend = m_BlendAssoc->GetBlendAmount(weight);
        if (blend > 0.0f) {
            const auto kfA = m_BlendSeq->GetKeyFrame<IsCompressed>(m_KeyFrameA);
            const auto kfB = m_BlendSeq->GetKeyFrame<IsCompressed>(m_KeyFrameB);

            // Calculate interpolation t
            const float t = kfA->DeltaTime != 0.0f
                ? (kfA->DeltaTime - m_RemainingTime) / kfA->DeltaTime
                : 0.0f;

            // Update translation
            if (m_BlendSeq->m_bHasTranslation) {
                trans = lerp<CVector>(kfB->Trans, kfA->Trans, t) * blend;
            }

            // Update rotation
            if (m_BlendSeq->m_bHasRotation) {
                rot.Slerp(kfB->Rot, kfA->Rot, m_Theta, m_InvSinTheta, t);
                rot *= blend;
            }
        }

        return looped;
    }

public:
    float m_Theta;       // angle between two quaternions
    float m_InvSinTheta; // 1 / sin(m_Theta), used in slerp calculation

    // Indices into `m_BlendSeq`
    int16 m_KeyFrameA; // Next key frame
    int16 m_KeyFrameB; // Previous key frame

    float m_RemainingTime; // Time until frames have to advance

    CAnimBlendSequence*    m_BlendSeq;
    CAnimBlendAssociation* m_BlendAssoc;
};
VALIDATE_SIZE(CAnimBlendNode, 0x18);
