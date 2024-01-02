#pragma once

#include "EventEditableResponse.h"

enum ePlayerGroupCommand : int32
{
    PLAYER_GROUP_COMMAND_ATTACK = 0,
    PLAYER_GROUP_COMMAND_GATHER = 2,
};

class CEventPlayerCommandToGroup : public CEventEditableResponse {
public:
    ePlayerGroupCommand m_command;
    CPed*               m_target;

public:
    static void InjectHooks();

    explicit CEventPlayerCommandToGroup(ePlayerGroupCommand command = ePlayerGroupCommand::PLAYER_GROUP_COMMAND_ATTACK, CPed* target = nullptr);
    ~CEventPlayerCommandToGroup() override;

    eEventType GetEventType() const override { return EVENT_PLAYER_COMMAND_TO_GROUP; }
    int32_t GetEventPriority() const override { return 44; }
    CEventPlayerCommandToGroup* CloneEditable() override { return new CEventPlayerCommandToGroup(ePlayerGroupCommand::PLAYER_GROUP_COMMAND_ATTACK, m_target); }
    int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override { return reinterpret_cast<CEntity*>(m_target); }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }

private:
    CEventPlayerCommandToGroup* Constructor(ePlayerGroupCommand command, CPed* target);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
};

VALIDATE_SIZE(CEventPlayerCommandToGroup, 0x1C);

class CEventPlayerCommandToGroupAttack : public CEventPlayerCommandToGroup {
public:
    static void InjectHooks();

    CEventPlayerCommandToGroupAttack(CPed* target) : CEventPlayerCommandToGroup(PLAYER_GROUP_COMMAND_ATTACK, target) {}
    ~CEventPlayerCommandToGroupAttack() override = default;

    eEventType GetEventType() const override { return EVENT_PLAYER_COMMAND_TO_GROUP; }
    int32 GetEventPriority() const override { return 44; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEventPlayerCommandToGroupAttack* CloneEditable() override { return new CEventPlayerCommandToGroupAttack(m_target); }

private:
    CEventPlayerCommandToGroupAttack* Constructor(CPed* target);
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
};

VALIDATE_SIZE(CEventPlayerCommandToGroupAttack, 0x1C);

class CEventPlayerCommandToGroupGather : public CEventPlayerCommandToGroup {
public:
    static void InjectHooks();

    CEventPlayerCommandToGroupGather(CPed* target) : CEventPlayerCommandToGroup(PLAYER_GROUP_COMMAND_GATHER, target) {}
    ~CEventPlayerCommandToGroupGather() override = default;

    eEventType GetEventType() const override { return EVENT_PLAYER_COMMAND_TO_GROUP_GATHER; }
    int32 GetEventPriority() const override { return 45; }
    CEventPlayerCommandToGroupGather* CloneEditable() override { return new CEventPlayerCommandToGroupGather(m_target); }

    CEventPlayerCommandToGroupGather* Constructor(CPed* target);
};

VALIDATE_SIZE(CEventPlayerCommandToGroupGather, 0x1C);

class CEventDontJoinPlayerGroup : public CEvent {
public:
    CPed* m_player;

public:
    static void InjectHooks();

    CEventDontJoinPlayerGroup(CPed* player);
    ~CEventDontJoinPlayerGroup() override;

    eEventType GetEventType() const override { return EVENT_DONT_JOIN_GROUP; }
    int32 GetEventPriority() const override { return 43; }
    int32 GetLifeTime() override { return 0; }
    CEventDontJoinPlayerGroup* Clone() override { return new CEventDontJoinPlayerGroup(m_player); }
    bool AffectsPed(CPed* ped) override { return true; }

    CEventDontJoinPlayerGroup* Constructor(CPed* player);
};

VALIDATE_SIZE(CEventDontJoinPlayerGroup, 0x10);

class CEventNewGangMember : public CEvent {
public:
    CPed* m_member;

public:
    static void InjectHooks();

    CEventNewGangMember(CPed* member);
    ~CEventNewGangMember() override;

    eEventType GetEventType() const override { return EVENT_NEW_GANG_MEMBER; }
    int32 GetEventPriority() const override { return 42; }
    int32 GetLifeTime() override { return 0; }
    CEventNewGangMember* Clone() override { return new CEventNewGangMember(m_member); }
    bool AffectsPed(CPed* ped) override { return true; }

    CEventNewGangMember* Constructor(CPed* member);
};

VALIDATE_SIZE(CEventNewGangMember, 0x10);
