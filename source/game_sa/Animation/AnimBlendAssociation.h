/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AnimAssociationData.h"
#include "eAnimBlendCallbackType.h"
#include "RenderWare.h"

class CAnimBlendNode;
class CAnimBlendHierarchy;
class CAnimBlendStaticAssociation;

enum eAnimationFlags {
    ANIMATION_DEFAULT            = 0x0,
    ANIMATION_STARTED            = 0x1,
    ANIMATION_LOOPED             = 0x2,
    ANIMATION_FREEZE_LAST_FRAME  = 0x4,
    ANIMATION_UNLOCK_LAST_FRAME  = 0x8,  // Animation will be stuck on last frame, if not set
    ANIMATION_PARTIAL            = 0x10, // TODO: Flag name is possibly incorrect? Following the usual logic (like `ANIMATION_MOVEMENT`), it should be `ANIMATION_GET_IN_CAR` (See  `RemoveGetInAnims`)
    ANIMATION_MOVEMENT           = 0x20,
    ANIMATION_TRANSLATE_Y        = 0x40,
    ANIMATION_TRANSLATE_X        = 0x80,
    ANIMATION_WALK               = 0x100,
    ANIMATION_200                = 0x200,
    ANIMATION_ADD_TO_BLEND       = 0x400, // Possibly should be renamed to ANIMATION_IDLE, see `CPed::PlayFootSteps()`
    ANIMATION_800                = 0x800,
    ANIMATION_SECONDARY_TASK_ANIM= 0x1000,
    ANIMATION_FREEZE_TRANSLATION = 0x2000,
    ANIMATION_BLOCK_REFERENCED   = 0x4000,
    ANIMATION_INDESTRUCTIBLE     = 0x8000 // The animation is never destroyed if this flag is set, NO MATTER WHAT
};

class CDefaultAnimCallback {
public:
    static void DefaultAnimCB(class CAnimBlendAssociation* animAssoc, void* something) {
        // nothing here
    }
};

class CAnimBlendLink {
public:
    CAnimBlendLink* next{};
    CAnimBlendLink* prev{};

    CAnimBlendLink() = default;

    void Init() {
        next = nullptr;
        prev = nullptr;
    }

    void Prepend(CAnimBlendLink* link) {
        if (next) {
            next->prev = link;
        }
        link->next = next;
        link->prev = this;
        next = link;
    }

    void Remove() {
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }
        Init();
    }
};

struct SClumpAnimAssoc {
    CAnimBlendLink       m_Link;
    uint16               m_nNumBlendNodes;
    int16                m_nAnimGroup;
    CAnimBlendNode*      m_pNodeArray;
    CAnimBlendHierarchy* m_pHierarchy;
    float                m_fBlendAmount;
    float                m_fBlendDelta;
    float                m_fCurrentTime;
    float                m_fSpeed;
    float                m_fTimeStep;
    int16                m_nAnimId;
    uint16               m_nFlags; // TODO: use bitfield

    float GetTimeProgress()                  const;
    float GetBlendAmount(float weight = 1.f) const { return IsPartial() ? m_fBlendAmount : m_fBlendAmount * weight; }

    [[nodiscard]] bool IsRunning()        const { return (m_nFlags & ANIMATION_STARTED) != 0; }
    [[nodiscard]] bool IsRepeating()      const { return (m_nFlags & ANIMATION_LOOPED) != 0; }
    [[nodiscard]] bool IsPartial()        const { return (m_nFlags & ANIMATION_PARTIAL) != 0; }
    [[nodiscard]] bool IsMoving()         const { return (m_nFlags & ANIMATION_MOVEMENT) != 0; }
    [[nodiscard]] bool HasYTranslation()  const { return (m_nFlags & ANIMATION_TRANSLATE_X) != 0; }
    [[nodiscard]] bool HasXTranslation()  const { return (m_nFlags & ANIMATION_TRANSLATE_Y) != 0; }
    [[nodiscard]] bool IsIndestructible() const { return (m_nFlags & ANIMATION_INDESTRUCTIBLE) != 0; }
};

class NOTSA_EXPORT_VTABLE CAnimBlendAssociation : public SClumpAnimAssoc {
public:
    eAnimBlendCallbackType m_nCallbackType;
    void (*m_pCallbackFunc)(CAnimBlendAssociation*, void*);
    void* m_pCallbackData;

public:
    CAnimBlendAssociation();
    CAnimBlendAssociation(RpClump* clump, CAnimBlendHierarchy* animHierarchy);
    CAnimBlendAssociation(CAnimBlendAssociation& assoc);
    explicit CAnimBlendAssociation(CAnimBlendStaticAssociation& assoc);
    virtual ~CAnimBlendAssociation();

    void AllocateAnimBlendNodeArray(int32 count);
    void FreeAnimBlendNodeArray();
    CAnimBlendNode* GetNode(int32 nodeIndex);

    void Init(RpClump* clump, CAnimBlendHierarchy* hierarchy);
    void Init(CAnimBlendAssociation& source);
    void Init(CAnimBlendStaticAssociation& source);

    void ReferenceAnimBlock();
    void SetBlendDelta(float value) { m_fBlendDelta = value; }
    void SetBlend(float blendAmount, float blendDelta);
    void SetBlendTo(float blendAmount, float blendDelta);
    void SetCurrentTime(float currentTime);
    void SetDeleteCallback(void(*callback)(CAnimBlendAssociation*, void*), void* data = nullptr);
    void SetFinishCallback(void(*callback)(CAnimBlendAssociation*, void*), void* data = nullptr);
    void Start(float currentTime = 0.f);
    void SyncAnimation(CAnimBlendAssociation* syncWith);
    bool UpdateBlend(float mult);
    bool UpdateTime(float a1, float a2);
    void UpdateTimeStep(float speedMult, float timeMult);
    [[nodiscard]] uint32 GetHashKey() const noexcept;

    // NOTSA
    void SetFlag(eAnimationFlags flag, bool value = true) {
        if (value)
            m_nFlags |= (int)flag;
        else
            m_nFlags &= ~(int)flag;
    }

    static CAnimBlendAssociation* FromLink(CAnimBlendLink* link) {
        return (CAnimBlendAssociation*)((byte*)link - offsetof(CAnimBlendAssociation, m_Link));
    }

    void SetSpeed(float speed) {
        m_fSpeed = speed;
    }

    auto GetNodes() { return std::span{ &m_pNodeArray, m_nNumBlendNodes }; }
    void SetDefaultFinishCallback() { SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr); }
private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAnimBlendAssociation* Constructor0()  { this->CAnimBlendAssociation::CAnimBlendAssociation(); return this; }
    CAnimBlendAssociation* Constructor1(RpClump* clump, CAnimBlendHierarchy* animHierarchy) { this->CAnimBlendAssociation::CAnimBlendAssociation(clump, animHierarchy); return this; }
    CAnimBlendAssociation* Constructor2(CAnimBlendAssociation& assoc) { this->CAnimBlendAssociation::CAnimBlendAssociation(assoc); return this; }
    CAnimBlendAssociation* Constructor3(CAnimBlendStaticAssociation& assoc) { this->CAnimBlendAssociation::CAnimBlendAssociation(assoc); return this; }
};
VALIDATE_SIZE(CAnimBlendAssociation, 0x3C);
