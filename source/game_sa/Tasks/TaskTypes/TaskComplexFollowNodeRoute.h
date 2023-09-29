#pragma once

#include "TaskComplex.h"
#include "PathFind.h"

class CPointRoute;

class NOTSA_EXPORT_VTABLE CTaskComplexFollowNodeRoute final : public CTaskComplex {
public:
    static constexpr auto Type = TASK_COMPLEX_FOLLOW_NODE_ROUTE;

    //static eTaskType GetSubTaskType(int32 unkn, bool bUnkn, const CPointRoute& pointRoute);

    CTaskComplexFollowNodeRoute(
        eMoveState     moveState,
        const CVector& targetPt,
        float          targetPtTolerance,
        float          slowDownDist,
        float          followNodeThresholdHeightChange,
        bool           bKeepNodesHeadingAwayFromTarget,
        int32          time,
        bool           bUseBlending
    );
    CTaskComplexFollowNodeRoute(const CTaskComplexFollowNodeRoute&);
    ~CTaskComplexFollowNodeRoute() override;

    eTaskType GetTaskType() const override { return Type; } // 0x66EB60
    CTask*    Clone() const override { return new CTaskComplexFollowNodeRoute{*this}; }
    void      StopTimer(const CEvent* event) override;
    bool      MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    CTask*    CreateNextSubTask(CPed* ped) override;
    CTask*    CreateFirstSubTask(CPed* ped) override;
    CTask*    ControlSubTask(CPed* ped) override;

    CTask*    CreateSubTask(eTaskType taskType, CPed* ped);

    CVector   GetLastWaypoint(CPed* ped);
    CVector   GetNextWaypoint(CPed* ped);
    //uint32  GetRouteSize();
    void      ComputeRoute();
    eTaskType CalcGoToTaskType(CPed* ped, eTaskType taskType);
    float     CalcBlendRatio(CPed* ped, bool bUsePointRoute);
    bool      CanGoStraightThere(CPed* ped, const CVector& from, const CVector& to, float maxDist);
    void      ComputePathNodes(const CPed* ped);
    void      SetTarget(CPed* ped, const CVector& target, float radius, float fUnkn1, float fUnkn2, bool bForce);

public:
    CVector      m_TargetPt{};                              //< Point we're trying to get to
    eMoveState   m_MoveState{};                             //< Move state to use to get to this point
    float        m_TargetPtTolerance{};                     //< Tolerance [Determinates how close the ped has to get to the point for the task to be considered as finished]
    float        m_SlowDownDist{};                      
    float        m_FollowNodeThresholdHeightChange{};   
    CNodeAddress m_StartNode{};
    CNodeRoute*  m_NodeRoute{};
    CPointRoute* m_PtRoute{};
    CNodeAddress m_CurrNode{};
    int32        m_CurrPt{};                                //< Current point we're at [If using `m_PtRoute`]
    int32        m_Time{};
    CTaskTimer   m_Timer{};
    bool         m_bKeepNodesHeadingAwayFromTarget : 1{};
    bool         m_LastRoutePointIsTarget : 1{};
    bool         m_bNewTarget : 1{};
    bool         m_bUseBlending : 1{};
    bool         m_bWillSlowDown : 1{};
    bool         m_bSlowingDown : 1{};
    bool         m_bSpeedingUp : 1{};
    float        m_SpeedDecreaseDist{};
    float        m_SpeedIncreaseDist{};
    float        m_SpeedDecreaseAmt{};
    float        m_SpeedIncreaseAmt{};

private: // Hook shit, ignore
    friend void InjectHooksMain();
    static void InjectHooks();

    // 0x66EA30
    CTaskComplexFollowNodeRoute* Constructor(eMoveState moveState, CVector const& targetPoint, float radius, float a5, float a6, bool a7, int32 time, bool a9) {
        this->CTaskComplexFollowNodeRoute::CTaskComplexFollowNodeRoute(moveState, targetPoint, radius, a5, a6, a7, time, a9);
        return this;
    }

    // 0x66EB70
    CTaskComplexFollowNodeRoute* Destructor() {
        this->CTaskComplexFollowNodeRoute::~CTaskComplexFollowNodeRoute();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexFollowNodeRoute, 0x60);
