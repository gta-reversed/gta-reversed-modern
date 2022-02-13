#pragma once

#include "TaskComplex.h"
#include "PathFind.h"

struct CPointRoute;

class CTaskComplexFollowNodeRoute : public CTaskComplex {
public:
    CVector m_vecTargetPos;
    int m_nMode;
    float m_fRadius;
    float m_fUnkn1;
    float m_fUnkn2;
    CNodeAddress m_nodeAddress1;
    CNodeRoute* m_pNodeRoute;
    CPointRoute* m_pPointRoute;
    CNodeAddress m_nodeAddress2;
    int unkn0;
    int m_nTime;
    int m_nTimeStartMaybe;
    int m_nSomeTime;
    bool bUnkn1;
    bool m_bStoppedMaybe;
    union {
        uint32_t m_nFlags;
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
    CTaskComplexFollowNodeRoute(int mode, const CVector& targetPos, float radius, float fUnkn1, float fUnkn2, bool bUnknFlag, int time, bool bUnknFlag2);
    ~CTaskComplexFollowNodeRoute();

    CTask* Clone() override {
        auto* clone = new CTaskComplexFollowNodeRoute(m_nMode, m_vecTargetPos, m_fRadius, m_fUnkn1, m_fUnkn2, m_bUnknFlag0x1, m_nTime, m_bUnknFlag0x8);
        clone->m_nodeAddress1 = m_nodeAddress1;
        return clone;
    }
    eTaskType GetTaskType() override {
        return TASK_COMPLEX_FOLLOW_NODE_ROUTE;
    }

    void StopTimer(const CEvent* event) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
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
    void ComputePathNodes(CPed* ped);
    void SetTarget(CPed* ped, const CVector& target, float radius, float fUnkn1, float fUnkn2, bool bForce);


private:
    friend void InjectHooksMain();
    static void InjectHooks();

};

VALIDATE_SIZE(CTaskComplexFollowNodeRoute, 0x60);
