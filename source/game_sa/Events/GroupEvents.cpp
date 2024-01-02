#include "StdInc.h"

#include "GroupEvents.h"

void CEventPlayerCommandToGroup::InjectHooks()
{
    RH_ScopedClass(CEventPlayerCommandToGroup);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B23D0);
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4B24D0);
}

void CEventPlayerCommandToGroupAttack::InjectHooks()
{
    RH_ScopedClass(CEventPlayerCommandToGroupAttack);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5F6340);
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4B2530);
}

void CEventPlayerCommandToGroupGather::InjectHooks()
{
    RH_ScopedClass(CEventPlayerCommandToGroupGather);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x609250);
}

void CEventDontJoinPlayerGroup::InjectHooks()
{
    RH_ScopedClass(CEventDontJoinPlayerGroup);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x6090E0);
}

void CEventNewGangMember::InjectHooks()
{
    RH_ScopedClass(CEventNewGangMember);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x608F70);
}

CEventPlayerCommandToGroup::CEventPlayerCommandToGroup(ePlayerGroupCommand command, CPed* target)
{
    m_command = command;
    m_target = target;
    CEntity::SafeRegisterRef(m_target);
}

CEventPlayerCommandToGroup::~CEventPlayerCommandToGroup()
{
    CEntity::SafeCleanUpRef(m_target);
}

CEventPlayerCommandToGroup* CEventPlayerCommandToGroup::Constructor(ePlayerGroupCommand command, CPed* target)
{
    this->CEventPlayerCommandToGroup::CEventPlayerCommandToGroup(command, target);
    return this;
}

// 0x4B24D0
bool CEventPlayerCommandToGroup::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventPlayerCommandToGroup::AffectsPedGroup_Reversed(pedGroup);
}

bool CEventPlayerCommandToGroup::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    CPed* leader = pedGroup->GetMembership().GetLeader();
    if (leader && leader->IsPlayer()) {
        for (int32 i = 0; i < TOTAL_PED_GROUP_FOLLOWERS; i++) {
            CPed* member = pedGroup->GetMembership().GetMember(i);
            if (member && member->m_nAreaCode != leader->m_nAreaCode) 
                return false;
        }
    }
    return true;
}

CEventPlayerCommandToGroupAttack* CEventPlayerCommandToGroupAttack::Constructor(CPed* target)
{
    this->CEventPlayerCommandToGroupAttack::CEventPlayerCommandToGroupAttack(target);
    return this;
}

// 0x4B2530
bool CEventPlayerCommandToGroupAttack::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventPlayerCommandToGroupAttack::AffectsPedGroup_Reversed(pedGroup);
}

bool CEventPlayerCommandToGroupAttack::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    bool affectsPedGroup = CEventPlayerCommandToGroup::AffectsPedGroup(pedGroup);
    if (affectsPedGroup) {
        for (int32 i = 0; i < TOTAL_PED_GROUP_FOLLOWERS; i++) {
            CPed* member = pedGroup->GetMembership().GetMember(i);
            if (member && !member->bDoesntListenToPlayerGroupCommands)
                return true;
        }
        return false;
    }
    return affectsPedGroup;
}

CEventPlayerCommandToGroupGather* CEventPlayerCommandToGroupGather::Constructor(CPed* target)
{
    this->CEventPlayerCommandToGroupGather::CEventPlayerCommandToGroupGather(target);
    return this;
}

CEventDontJoinPlayerGroup::CEventDontJoinPlayerGroup(CPed* player)
{
    m_player = player;
    CEntity::SafeRegisterRef(m_player);
}

CEventDontJoinPlayerGroup::~CEventDontJoinPlayerGroup()
{
    CEntity::SafeCleanUpRef(m_player);
}

CEventDontJoinPlayerGroup* CEventDontJoinPlayerGroup::Constructor(CPed* player)
{
    this->CEventDontJoinPlayerGroup::CEventDontJoinPlayerGroup(player);
    return this;
}

CEventNewGangMember::CEventNewGangMember(CPed* member)
{
    m_member = member;
    CEntity::SafeRegisterRef(m_member);
}

CEventNewGangMember::~CEventNewGangMember()
{
    CEntity::SafeCleanUpRef(m_member);
}

CEventNewGangMember* CEventNewGangMember::Constructor(CPed* member)
{
    this->CEventNewGangMember::CEventNewGangMember(member);
    return this;
}
