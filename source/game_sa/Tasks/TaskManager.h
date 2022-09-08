/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Base.h"
#include <initializer_list>
#include "Task.h"
#include <algorithm>

enum ePrimaryTasks // array indexes
{
    TASK_PRIMARY_PHYSICAL_RESPONSE = 0,
    TASK_PRIMARY_EVENT_RESPONSE_TEMP,
    TASK_PRIMARY_EVENT_RESPONSE_NONTEMP,
    TASK_PRIMARY_PRIMARY,
    TASK_PRIMARY_DEFAULT,
    TASK_PRIMARY_MAX
};

enum eSecondaryTask : uint32 // array indexes
{
    TASK_SECONDARY_ATTACK = 0,              // want duck to be after attack
    TASK_SECONDARY_DUCK,                    // because attack controls ducking movement
    TASK_SECONDARY_SAY,
    TASK_SECONDARY_FACIAL_COMPLEX,
    TASK_SECONDARY_PARTIAL_ANIM,
    TASK_SECONDARY_IK,
    TASK_SECONDARY_MAX
};

class CTaskComplex;
class CTaskSimple;
class CPed;

class CTaskManager {
public:

    std::array<CTask*, TASK_PRIMARY_MAX>   m_aPrimaryTasks{};
    std::array<CTask*, TASK_SECONDARY_MAX> m_aSecondaryTasks{};
    CPed*                                  m_pPed{};

public:
    static void InjectHooks();

    explicit CTaskManager(CPed* ped);
    ~CTaskManager();

    CTask* GetActiveTask();
    CTask* FindActiveTaskByType(int32 taskType);
    CTask* FindTaskByType(ePrimaryTasks taskIndex, eTaskType taskType);
    CTask* GetTaskSecondary(eSecondaryTask taskIndex);

    bool HasTaskPrimary(const CTask* task);
    bool HasTaskSecondary(const CTask* task);

    /// Delete all tasks
    void Flush();
    void FlushImmediately();

    void SetNextSubTask(CTaskComplex* task);

    void StopTimers(const CEvent* event);
    CTask* GetSimplestActiveTask();
    CTaskSimple* GetSimplestTask(int32 taskIndex);
    static CTaskSimple* GetSimplestTask(CTask* task);

    void AddSubTasks(CTaskComplex* task);
    void ParentsControlChildren(CTaskComplex* task);
    void SetTask(CTask* task, int32 taskIndex, bool unused = false);
    void SetTaskSecondary(CTask* task, int32 taskIndex);
    void ClearTaskEventResponse();
    void ManageTasks();

    // Why they doesn't have version for *primary tasks*? :thinking:
    CTask* GetTaskPrimary(int32 taskIndex) noexcept {
        return m_aPrimaryTasks[taskIndex];
    }

    auto& GetPrimaryTasks() const { return m_aPrimaryTasks; }
    auto& GetSecondaryTasks() const { return m_aSecondaryTasks; }


    // NOTSA - Check if any of the given tasks is active
    bool IsAnyTaskActiveByType(std::initializer_list<int32> types) {
        return std::any_of(types.begin(), types.end(), [this](auto type) {
            return FindActiveTaskByType(type);
        });
    }

    CTask* FindActiveTaskFromList(std::initializer_list<eTaskType> types) {
        for (auto type : types) {
            if (const auto task = FindActiveTaskByType(type)) {
                return task;
            }
        }
        return nullptr;
    }

    // Find active task, check if its of type `T`, and return it, nullptr othetwise (if not found/not of the requrested type)
    template<Task T>
    T* GetActiveTaskAs() {
        if (const auto task = GetActiveTask()) {
            if (task->GetTaskType() == T::Type) {
                return static_cast<T*>(task);
            }
        }
        return nullptr;
    }

    // Find simplest active task, check if its of type `T`, and return it, nullptr othetwise (if not found/not of the requrested type)
    template<Task T>
    T* GetSimplestActiveTaskAs() {
        if (const auto task = GetSimplestActiveTask()) {
            if (task->GetTaskType() == T::Type) {
                return static_cast<T*>(task);
            }
        }
        return nullptr;
    }

    // Find an active task from the give types and return the first one.
    template<eTaskType... Ts>
    auto Find() { // TODO: For now just return `CTask*`, but would be nice to return the first common base class somehow
        CTask* ret{};
        (... || (ret = FindActiveTaskByType(Ts))); // Find first active task from given types
        return ret;
    }

    // Find an active task from the given types and return the first one.
    template<Task... Ts>
    auto Find() requires(sizeof...(Ts) > 1) { // Only use this overload if there's more than 1 Task
        return Find<Ts::Type...>();
    }

    template<Task T>
    T* Find() {
        return static_cast<T*>(Find<T::Type>());
    }

    template<Task... Ts>
    bool HasAnyOf() {
        // This won't work if the task has no `Type` member
        // If it has a `GetTaskType` function feel free to add it,
        // otherwise don't.
        return (... || FindActiveTaskByType(Ts::Type));
    }

    template<eTaskType... Ts>
    bool HasAnyOf() {
        return (... || Find<Ts>());
    }

    template<eTaskType T>
    bool Has() {
        return Find<T>();
    }

    // Checks if the first found task is the same for both
    template<eTaskType... Ts>
    bool IsFirstFoundTaskMatching(CTaskManager& mgr) {
        if (const auto our = Find<Ts...>()) {
            if (const auto other = mgr.Find<Ts...>()) { // Find first task from the list
                if (our->GetTaskType() == other->GetTaskType()) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    CTaskManager* Constructor(CPed* ped) {
        this->CTaskManager::CTaskManager(ped);
        return this;
    }

    CTaskManager* Destructor() {
        this->CTaskManager::~CTaskManager();
        return this;
    }
};

VALIDATE_SIZE(CTaskManager, 0x30);
