/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eTaskType.h"

enum eAbortPriority : int32 {
    ABORT_PRIORITY_LEISURE = 0,
    ABORT_PRIORITY_URGENT,
    ABORT_PRIORITY_IMMEDIATE
};

class CEvent;
class CPed;
class CTaskSimple;
class CTaskComplex;

class CTask {
public:
    class CTask* m_pParentTask;

    void* operator new(uint32 size);
    void operator delete(void* object);

    CTask() { m_pParentTask = nullptr; } // 0x61A340
    virtual ~CTask() = default;          // 0x61A660

    virtual class CTask* Clone() = 0;
    virtual class CTask* GetSubTask() = 0;
    virtual bool IsSimple() = 0;
    virtual eTaskType GetTaskType() = 0;
    virtual void StopTimer(const CEvent* event);
    virtual bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) = 0;

    static bool IsGoToTask(CTask* task);

    CTaskSimple*  AsSimple()  { return reinterpret_cast<CTaskSimple*>(this); }
    CTaskComplex* AsComplex() { return reinterpret_cast<CTaskComplex*>(this); }

    // NOTSA

    // I thought this is a good idea, turns out not so much
    // TODO: Get rid of it :D
    template<typename T>
    T* As() {
        return static_cast<T*>(this);
    }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void* New(uint32);
    void  Delete(void* object);
};

VALIDATE_SIZE(CTask, 0x8);
