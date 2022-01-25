#include "StdInc.h"

void CEventPlayerCommandToGroup::InjectHooks()
{
    Install("CEventPlayerCommandToGroup", "CEventPlayerCommandToGroup", 0x4B23D0, &CEventPlayerCommandToGroup::Constructor);
    Install("CEventPlayerCommandToGroup", "AffectsPedGroup_Reversed", 0x4B24D0, &CEventPlayerCommandToGroup::AffectsPedGroup_Reversed);
}

void CEventPlayerCommandToGroupAttack::InjectHooks()
{
    Install("CEventPlayerCommandToGroupAttack", "CEventPlayerCommandToGroupAttack", 0x5F6340, &CEventPlayerCommandToGroupAttack::Constructor);
    Install("CEventPlayerCommandToGroupAttack", "AffectsPedGroup_Reversed", 0x4B2530, &CEventPlayerCommandToGroupAttack::AffectsPedGroup_Reversed);
}

void CEventPlayerCommandToGroupGather::InjectHooks()
{
    Install("CEventPlayerCommandToGroupGather", "CEventPlayerCommandToGroupGather", 0x609250, &CEventPlayerCommandToGroupGather::Constructor);
}

void CEventDontJoinPlayerGroup::InjectHooks()
{
    Install("CEventDontJoinPlayerGroup", "CEventDontJoinPlayerGroup", 0x6090E0, &CEventDontJoinPlayerGroup::Constructor);
}

void CEventNewGangMember::InjectHooks()
{
    Install("CEventNewGangMember", "CEventNewGangMember", 0x608F70, &CEventNewGangMember::Constructor);
}

CEventPlayerCommandToGroup::CEventPlayerCommandToGroup(ePlayerGroupCommand command, CPed* target)
{
    m_command = command;
    m_target = target;
    if (target)
        target->RegisterReference(reinterpret_cast<CEntity**>(&m_target));
}

CEventPlayerCommandToGroup::~CEventPlayerCommandToGroup()
{
    if (m_target)
        m_target->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_target));
}

CEventPlayerCommandToGroup* CEventPlayerCommandToGroup::Constructor(ePlayerGroupCommand command, CPed* target)
{
    this->CEventPlayerCommandToGroup::CEventPlayerCommandToGroup(command, target);
    return this;
}

bool CEventPlayerCommandToGroup::AffectsPedGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B24D0, CEventPlayerCommandToGroup*, CPedGroup*>(this, pedGroup);
#else
    return CEventPlayerCommandToGroup::AffectsPedGroup_Reversed(pedGroup);
#endif
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

bool CEventPlayerCommandToGroupAttack::AffectsPedGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B2530, CEventPlayerCommandToGroupAttack*, CPedGroup*>(this, pedGroup);
#else
    return CEventPlayerCommandToGroupAttack::AffectsPedGroup_Reversed(pedGroup);
#endif
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
    if (player)
        player->RegisterReference(reinterpret_cast<CEntity**>(&m_player));
}

CEventDontJoinPlayerGroup::~CEventDontJoinPlayerGroup()
{
    if (m_player)
        m_player->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_player));
}

CEventDontJoinPlayerGroup* CEventDontJoinPlayerGroup::Constructor(CPed* player)
{
    this->CEventDontJoinPlayerGroup::CEventDontJoinPlayerGroup(player);
    return this;
}

CEventNewGangMember::CEventNewGangMember(CPed* member)
{
    m_member = member;
    if (member)
        member->RegisterReference(reinterpret_cast<CEntity**>(&m_member));
}

CEventNewGangMember::~CEventNewGangMember()
{
    if (m_member)
        m_member->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_member));
}

CEventNewGangMember* CEventNewGangMember::Constructor(CPed* member)
{
    this->CEventNewGangMember::CEventNewGangMember(member);
    return this;
}
