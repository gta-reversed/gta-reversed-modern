#pragma once

#include "TaskComplex.h"

class CTaskComplexHitResponse;
class CPed;

enum class eHitSide : int32 {
    FRONT,
    LEFT,
    BACK,
    RIGHT
};

class NOTSA_EXPORT_VTABLE CTaskComplexHitResponse final : public CTaskComplex {
public:
    eHitSide m_HitSide = {};

public:
    static constexpr auto Type = eTaskType::TASK_COMPLEX_HIT_RESPONSE;

    static void InjectHooks();

    CTaskComplexHitResponse(eHitSide hs);
    CTaskComplexHitResponse(const CTaskComplexHitResponse&);
    ~CTaskComplexHitResponse() override = default;

    CTask*    Clone() const override { return new CTaskComplexHitResponse{ *this }; }
    eTaskType GetTaskType() const override { return Type; }
    CTask*    CreateNextSubTask(CPed* ped) override { return nullptr; }
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override { return m_pSubTask; }

private: // Wrappers for hooks
    // 0x631D70
    CTaskComplexHitResponse* Constructor(eHitSide hs) {
        this->CTaskComplexHitResponse::CTaskComplexHitResponse(hs);
        return this;
    }

    // 0x631DA0
    CTaskComplexHitResponse* Destructor() {
        this->CTaskComplexHitResponse::~CTaskComplexHitResponse();
        return this;
    }
};
