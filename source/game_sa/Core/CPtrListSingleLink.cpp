#include "StdInc.h"

void CPtrListSingleLink::Flush()
{
    plugin::CallMethod<0x552400, CPtrListSingleLink*>(this);
}

void CPtrListSingleLink::AddItem(void* item)
{
    plugin::CallMethod<0x5335E0, CPtrListSingleLink*, void*>(this, item);
}

void CPtrListSingleLink::DeleteItem(void* item)
{
    plugin::CallMethod<0x533610, CPtrListSingleLink*, void*>(this, item);
}
