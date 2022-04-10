#pragma once

#include "EventEditableResponse.h"
#include "Vector.h"

class NOTSA_EXPORT_VTABLE CEventAcquaintancePed : public CEventEditableResponse {
public:
    CPed* m_ped;

public:
    CEventAcquaintancePed(CPed* ped);
    ~CEventAcquaintancePed();

    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override { return reinterpret_cast<CEntity*>(m_ped); }
    bool TakesPriorityOver(const CEvent& refEvent) override;
    bool CanBeInterruptedBySameEvent() override { return true; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventAcquaintancePed* Constructor(CPed* ped);

    bool AffectsPed_Reversed(CPed* ped);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedHate : public CEventAcquaintancePed {
public:
    CEventAcquaintancePedHate(CPed* ped) : CEventAcquaintancePed (ped) {}
    ~CEventAcquaintancePedHate() {}

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_HATE; }
    int32 GetEventPriority() const override { return 26; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedHate(m_ped); }

private:
    friend class CEventAcquaintancePed;
    static void InjectHooks();

    CEventAcquaintancePedHate* Constructor(CPed* ped);
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedRespect : public CEventAcquaintancePed {
public:
    CEventAcquaintancePedRespect(CPed* ped) : CEventAcquaintancePed(ped) {}
    ~CEventAcquaintancePedRespect() {}

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_RESPECT; }
    int32 GetEventPriority() const override { return 23; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedRespect(m_ped); }
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedLike : public CEventAcquaintancePed {
public:
    CEventAcquaintancePedLike(CPed* ped) : CEventAcquaintancePed(ped) {}
    ~CEventAcquaintancePedLike() {}

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_LIKE; }
    int32 GetEventPriority() const override { return 22; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedLike(m_ped); }
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedDislike : public CEventAcquaintancePed {
public:
    CEventAcquaintancePedDislike(CPed* ped) : CEventAcquaintancePed(ped) {}
    ~CEventAcquaintancePedDislike() {}

    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_DISLIKE; }
    int32 GetEventPriority() const override { return 24; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedDislike(m_ped); }
};

class NOTSA_EXPORT_VTABLE CEventAcquaintancePedHateBadlyLit : public CEventAcquaintancePed {
public:
    uint32 m_startTimeInMs;
    CVector m_point;

    static void InjectHooks();

    CEventAcquaintancePedHateBadlyLit(CPed* ped, int32 startTimeInMs, const CVector& point);
    ~CEventAcquaintancePedHateBadlyLit() {}
private:
    CEventAcquaintancePedHateBadlyLit* Constructor(CPed* ped, int32 startTimeInMs, const CVector& point);
public:
    eEventType GetEventType() const override { return EVENT_ACQUAINTANCE_PED_HATE_BADLY_LIT; }
    int32 GetEventPriority() const override { return 25; }
    bool AffectsPed(CPed* ped) override;
    bool CanBeInterruptedBySameEvent() override { return true; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedHateBadlyLit(m_ped, m_startTimeInMs, m_point); }
private:
    bool AffectsPed_Reversed(CPed* ped);
};

class NOTSA_EXPORT_VTABLE CEventSeenCop : public CEventAcquaintancePed {
public:
    static void InjectHooks();

    CEventSeenCop(CPed* cop) : CEventAcquaintancePed(cop) {}
    ~CEventSeenCop() {}
private:
    CEventSeenCop* Constructor(CPed* cop);
public:
    eEventType GetEventType() const override { return EVENT_SEEN_COP; }
    int32 GetEventPriority() const override { return 21; }
    bool AffectsPed(CPed* ped) override { return CEventAcquaintancePed::AffectsPed(ped); }
    CEventSeenCop* CloneEditable() override { return new CEventSeenCop(m_ped); }
};

VALIDATE_SIZE(CEventSeenCop, 0x18);
