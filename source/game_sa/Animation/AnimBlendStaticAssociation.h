/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CAnimBlendSequence;
class CAnimBlendHierarchy;

class CAnimBlendStaticAssociation {
    PLUGIN_NO_DEFAULT_CONSTRUCTION_VIRTUALBASE(CAnimBlendStaticAssociation)

public:
    uint16               m_nNumBlendNodes;
    int16                m_nAnimId;
    uint16               m_nAnimGroup;
    uint16               m_nFlags;
    CAnimBlendSequence** m_pSequenceArray;
    CAnimBlendHierarchy* m_pHierarchy;

    // vtable function #0 (destructor)

    void AllocateSequenceArray(int32 count);
    void FreeSequenceArray();
    void Init(RpClump* clump, CAnimBlendHierarchy* hierarchy);

    auto GetHashKey() const noexcept { return m_pHierarchy->m_hashKey; }
};

VTABLE_DESC(CAnimBlendStaticAssociation, 0x85C6CC, 1);
VALIDATE_SIZE(CAnimBlendStaticAssociation, 0x14);
