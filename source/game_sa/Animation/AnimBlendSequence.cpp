#include "StdInc.h"

void CAnimBlendSequence::InjectHooks()
{
    RH_ScopedInstall(GetUncompressedFrame, 0x4CF1F0);
    RH_ScopedInstall(GetCompressedFrame, 0x4CF220);
}

CAnimSequenceRootFrameUncompressed* CAnimBlendSequence::GetUncompressedFrame(int32 iFrame)
{
    if (m_isRoot)
        return &static_cast<CAnimSequenceRootFrameUncompressed*>(m_pFrames)[iFrame];

    auto* pData = static_cast<CAnimSequenceChildFrameUncompressed*>(m_pFrames);
    return reinterpret_cast<CAnimSequenceRootFrameUncompressed*>(&pData[iFrame]);
}

CAnimSequenceRootFrameCompressed* CAnimBlendSequence::GetCompressedFrame(int32 iFrame)
{
    if (m_isRoot)
        return &static_cast<CAnimSequenceRootFrameCompressed*>(m_pFrames)[iFrame];

    auto* pData = static_cast<CAnimSequenceChildFrameCompressed*>(m_pFrames);
    return reinterpret_cast<CAnimSequenceRootFrameCompressed*>(&pData[iFrame]);
}
