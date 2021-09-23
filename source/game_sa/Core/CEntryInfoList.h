#pragma once

#include "CEntryInfoNode.h"

class CEntryInfoList {
public:
    CEntryInfoNode* m_pNode;

public:
    static void InjectHooks();

    void Flush();                           // 0x536E10
    void DeleteNode(CEntryInfoNode* pNode); // Most likely inlined in final exe
};
VALIDATE_SIZE(CEntryInfoList, 0x4);
