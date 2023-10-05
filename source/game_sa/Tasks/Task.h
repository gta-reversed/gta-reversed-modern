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
class CTask;

template<typename T>
concept Task = std::is_base_of_v<CTask, T>;

class CTask {
public:
    CTask* m_pParentTask;

    void* operator new(size_t size);
    void operator delete(void* object);

    CTask() { m_pParentTask = nullptr; } // 0x61A340
    virtual ~CTask() = default;          // 0x61A660

    virtual CTask* Clone() const = 0;
    virtual CTask* GetSubTask() = 0;
    virtual bool IsSimple() = 0;
    virtual eTaskType GetTaskType() const = 0;
    virtual void StopTimer(const CEvent* event);
    virtual bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) = 0;

    static bool IsGoToTask(CTask* task);
    static bool IsTaskPtr(CTask* task);

    CTaskSimple*  AsSimple()  { return reinterpret_cast<CTaskSimple*>(this); }
    CTaskComplex* AsComplex() { return reinterpret_cast<CTaskComplex*>(this); }

    /// Works like `dynamic_cast` => Checks if task if ofthe required type, if so, returns it, otherwise nullptr
    template<Task T>
    static T* DynCast(CTask* task) {
        if (task) {
            if (task->GetTaskType() == T::Type) {
                return static_cast<T*>(task);
            }
        }
        return nullptr;
    }

    template<eTaskType... Types>
    static bool IsA(CTask* task) {
        const auto ttype = task->GetTaskType();
        return ((ttype == Types) || ...);
    }

    template<Task... Ts>
    static bool IsA(CTask* task) {
        return IsA<Ts::Type...>(task);
    }


    /// Works like `static_cast` + in debug mode asserts the type to be as expected.
    template<Task T>
    static T* Cast(CTask* task) {
        assert(!task || task->GetTaskType() == T::Type);
        return static_cast<T*>(task);
    }
};
VALIDATE_SIZE(CTask, 0x8);


