#pragma once
#include "TaskComplex.h"

class CPedGroup;
class CEntity;

class CTaskComplexGangLeader : public CTaskComplex {
public:
    CPedGroup* m_PedGroup = {};    // 0xC
    uint32 m_Time = {};            // 0x10
    int32 m_Time1 = {};            // 0x14
    bool byte18 = {};              // 0x18
    uint8 byte19 = {};             // 0x19
    uint8 gap1A[2] = {};           // 0x1A
    int32 m_Time2 = {};            // 0x1C
    int32 m_Time3 = {};            // 0x20
    uint8 byte24 = {};             // 0x24
    bool m_bTime = {};             // 0x25
    uint8 gap26[2] = {};           // 0x26
    int32 dword28 = {};            // 0x28
    int32 dword2C = {};            // 0x2C
    uint8 byte30 = {};             // 0x30
    uint8 byte31 = {};             // 0x31
    uint8 gap32[2] = {};           // 0x32
    bool byte34 = {};              // 0x34

public:
    static void InjectHooks();

    ~CTaskComplexGangLeader();
    CTaskComplexGangLeader(CPedGroup* pedGroup);

    static int32 GetRandomGangAmbientAnim(CPed* ped, CEntity* entity);
    static bool ShouldLoadGangAnims();
    static void DoGangAbuseSpeech(CPed* ped, CPed* a2);

    CPed* TryToPassObject(CPed* ped, CPedGroup* pedGroup);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_LEADER;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);
    virtual void ScanForStuff(CPed* ped);

private: // Wrappers for hooks
    // 0x65DED0
    CTaskComplexGangLeader* Constructor(CPedGroup* pedGroup) {
        this->CTaskComplexGangLeader::CTaskComplexGangLeader(pedGroup);
        return this;
    }

    // 0x65DF30
    CTaskComplexGangLeader* Destructor() {
        this->CTaskComplexGangLeader::~CTaskComplexGangLeader();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexGangLeader, 0x38);
