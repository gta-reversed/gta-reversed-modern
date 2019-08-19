/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "eTaskType.h"

enum eAbortPriority
{
    ABORT_PRIORITY_LEISURE = 0,
    ABORT_PRIORITY_URGENT,
    ABORT_PRIORITY_IMMEDIATE
};

class  CTask {
    CTask() = delete;
protected:
    CTask(plugin::dummy_func_t) {}
public:
//    DWORD * vTable;
	class CTask *m_pParentTask;

	void *operator new(unsigned int size);
	void operator delete(void *object);

    virtual class CTask* DeletingDestructor(uint8_t deletingFlags);
	virtual class CTask *Clone();//=0
	virtual class CTask *GetSubTask();//=0
	virtual bool IsSimple();//=0
	virtual eTaskType GetId();//=0
	virtual void StopTimer(class CEvent *_event);
	virtual bool MakeAbortable(class CPed *ped, eAbortPriority priority, class CEvent *_event);//=0
};

VALIDATE_SIZE(CTask, 8);