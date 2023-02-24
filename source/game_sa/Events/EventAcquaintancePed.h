#pragma once

#include "EventEditableResponse.h"
#include "Vector.h"

class NOTSA_EXPORT_VTABLE CEventAcquaintancePed : public CEventEditableResponse {
public:
    CPed* m_ped;

public:
    explicit CEventAcquaintancePed(CPed* ped, eTaskType taskType = TASK_NONE/*notsa arg*/);
    ~CEventAcquaintancePed() override;

    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override { return reinterpret_cast<CEntity*>(m_ped); }
    bool TakesPriorityOver(const CEvent& refEvent) override;
    bool CanBeInterruptedBySameEvent() override { return true; }

public:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventAcquaintancePed* Constructor(CPed* ped);

    bool AffectsPed_Reversed(CPed* ped);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedHate : public CEventAcquaintancePed {
public:
    using CEventAcquaintancePed::CEventAcquaintancePed;

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_HATE; }
    int32 GetEventPriority() const override { return 26; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedHate(m_ped); }

public:
    friend class CEventAcquaintancePed;
    static void InjectHooks();

    CEventAcquaintancePedHate* Constructor2(CPed* ped);
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedRespect : public CEventAcquaintancePed {
public:
    using CEventAcquaintancePed::CEventAcquaintancePed;

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_RESPECT; }
    int32 GetEventPriority() const override { return 23; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedRespect(m_ped); }
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedLike : public CEventAcquaintancePed {
public:
    using CEventAcquaintancePed::CEventAcquaintancePed;

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_LIKE; }
    int32 GetEventPriority() const override { return 22; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedLike(m_ped); }
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedDislike : public CEventAcquaintancePed {
public:
    using CEventAcquaintancePed::CEventAcquaintancePed;

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_DISLIKE; }
    int32 GetEventPriority() const override { return 24; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedDislike(m_ped); }
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedHateBadlyLit : public CEventAcquaintancePed {
public:
    uint32 m_startTimeInMs;
    CVector m_point;

public:
    CEventAcquaintancePedHateBadlyLit(CPed* ped, int32 startTimeInMs, const CVector& point);
    ~CEventAcquaintancePedHateBadlyLit() override = default;

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_HATE_BADLY_LIT; }
    int32 GetEventPriority() const override { return 25; }
    bool AffectsPed(CPed* ped) override;
    bool CanBeInterruptedBySameEvent() override { return true; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedHateBadlyLit(m_ped, m_startTimeInMs, m_point); }

public:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventAcquaintancePedHateBadlyLit* Constructor(CPed* ped, int32 startTimeInMs, const CVector& point);
    bool AffectsPed_Reversed1(CPed* ped);
};

class NOTSA_EXPORT_VTABLE CEventSeenCop : public CEventAcquaintancePed {
public:
    using CEventAcquaintancePed::CEventAcquaintancePed;

    eEventType GetEventType() const override { return EVENT_SEEN_COP; }
    int32 GetEventPriority() const override { return 21; }
    bool AffectsPed(CPed* ped) override { return CEventAcquaintancePed::AffectsPed(ped); }
    CEventSeenCop* CloneEditable() override { return new CEventSeenCop(m_ped); }

public:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventSeenCop* Constructor1(CPed* cop);
};

VALIDATE_SIZE(CEventSeenCop, 0x18);
