/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include <extensions/WEnum.hpp>

class CAnimBlendSequence;
class CAnimBlendHierarchy;

//! Stores static animation data loaded from an animation clump.
class CAnimBlendStaticAssociation {
public:
    static void InjectHooks();

    CAnimBlendStaticAssociation() = default;
    CAnimBlendStaticAssociation(RpClump* clump, CAnimBlendHierarchy* hier);
    virtual ~CAnimBlendStaticAssociation();

    void Init(RpClump* clump, CAnimBlendHierarchy* hier);
    void AllocateSequenceArray(int32 count);
    void FreeSequenceArray();

    auto GetHashKey() const noexcept { return m_BlendHier->m_hashKey; }

    // 0x4CDF50 - Virtual deleting destructor wrapper
    auto Destructor(uint32 flags) {
        if (flags & 2) { // Vector (array)
            std::destroy_n(this, *(size_t*)((char*)this - sizeof(size_t))); // Number of objects is stored at the beginning of the array by the compiler ;)
            if (flags & 1) {
                delete ((char*)this - sizeof(size_t));
            }
        } else { // Scalar (single object)
            std::destroy_at(this);
            if (flags & 1) {
                delete this;
            }
        }
        return this;
    }

    bool IsValid() const { return m_BlendSeqs; } // vanilla sa, inlined function
    auto GetAnimHierarchy() const { return m_BlendHier; }
public:
    uint16                        m_NumBlendNodes{};
    notsa::WEnumS16<AnimationId>  m_AnimId{ANIM_ID_UNDEFINED};
    notsa::WEnumS16<AssocGroupId> m_AnimGroupId{ANIM_GROUP_NONE};
    uint16                        m_Flags{};
    CAnimBlendSequence**          m_BlendSeqs{};
    CAnimBlendHierarchy*          m_BlendHier{};
};
VALIDATE_SIZE(CAnimBlendStaticAssociation, 0x14);
