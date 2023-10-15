#pragma once

#include "TaskComplex.h"

struct InteriorGroup_c;
struct Interior_c;
struct InteriorInfo_t;
class  CTaskInteriorBeInOffice;
class  CPed;

class NOTSA_EXPORT_VTABLE CTaskInteriorBeInOffice : public CTaskComplex {
public:
    static constexpr auto Type = eTaskType::TASK_INTERIOR_BE_IN_OFFICE;

    static void InjectHooks();

    CTaskInteriorBeInOffice(InteriorGroup_c*);
    CTaskInteriorBeInOffice(const CTaskInteriorBeInOffice&);
    ~CTaskInteriorBeInOffice() override = default;

    CTask*    Clone() const override { return new CTaskInteriorBeInOffice{ *this }; }
    eTaskType GetTaskType() const override { return Type; }
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override { return m_pSubTask; }

private:
    InteriorGroup_c* m_InteriorGroup{};
    Interior_c*      m_CurrInterior{};
    InteriorInfo_t*  m_CurrInteriorInfo{};

private: // Wrappers for hooks
    // 0x675220
    CTaskInteriorBeInOffice* Constructor(InteriorGroup_c* ig) {
        this->CTaskInteriorBeInOffice::CTaskInteriorBeInOffice(ig);
        return this;
    }

    // 0x675260
    CTaskInteriorBeInOffice* Destructor() {
        this->CTaskInteriorBeInOffice::~CTaskInteriorBeInOffice();
        return this;
    }
};
