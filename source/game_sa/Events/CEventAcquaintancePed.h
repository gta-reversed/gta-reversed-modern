#pragma once
#include "CEventEditableResponse.h"
#include "CVector.h"

class CEventAcquaintancePed : public CEventEditableResponse
{
public:
    CPed* m_ped;

    static void InjectHooks();

    CEventAcquaintancePed(CPed* ped);
    ~CEventAcquaintancePed();
private:
    CEventAcquaintancePed* Constructor(CPed* ped);
public:
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() override { return reinterpret_cast<CEntity*>(m_ped); }
    bool TakesPriorityOver(CEvent* refEvent) override;
    bool CanBeInterruptedBySameEvent() override { return true; }
private:
    bool AffectsPed_Reversed(CPed* ped);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
    bool TakesPriorityOver_Reversed(CEvent* refEvent);
};

class CEventAcquaintancePedHate : public CEventAcquaintancePed
{
public:
    static void InjectHooks();

    CEventAcquaintancePedHate(CPed* ped) : CEventAcquaintancePed (ped) {}
    ~CEventAcquaintancePedHate() {}
private:
    CEventAcquaintancePedHate* Constructor(CPed* ped);
public:
    eEventType GetEventType() override { return EVENT_ACQUAINTANCE_PED_HATE; }
    int GetEventPriority() override { return 26; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedHate(m_ped); }
};

class CEventAcquaintancePedRespect : public CEventAcquaintancePed
{
public:
    CEventAcquaintancePedRespect(CPed* ped) : CEventAcquaintancePed(ped) {}
    ~CEventAcquaintancePedRespect() {}

    eEventType GetEventType() override { return EVENT_ACQUAINTANCE_PED_RESPECT; }
    int GetEventPriority() override { return 23; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedRespect(m_ped); }
};

class CEventAcquaintancePedLike : public CEventAcquaintancePed
{
public:
    CEventAcquaintancePedLike(CPed* ped) : CEventAcquaintancePed(ped) {}
    ~CEventAcquaintancePedLike() {}

    eEventType GetEventType() override { return EVENT_ACQUAINTANCE_PED_LIKE; }
    int GetEventPriority() override { return 22; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedLike(m_ped); }
};

class CEventAcquaintancePedDislike : public CEventAcquaintancePed
{
public:
    CEventAcquaintancePedDislike(CPed* ped) : CEventAcquaintancePed(ped) {}
    ~CEventAcquaintancePedDislike() {}

    eEventType GetEventType() override { return EVENT_ACQUAINTANCE_PED_DISLIKE; }
    int GetEventPriority() override { return 24; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedDislike(m_ped); }
};

class CEventAcquaintancePedHateBadlyLit : public CEventAcquaintancePed
{
public:
    std::uint32_t m_startTimeInMs;
    CVector m_point;

    static void InjectHooks();

    CEventAcquaintancePedHateBadlyLit(CPed* ped, std::int32_t startTimeInMs, const CVector& point);
    ~CEventAcquaintancePedHateBadlyLit() {}
private:
    CEventAcquaintancePedHateBadlyLit* Constructor(CPed* ped, std::int32_t startTimeInMs, const CVector& point);
public:
    eEventType GetEventType() override { return EVENT_ACQUAINTANCE_PED_HATE_BADLY_LIT; }
    int GetEventPriority() override { return 25; }
    bool AffectsPed(CPed* ped) override;
    bool CanBeInterruptedBySameEvent() override { return true; }
    CEventEditableResponse* CloneEditable() override { return new CEventAcquaintancePedHateBadlyLit(m_ped, m_startTimeInMs, m_point); }
private:
    bool AffectsPed_Reversed(CPed* ped);
};

class CEventSeenCop : public CEventAcquaintancePed {
public:
    static void InjectHooks();

    CEventSeenCop(CPed* cop) : CEventAcquaintancePed(cop) {}
    ~CEventSeenCop() {}
private:
    CEventSeenCop* Constructor(CPed* cop);
public:
    eEventType GetEventType() override { return EVENT_SEEN_COP; }
    std::int32_t GetEventPriority() override { return 21; }
    bool AffectsPed(CPed* ped) override { return CEventAcquaintancePed::AffectsPed(ped); }
    CEventSeenCop* CloneEditable() override { return new CEventSeenCop(m_ped); }
};

VALIDATE_SIZE(CEventSeenCop, 0x18);
