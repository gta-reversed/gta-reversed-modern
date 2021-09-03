/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskComplex.h"
#include "CNodeAddress.h"

enum eWanderType
{
    WANDER_TYPE_STANDARD = 0,
    WANDER_TYPE_COP,
    WANDER_TYPE_MEDIC,
    WANDER_TYPE_CRIMINAL,
    WANDER_TYPE_GANG,
    WANDER_TYPE_SHOP,
    WANDER_TYPE_FLEE,
    WANDER_TYPE_PROSTITUTE
};

class CPed;
class CNodeAddress;
class CVector;

class CTaskComplexWander : public CTaskComplex {
protected:
    CTaskComplexWander(plugin::dummy_func_t) : CTaskComplex() {}
public:
    int32 m_nMoveState; // see eMoveState
    uint8 m_nDir;
private:
    char _pad[3];
public:
    float m_fTargetRadius;

    CNodeAddress m_LastNode;
    CNodeAddress m_NextNode;

    int32 m_nLastUpdateDirFrameCount;

    union
    {
        uint8 m_nFlags;
        struct {
            uint8 m_bWanderSensibly : 1;
            uint8 m_bNewDir : 1;
            uint8 m_bNewNodes : 1;
            uint8 m_bAllNodesBlocked : 1;
        };
    };

    static void InjectHooks();
    CTaskComplexWander(int32 moveState, uint8 dir, bool bWanderSensibly = true, float fTargetRadius = 0.5f);
    ~CTaskComplexWander();
    CTaskComplexWander* Constructor(int32 moveState, uint8 dir, bool bWanderSensibly = true, float fTargetRadius = 0.5f);

    // original virtual functions
    eTaskType GetId() override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    virtual int32 GetWanderType() = 0;
    virtual void ScanForStuff(CPed* ped) = 0;
    virtual void UpdateDir(CPed* pPed);
    virtual void UpdatePathNodes(CPed* pPed, int8 dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8* outDir);

    // reversed virtual functions
    eTaskType GetId_Reversed() { return TASK_COMPLEX_WANDER; };
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    void UpdateDir_Reversed(CPed* pPed);
    void UpdatePathNodes_Reversed(CPed* pPed, int8 dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8* outDir);

    CTask* CreateSubTask(CPed* ped, int32 taskId);
    void ComputeTargetPos(CPed* pPed, CVector* pOutTargetPos, CNodeAddress* pTargetNodeAddress);
    float ComputeTargetHeading(CPed* ped);
    bool ValidNodes();
    void ScanForBlockedNodes(CPed* pPed);
    bool ScanForBlockedNode(CPed* pPed, CNodeAddress* targetNodeAddress);
    bool ScanForBlockedNode(CVector* position, class CEntity* pEntity);

    static CTaskComplexWander* GetWanderTaskByPedType(CPed* pPed);
};

VALIDATE_SIZE(CTaskComplexWander, 0x28);
