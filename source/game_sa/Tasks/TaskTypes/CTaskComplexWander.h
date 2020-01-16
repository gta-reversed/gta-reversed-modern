/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
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
    CTaskComplexWander(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    int m_nMoveState; // see eMoveState
    unsigned char m_nDir;
private:
    char _pad[3];
public:
    float m_fTargetRadius;

    CNodeAddress m_LastNode;
    CNodeAddress m_NextNode;

    int m_nLastUpdateDirFrameCount;

    union
    {
        unsigned char m_nFlags;
        struct {
            unsigned char m_bWanderSensibly : 1;
            unsigned char m_bNewDir : 1;
            unsigned char m_bNewNodes : 1;
            unsigned char m_bAllNodesBlocked : 1;
        };
    };

    static void InjectHooks();

    // original virtual functions
    eTaskType GetId() override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    virtual int GetWanderType();
    virtual void ScanForStuff(CPed* ped);
    virtual void UpdateDir(CPed* pPed);
    virtual void UpdatePathNodes(CPed* pPed, int8_t dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8_t* outDir);

    // reversed virtual functions
    eTaskType GetId_Reversed();
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);

    void UpdateDir_Reversed(CPed* pPed);
    void UpdatePathNodes_Reversed(CPed* pPed, int8_t dir, CNodeAddress* originNode, CNodeAddress* targetNode, int8_t* outDir);

    CTaskComplexWander* Constructor(int moveState, unsigned char dir, bool bWanderSensibly, float fTargetRadius = 0.5f);
    CTask* CreateSubTask(CPed* ped, int taskId);
    void ComputeTargetPos(CPed* pPed, CVector* pOutTargetPos, CNodeAddress* pTargetNodeAddress);
    float ComputeTargetHeading(CPed* ped);
    bool ValidNodes();
    void ScanForBlockedNodes(CPed* pPed);
    bool ScanForBlockedNode(CPed* pPed, CNodeAddress* targetNodeAddress);
    bool ScanForBlockedNode(CVector* position, class CEntity* pEntity);

    static CTaskComplexWander* GetWanderTaskByPedType(CPed* pPed);
};

VALIDATE_SIZE(CTaskComplexWander, 0x28);
