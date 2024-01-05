#include "StdInc.h"

#include "AnimBlendNode.h"

void CAnimBlendNode::InjectHooks() {
    RH_ScopedClass(CAnimBlendNode);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Init, 0x4CFB70);
    RH_ScopedInstall(NextKeyFrameNoCalc, 0x4CFB90);
    RH_ScopedInstall(GetCurrentTranslation, 0x4CFC50);
    RH_ScopedInstall(GetCurrentTranslationCompressed, 0x4CFE60);
    RH_ScopedInstall(GetEndTranslation, 0x4CFD90);
    RH_ScopedInstall(GetEndTranslationCompressed, 0x4D0000);
    RH_ScopedInstall(CalcTheta, 0x4D00E0);
    RH_ScopedInstall(UpdateTime, 0x4D0160);
    RH_ScopedInstall(CalcDeltas, 0x4D0190);
    RH_ScopedInstall(FindKeyFrame, 0x4D0240);
    RH_ScopedInstall(CalcDeltasCompressed, 0x4D0350);
    RH_ScopedInstall(NextKeyFrame, 0x4D04A0);
    RH_ScopedInstall(NextKeyFrameCompressed, 0x4D0570);
    RH_ScopedInstall(SetupKeyFrameCompressed, 0x4D0650);
    RH_ScopedInstall(Update, 0x4D06C0);
    RH_ScopedInstall(UpdateCompressed, 0x4D08D0);
}

// 0x4CFB70
void CAnimBlendNode::Init() {
    m_BlendAssoc = nullptr;
    m_BlendSeq = nullptr;
    m_RemainingTime = 0.0f;
    m_KeyFrameB = -1;
    m_KeyFrameA = -1;
}

// 0x4D0240
bool CAnimBlendNode::FindKeyFrame(float time) {
    if (m_BlendSeq->m_FramesNum < 1) {
        return false;
    }

    m_KeyFrameA = 0;
    m_KeyFrameB = m_KeyFrameA;

    if (m_BlendSeq->m_FramesNum == 1) {
        m_RemainingTime = 0.0f;
        CalcDeltas();
        return true;
    }

    // Rewind anim until `t` is between `m_KeyFrameA` and `m_KeyFrameB`
    // Maybe check if GetUncompressedFrame is < numFrames?
    for (; time > m_BlendSeq->GetUKeyFrame(++m_KeyFrameA)->DeltaTime; m_KeyFrameB = m_KeyFrameA) {
        time -= m_BlendSeq->GetUKeyFrame(m_KeyFrameA)->DeltaTime;

        if (m_KeyFrameA + 1 >= m_BlendSeq->m_FramesNum) {
            // reached end of animation
            if (!m_BlendAssoc->IsRepeating()) {
                CalcDeltas();
                m_RemainingTime = 0.0f;
                return false;
            }
            m_KeyFrameA = 0;
        }
    }

    m_RemainingTime = m_BlendSeq->GetUKeyFrame(m_KeyFrameA)->DeltaTime - time;

    CalcDeltas();

    return true;
}

// 0x4D00E0
void CAnimBlendNode::CalcTheta(float angleCos) {
    m_Theta       = std::acos(std::min(angleCos, 1.0f));
    m_InvSinTheta = m_Theta == 0.0f
        ? 0.0f
        : 1.0f / std::sin(m_Theta);
}

// 0x4D0190
void CAnimBlendNode::CalcDeltas() {
    if (!m_BlendSeq->m_bHasRotation) {
        return;
    }

    KeyFrame* kfA = m_BlendSeq->GetUncompressedFrame(m_KeyFrameA);
    KeyFrame* kfB = m_BlendSeq->GetUncompressedFrame(m_KeyFrameB);

    CalcTheta(DotProduct(kfA->Rot, kfB->Rot));
}

// 0x4D0350
void CAnimBlendNode::CalcDeltasCompressed() {
    if (!m_BlendSeq->m_bHasRotation) {
        return;
    }

    KeyFrameCompressed* kfA = m_BlendSeq->GetCompressedFrame(m_KeyFrameA);
    KeyFrameCompressed* kfB = m_BlendSeq->GetCompressedFrame(m_KeyFrameB);

    CQuaternion rotA = kfA->Rot, rotB = kfB->Rot;
    const auto angleCos = DotProduct(rotA, rotB);
    if (angleCos < 0.0f) {
        rotB     = -rotB;
        kfB->Rot = rotB;
    }
    CalcTheta(angleCos);
}

// 0x4CFB90 - Unused
bool CAnimBlendNode::NextKeyFrameNoCalc() {
    NOTSA_UNREACHABLE("Unused Function");
}

// 0x4D0650
bool CAnimBlendNode::SetupKeyFrameCompressed() {
    if (m_BlendSeq->m_FramesNum < 1) {
        return false;
    }

    m_KeyFrameA = 1;
    m_KeyFrameB = 0;

    if (m_BlendSeq->m_FramesNum == 1) { // Only 1 frame
        m_KeyFrameA     = 0;
        m_RemainingTime = 0.0f;
    } else { // More than a frame
        m_RemainingTime = m_BlendSeq->GetCompressedFrame(m_KeyFrameA)->DeltaTime;
    }

    CalcDeltasCompressed();
    return true;
}

// 0x4D0160 - Unused
bool CAnimBlendNode::UpdateTime() {
    if (m_BlendAssoc->IsRunning()) {
        m_RemainingTime -= m_BlendAssoc->m_TimeStep;
        if (m_RemainingTime <= 0.0f) {
            return NextKeyFrameNoCalc();
        }
    }
    return false;
}
