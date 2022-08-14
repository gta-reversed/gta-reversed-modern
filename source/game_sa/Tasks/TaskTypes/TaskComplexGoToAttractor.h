#pragma once
#include "TaskComplex.h"

class CTaskComplexGoToAttractor : public CTaskComplex {
public:
    CPedAttractor* m_pAttractor = {}; // 0xC
    CVector m_vecAttrPosn = {};       // 0x10
    float m_fAttrHeading = {};        // 0x1C
    float m_fAttrTime = {};           // 0x20
    int32 m_nQueueNumber = {};        // 0x24
    int32 field_28 = {};              // 0x28

public:
    static void InjectHooks();

    ~CTaskComplexGoToAttractor();
    CTaskComplexGoToAttractor(CPedAttractor* attractor, CVector const& attrPosn, float attrHeading, float attrTime, int32 queueNumber, int32 a7);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_ATTRACTOR;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x66B640
    CTaskComplexGoToAttractor* Constructor(CPedAttractor* attractor, CVector const& attrPosn, float attrHeading, float attrTime, int32 queueNumber, int32 a7) {
        this->CTaskComplexGoToAttractor::CTaskComplexGoToAttractor(attractor, attrPosn, attrHeading, attrTime, queueNumber, a7);
        return this;
    }

    // 0x66B6A0
    CTaskComplexGoToAttractor* Destructor() {
        this->CTaskComplexGoToAttractor::~CTaskComplexGoToAttractor();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGoToAttractor, 0x2C);
