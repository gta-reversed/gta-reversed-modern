#include "StdInc.h"

#include "AnimBlendStaticAssociation.h"

void CAnimBlendStaticAssociation::InjectHooks() {
    RH_ScopedClass(CAnimBlendStaticAssociation);
    RH_ScopedCategory("Animation");

    //RH_ScopedInstall(Constructor0, 0x4CE940, { .reversed = false });
    //RH_ScopedInstall(Constructor1, 0x4CEF60, { .reversed = false });
    //RH_ScopedInstall(Destructor, 0x4CDF50, { .reversed = false });
    RH_ScopedInstall(Init, 0x4CEC20, { .reversed = false });
    RH_ScopedInstall(AllocateSequenceArray, 0x4CE960);
    RH_ScopedInstall(FreeSequenceArray, 0x4CE9A0);
}

// 0x4CE940
CAnimBlendStaticAssociation::CAnimBlendStaticAssociation() {
    m_nAnimId = -1;
    m_nAnimGroup = -1;
    m_nFlags = 0;
    m_pSequenceArray = 0;
    m_pHierarchy = 0;
}

// 0x4CEF60
CAnimBlendStaticAssociation::CAnimBlendStaticAssociation(RpClump* clump, CAnimBlendHierarchy* hier) {
    plugin::CallMethod<0x4CEF60, CAnimBlendStaticAssociation*, RpClump*, CAnimBlendHierarchy*>(this, clump, hier);
}

// 0x4CDF50 virtual
CAnimBlendStaticAssociation::~CAnimBlendStaticAssociation() {
    assert(0);
}

// 0x4CEC20
void CAnimBlendStaticAssociation::Init(RpClump* clump, CAnimBlendHierarchy* hier) {
    plugin::CallMethod<0x4CEC20, CAnimBlendStaticAssociation*, RpClump*, CAnimBlendHierarchy*>(this, clump, hier);
}

// 0x4CE960
void CAnimBlendStaticAssociation::AllocateSequenceArray(int32 count) {
    m_pSequenceArray = (CAnimBlendSequence**)CMemoryMgr::Malloc(sizeof(CAnimBlendSequence*) * count);
    for (auto& array : std::span{ m_pSequenceArray, (size_t)count }) {
        array = nullptr;
    }
}

// 0x4CE9A0
void CAnimBlendStaticAssociation::FreeSequenceArray() {
    if (m_pSequenceArray) {
        CMemoryMgr::Free(m_pSequenceArray);
    }
}
