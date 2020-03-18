#pragma once
#include "PluginBase.h"

class CEntryInfoNode
{
public:
    class CPtrListDoubleLink*  m_pDoubleLinkList;
    class CPtrNodeDoubleLink* m_pDoubleLink;
    class CRepeatSector* m_pRepeatSector;
    CEntryInfoNode* m_pPrevious;
    CEntryInfoNode* m_pNext;
};

VALIDATE_SIZE(CEntryInfoNode, 0x14);
