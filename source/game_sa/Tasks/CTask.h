/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eTaskType.h"

enum eAbortPriority : int
{
    ABORT_PRIORITY_LEISURE = 0,
    ABORT_PRIORITY_URGENT,
    ABORT_PRIORITY_IMMEDIATE
};

class CTask {
public:
    class CTask* m_pParentTask;

    void* operator new(unsigned int size);
    void operator delete(void* object);

    CTask();
    virtual ~CTask();

    virtual class CTask* Clone() = 0;
    virtual class CTask* GetSubTask() = 0;
    virtual bool IsSimple() = 0;
    virtual eTaskType GetId() = 0;
    virtual void StopTimer(class CEvent* _event);
    virtual bool MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event) = 0;

    static bool IsGoToTask(CTask* pTask);
};

VALIDATE_SIZE(CTask, 8);
