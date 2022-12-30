#include "StdInc.h"

#include "TaskComplexChat.h"
#include "InterestingEvents.h"
#include "TaskSimpleRunAnim.h"
#include "TaskSimpleStandStill.h"

// 0x682CB0
CTaskComplexChat::CTaskComplexChat(bool a2, CPed* ped, int32 updateDirectionCount, int16 conversationId) : CTaskComplex() {
    byteC = a2;
    m_UpdateDirectionCount = updateDirectionCount;
    m_Ped = ped;
    m_ConversationId = conversationId;
    CEntity::SafeRegisterRef(m_Ped);
    byte1A = 0;
    dword1C = 0;
}

// 0x682D40
CTaskComplexChat::~CTaskComplexChat() {
    CEntity::SafeCleanUpRef(m_Ped);
}

// 0x682DA0
CTask* CTaskComplexChat::Clone() {
    auto* task = new CTaskComplexChat(byteC, m_Ped, m_UpdateDirectionCount, m_ConversationId);
    task->byte1A = byte1A;
    return task;
}

// 0x682E10
CTask* CTaskComplexChat::CreateNextSubTask(CPed* ped) {
    return nullptr;
}

// 0x682E20
CTask* CTaskComplexChat::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x682E20, CTaskComplexChat*, CPed*>(this, ped);

    if (!m_Ped)
        return nullptr;

    if (!byteC) {
        return new CTaskSimpleStandStill(999999);
    }

    if (m_ConversationId > -1) {
        ped->Say(m_ConversationId);
    }

    g_InterestingEvents.Add(CInterestingEvents::INTERESTING_EVENT_1, ped);

    if (m_ConversationId == 164 || m_ConversationId > 166 && m_ConversationId <= 168) {
        auto RandomNumberInRange = CGeneral::GetRandomNumberInRange(0, 3);
        if (RandomNumberInRange) {
            if (RandomNumberInRange == 1) {
                return new CTaskSimpleRunAnim(ANIM_GROUP_DEFAULT, ANIM_ID_ENDCHAT_02, 4.0f, 0);
            } else if (RandomNumberInRange == 2) {
                return new CTaskSimpleRunAnim(ANIM_GROUP_DEFAULT, ANIM_ID_ENDCHAT_03, 4.0f, 0);
            } else {
                // todo: return new CTaskSimpleChat(4000);
            }
        }
        return new CTaskSimpleRunAnim(ANIM_GROUP_DEFAULT, ANIM_ID_ENDCHAT_01, 4.0f, 0);
    }
    // todo: return new CTaskSimpleChat(999999);
}

// 0x683060
CTask* CTaskComplexChat::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x683060, CTaskComplexChat*, CPed*>(this, ped);
}
