#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CPed;
class CEntity;

class CTaskComplexTurnToFaceEntityOrCoord : public CTaskComplex {
public:
    CEntity* m_entityToFace = {};
    bool m_bFaceEntity = {};
    CVector m_coordsToFace = {};
    float m_fChangeRateMult = {};
    float m_fMaxHeading = {};

public:
    static void InjectHooks();

    constexpr static auto Type = eTaskType::TASK_COMPLEX_TURN_TO_FACE_ENTITY;

    CTaskComplexTurnToFaceEntityOrCoord(CEntity* entity, float changeRateMult, float maxHeading);
    CTaskComplexTurnToFaceEntityOrCoord(CVector const& coords, float changeRateMult, float maxHeading);
    ~CTaskComplexTurnToFaceEntityOrCoord() override;

    CTask* Clone() override;
    eTaskType GetTaskType() override { return Type; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    float ComputeTargetHeading(CPed* ped) const;
private: // Wrappers for hooks
    // 0x66B890
    CTaskComplexTurnToFaceEntityOrCoord* Constructor(CEntity* entity, float changeRateMult, float maxHeading) {
        this->CTaskComplexTurnToFaceEntityOrCoord::CTaskComplexTurnToFaceEntityOrCoord(entity, changeRateMult, maxHeading);
        return this;
    }
    // 0x66B910
    CTaskComplexTurnToFaceEntityOrCoord* Constructor(CVector const& coords, float changeRateMult, float maxHeading) {
        this->CTaskComplexTurnToFaceEntityOrCoord::CTaskComplexTurnToFaceEntityOrCoord(coords, changeRateMult, maxHeading);
        return this;
    }

    // 0x66B960
    CTaskComplexTurnToFaceEntityOrCoord* Destructor() {
        this->CTaskComplexTurnToFaceEntityOrCoord::~CTaskComplexTurnToFaceEntityOrCoord();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexTurnToFaceEntityOrCoord, 0x28);
