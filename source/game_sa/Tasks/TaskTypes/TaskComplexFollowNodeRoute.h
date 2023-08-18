#pragma once

#include "TaskComplex.h"
#include "PathFind.h"

class CPointRoute;

class CTaskComplexFollowNodeRoute : public CTaskComplex {
public:
    CVector      m_vecTargetPos;
    int32        m_nMode;
    float        m_fRadius;
    float        m_fUnkn1;
    float        m_fUnkn2;
    CNodeAddress m_nodeAddress1;
    CNodeRoute*  m_pNodeRoute;
    CPointRoute* m_pPointRoute;
    CNodeAddress m_nodeAddress2;
    int32        unkn0;
    int32        m_nTime;
    int32        m_nTimeStarted;
    int32        m_nTimeStopped;
    bool         bUnkn1;
    bool         m_bStoppedMaybe;
    union {
        uint32 m_nFlags;
        struct {
            uint32 m_bUnknFlag0x1 : 1;
            uint32 m_bUnknFlag0x2 : 1;
            uint32 m_bUnknFlag0x4 : 1;
            uint32 m_bUnknFlag0x8 : 1;

            uint32 : 1;
            uint32 m_bUnknFlag0x20 : 1;
            uint32 m_bUnknFlag0x40 : 1;
        };
    };
    float m_afUnkn[4];

public:
    static constexpr auto Type = TASK_COMPLEX_FOLLOW_NODE_ROUTE;

    CTaskComplexFollowNodeRoute(int32 mode, const CVector& targetPos, float radius, float fUnkn1, float fUnkn2, bool bUnknFlag, int32 time, bool bUnknFlag2);
    ~CTaskComplexFollowNodeRoute() override;

    eTaskType GetTaskType() const override { return Type; } // 0x66EB60
    CTask* Clone() const override;
    void StopTimer(const CEvent* event) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    uint32 GetRouteSize();
    static eTaskType GetSubTaskType(int32 unkn, bool bUnkn, const CPointRoute& pointRoute);
    CVector GetLastWaypoint(CPed* ped);
    CVector GetNextWaypoint(CPed* ped);
    void ComputeRoute();
    eTaskType CalcGoToTaskType(CPed* ped, eTaskType taskType);
    float CalcBlendRatio(CPed* ped, bool bUsePointRoute);
    bool CanGoStraightThere(CPed* ped, const CVector& from, const CVector& to, float maxDist);
    void ComputePathNodes(const CPed* ped);
    void SetTarget(CPed* ped, const CVector& target, float radius, float fUnkn1, float fUnkn2, bool bForce);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTask* Clone_Reversed() { return CTaskComplexFollowNodeRoute::Clone(); };
    void StopTimer_Reversed(const CEvent* event) { CTaskComplexFollowNodeRoute::StopTimer(event); };
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) { return CTaskComplexFollowNodeRoute::MakeAbortable(ped, priority, event); };
    CTask* CreateNextSubTask_Reversed(CPed* ped) { return CTaskComplexFollowNodeRoute::CreateNextSubTask(ped); };
    CTask* CreateFirstSubTask_Reversed(CPed* ped) { return CTaskComplexFollowNodeRoute::CreateFirstSubTask(ped); };
    CTask* ControlSubTask_Reversed(CPed* ped) { return CTaskComplexFollowNodeRoute::ControlSubTask(ped); };

};

VALIDATE_SIZE(CTaskComplexFollowNodeRoute, 0x60);
