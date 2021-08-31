#include "StdInc.h"

void CTaskComplexWalkRoundObject::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexWalkRoundObject", "CTaskComplexWalkRoundObject", 0x655020, &CTaskComplexWalkRoundObject::Constructor);
}

CTaskComplexWalkRoundObject::CTaskComplexWalkRoundObject(std::int32_t moveState, CVector* targetPoint, CEntity* object)
{
    m_moveState = moveState;
    m_targetPoint = *targetPoint;
    m_object = object;
    field_24 = 0;
    field_28 = 0;
    field_2C = 0;
    field_2D = 0;
    if (m_object)
        m_object->RegisterReference(reinterpret_cast<CEntity**>(&m_object));
    m_pointRoute = CPools::ms_pPointRoutePool->New();
    if (m_pointRoute)
        m_pointRoute->field_0 = 0;
}

CTaskComplexWalkRoundObject::~CTaskComplexWalkRoundObject()
{
    if (m_object)
        m_object->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_object));
    if (m_pointRoute)
        CPools::ms_pPointRoutePool->Delete(m_pointRoute);
}

CTaskComplexWalkRoundObject* CTaskComplexWalkRoundObject::Constructor(std::int32_t moveState, CVector* targetPoint, CEntity* object)
{
    this->CTaskComplexWalkRoundObject::CTaskComplexWalkRoundObject(moveState, targetPoint, object);
    return this;
}

CTask* CTaskComplexWalkRoundObject::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x6575F0, CTaskComplexWalkRoundObject*, CPed*>(this, ped);
}

CTask* CTaskComplexWalkRoundObject::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x657220, CTaskComplexWalkRoundObject*, CPed*>(this, ped);
}

CTask* CTaskComplexWalkRoundObject::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x657380, CTaskComplexWalkRoundObject*, CPed*>(this, ped);
}

CTask* CTaskComplexWalkRoundObject::CreateRouteTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x655140, CTaskComplexWalkRoundObject*, CPed*>(this, ped);
}

