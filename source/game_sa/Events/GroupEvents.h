#pragma once

#include "CEventEditableResponse.h"

enum ePlayerGroupCommand : int32
{
    PLAYER_GROUP_COMMAND_ATTACK = 0,
    PLAYER_GROUP_COMMAND_GATHER = 2,
};

class CEventPlayerCommandToGroup : public CEventEditableResponse {
public:
    ePlayerGroupCommand m_command;
    CPed*               m_target;

    static void InjectHooks();

    CEventPlayerCommandToGroup(ePlayerGroupCommand command, CPed* target);
    ~CEventPlayerCommandToGroup();
private:
    CEventPlayerCommandToGroup* Constructor(ePlayerGroupCommand command, CPed* target);
public:
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return false; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override { return reinterpret_cast<CEntity*>(m_target); }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
private:
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
};

VALIDATE_SIZE(CEventPlayerCommandToGroup, 0x1C);

class CEventPlayerCommandToGroupAttack : public CEventPlayerCommandToGroup {
public:
    static void InjectHooks();

    CEventPlayerCommandToGroupAttack(CPed* target) : CEventPlayerCommandToGroup(PLAYER_GROUP_COMMAND_ATTACK, target) {}
    ~CEventPlayerCommandToGroupAttack() {}
private:
    CEventPlayerCommandToGroupAttack* Constructor(CPed* target);
public:
    eEventType GetEventType() const override { return EVENT_PLAYER_COMMAND_TO_GROUP; }
    int32 GetEventPriority() const override { return 44; }
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEventPlayerCommandToGroupAttack* CloneEditable() override { return new CEventPlayerCommandToGroupAttack(m_target); }
private:
    bool AffectsPedGroup_Reversed(CPedGroup* pedGroup);
};

VALIDATE_SIZE(CEventPlayerCommandToGroupAttack, 0x1C);

class CEventPlayerCommandToGroupGather : public CEventPlayerCommandToGroup {
public:
    static void InjectHooks();

    CEventPlayerCommandToGroupGather(CPed* target) : CEventPlayerCommandToGroup(PLAYER_GROUP_COMMAND_GATHER, target) {}
    ~CEventPlayerCommandToGroupGather() {}
private:
    CEventPlayerCommandToGroupGather* Constructor(CPed* target);
public:
    eEventType GetEventType() const override { return EVENT_PLAYER_COMMAND_TO_GROUP_GATHER; }
    int32 GetEventPriority() const override { return 45; }
    CEventPlayerCommandToGroupGather* CloneEditable() override { return new CEventPlayerCommandToGroupGather(m_target); }
};

VALIDATE_SIZE(CEventPlayerCommandToGroupGather, 0x1C);

class CEventDontJoinPlayerGroup : public CEvent {
public:
    CPed* m_player;

    static void InjectHooks();

    CEventDontJoinPlayerGroup(CPed* player);
    ~CEventDontJoinPlayerGroup();
private:
    CEventDontJoinPlayerGroup* Constructor(CPed* player);
public:
    eEventType GetEventType() const override { return EVENT_DONT_JOIN_GROUP; }
    int32 GetEventPriority() const override { return 43; }
    int32 GetLifeTime() override { return 0; }
    CEventDontJoinPlayerGroup* Clone() override { return new CEventDontJoinPlayerGroup(m_player); }
    bool AffectsPed(CPed* ped) override { return true; }
};

VALIDATE_SIZE(CEventDontJoinPlayerGroup, 0x10);

class CEventNewGangMember : public CEvent {
public:
    CPed* m_member;

    static void InjectHooks();

    CEventNewGangMember(CPed* member);
    ~CEventNewGangMember();
private:
    CEventNewGangMember* Constructor(CPed* member);
public:
    eEventType GetEventType() const override { return EVENT_NEW_GANG_MEMBER; }
    int32 GetEventPriority() const override { return 42; }
    int32 GetLifeTime() override { return 0; }
    CEventNewGangMember* Clone() override { return new CEventNewGangMember(m_member); }
    bool AffectsPed(CPed* ped) override { return true; }
};

VALIDATE_SIZE(CEventNewGangMember, 0x10);
