#pragma once

#include "TaskComplex.h"

class CEntity;

class CTaskComplexChat : public CTaskComplex {
public:
    bool  byteC;
    CPed* m_Ped;
    int32 m_UpdateDirectionCount;
    int16 m_ConversationId;
    int8  byte1A;
    int32 dword1C;

public:
    CTaskComplexChat(bool a2, CPed* ped, int32 updateDirectionCount, int16 conversationId);
    ~CTaskComplexChat() override;

    eTaskType GetTaskType() override { return TASK_COMPLEX_CHAT; } // 0x682D30
    CTask* Clone() override;

    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
};
VALIDATE_SIZE(CTaskComplexChat, 0x20);
