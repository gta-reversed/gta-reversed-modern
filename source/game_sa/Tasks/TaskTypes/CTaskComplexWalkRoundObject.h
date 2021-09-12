#include "CTaskComplex.h"
#include "CVector.h"

class CPointRoute;
class CTaskComplexWalkRoundObject : public CTaskComplex {
public:
    int32 m_moveState;
    CVector m_targetPoint;
    CEntity* m_object;
    CPointRoute* m_pointRoute;
    int32 field_24;
    int32 field_28;
    int8 field_2C;
    int8 field_2D;
    int32 field_30;

    static void InjectHooks();

    CTaskComplexWalkRoundObject(int32 moveState, CVector* targetPoint, CEntity* object);
    ~CTaskComplexWalkRoundObject();
private:
    CTaskComplexWalkRoundObject* Constructor(int32 moveState, CVector* targetPoint, CEntity* object);
public:
    CTask* Clone() override { return new CTaskComplexWalkRoundObject(m_moveState,&m_targetPoint, m_object); }
    eTaskType GetTaskType() override { return TASK_COMPLEX_WALK_ROUND_OBJECT; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
public:
    CTask* CreateRouteTask(CPed* ped);

};

VALIDATE_SIZE(CTaskComplexWalkRoundObject, 0x34);
