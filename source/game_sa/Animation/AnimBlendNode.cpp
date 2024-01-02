#include "StdInc.h"

#include "AnimBlendNode.h"

void CAnimBlendNode::InjectHooks() {
    RH_ScopedClass(CAnimBlendNode);
    RH_ScopedCategory("Animation");

    RH_ScopedInstall(Init, 0x4CFB70);
    RH_ScopedInstall(NextKeyFrameNoCalc, 0x4CFB90);
    RH_ScopedInstall(GetCurrentTranslation, 0x4CFC50, { .reversed = false });
    RH_ScopedInstall(GetCurrentTranslationCompressed, 0x4CFE60, { .reversed = false });
    RH_ScopedInstall(GetEndTranslation, 0x4CFD90, { .reversed = false });
    RH_ScopedInstall(GetEndTranslationCompressed, 0x4D0000, { .reversed = false });
    RH_ScopedInstall(CalcTheta, 0x4D00E0);
    RH_ScopedInstall(UpdateTime, 0x4D0160);
    RH_ScopedInstall(CalcDeltas, 0x4D0190);
    RH_ScopedInstall(FindKeyFrame, 0x4D0240);
    RH_ScopedInstall(CalcDeltasCompressed, 0x4D0350);
    RH_ScopedInstall(NextKeyFrame, 0x4D04A0, { .reversed = false });
    RH_ScopedInstall(NextKeyFrameCompressed, 0x4D0570, { .reversed = false });
    RH_ScopedInstall(SetupKeyFrameCompressed, 0x4D0650);
    RH_ScopedInstall(Update, 0x4D06C0, { .reversed = false });
    RH_ScopedInstall(UpdateCompressed, 0x4D08D0, { .reversed = false });
}

// 0x4CFB70
void CAnimBlendNode::Init() {
    m_pAnimBlendAssociation = nullptr;
    m_pAnimSequence = nullptr;
    m_fRemainingTime = 0.0f;
    m_PreviousKeyFrameId = -1;
    m_nNextKeyFrameId = -1;
}

// 0x4D0240
bool CAnimBlendNode::FindKeyFrame(float time) {
    if (m_pAnimSequence->m_nFrameCount < 1) {
        return false;
    }

    m_nNextKeyFrameId = 0;
    m_PreviousKeyFrameId = m_nNextKeyFrameId;

    if (m_pAnimSequence->m_nFrameCount == 1) {
        m_fRemainingTime = 0.0f;
        CalcDeltas();
        return true;
    }

    // advance until t is between m_PreviousKeyFrameId and m_nNextKeyFrameId
    // maybe check if GetUncompressedFrame is < numFrames?
    while (time > m_pAnimSequence->GetUncompressedFrame(++m_nNextKeyFrameId)->deltaTime) {
        time -= m_pAnimSequence->GetUncompressedFrame(m_nNextKeyFrameId)->deltaTime;
        if (m_nNextKeyFrameId + 1 >= m_pAnimSequence->m_nFrameCount) {
            // reached end of animation
            if (!m_pAnimBlendAssociation->IsRepeating()) {
                CalcDeltas();
                m_fRemainingTime = 0.0f;
                return false;
            }
            m_nNextKeyFrameId = 0;
        }
        m_PreviousKeyFrameId = m_nNextKeyFrameId;
    }

    m_fRemainingTime = m_pAnimSequence->GetUncompressedFrame(m_nNextKeyFrameId)->deltaTime - time;

    CalcDeltas();
    return true;
}

// 0x4D00E0
void CAnimBlendNode::CalcTheta(float angle) {
    m_fTheta0 = std::acos(std::min(angle, 1.0f));
    m_fTheta1 = m_fTheta0 == 0.0f ? 0.0f : 1.0f / std::sin(m_fTheta0);
}

// 0x4D0190
void CAnimBlendNode::CalcDeltas() {
    if (!m_pAnimSequence->m_numFramesSet) {
        return;
    }

    KeyFrame* kfA = m_pAnimSequence->GetUncompressedFrame(m_nNextKeyFrameId);
    KeyFrame* kfB = m_pAnimSequence->GetUncompressedFrame(m_PreviousKeyFrameId);

    CalcTheta(DotProduct(kfA->rotation, kfB->rotation));
}

// 0x4D0350
void CAnimBlendNode::CalcDeltasCompressed() {
    if (!m_pAnimSequence->m_numFramesSet) {
        return;
    }

    KeyFrameCompressed* kfA = m_pAnimSequence->GetCompressedFrame(m_nNextKeyFrameId);
    KeyFrameCompressed* kfB = m_pAnimSequence->GetCompressedFrame(m_PreviousKeyFrameId);
    CQuaternion rotA, rotB;
    kfA->GetRotation(&rotA);
    kfB->GetRotation(&rotB);
    float cos = DotProduct(rotA, rotB);
    if (cos < 0.0f) {
        rotB = -rotB;
        kfB->SetRotation(rotB);
    }
    CalcTheta(DotProduct(rotA, rotB));
}

// 0x4CFC50
void CAnimBlendNode::GetCurrentTranslation(CVector& trans, float weight) {
    assert(0);
}

// 0x4CFE60
void CAnimBlendNode::GetCurrentTranslationCompressed(CVector& trans, float weight) {
    assert(0);
}

// 0x4CFD90
void CAnimBlendNode::GetEndTranslation(CVector& trans, float weight) {
    assert(0);
}

// 0x4D0000
void CAnimBlendNode::GetEndTranslationCompressed(CVector& trans, float weight) {
    assert(0);
}

// 0x4D04A0
bool CAnimBlendNode::NextKeyFrame() {
    return plugin::CallMethodAndReturn<bool, 0x4D04A0>(this);
}

// 0x4D0570
bool CAnimBlendNode::NextKeyFrameCompressed() {
    return plugin::CallMethodAndReturn<bool, 0x4D0570>(this);
}

// 0x4CFB90
bool CAnimBlendNode::NextKeyFrameNoCalc() {
    return plugin::CallMethodAndReturn<bool, 0x4CFB90>(this);
}

// 0x4D0650
bool CAnimBlendNode::SetupKeyFrameCompressed() {
    if (m_pAnimSequence->m_nFrameCount < 1) {
        return false;
    }

    m_nNextKeyFrameId = 1;
    m_PreviousKeyFrameId = 0;

    if (m_pAnimSequence->m_nFrameCount == 1) {
        m_nNextKeyFrameId = 0;
        m_fRemainingTime = 0.0f;
    } else
        m_fRemainingTime = m_pAnimSequence->GetCompressedFrame(m_nNextKeyFrameId)->GetDeltaTime();

    CalcDeltasCompressed();
    return true;
}

// 0x4D06C0
bool CAnimBlendNode::Update(CVector& trans, CQuaternion& rot, float weight) {
    return plugin::CallMethodAndReturn<bool, 0x4D06C0, CAnimBlendNode*, CVector&, CQuaternion&, float>(this, trans, rot, weight);
}

// 0x4D08D0
bool CAnimBlendNode::UpdateCompressed(CVector& trans, CQuaternion& rot, float weight) {
    return plugin::CallMethodAndReturn<bool, 0x4D08D0, CAnimBlendNode*, CVector&, CQuaternion&, float>(this, trans, rot, weight);
}

// 0x4D0160
bool CAnimBlendNode::UpdateTime() {
    if (m_pAnimBlendAssociation->IsRunning()) {
        m_fRemainingTime -= m_pAnimBlendAssociation->m_fTimeStep;
        if (m_fRemainingTime <= 0.0f) {
            return NextKeyFrameNoCalc();
        }
    }
    return false;
}
