#pragma once

#include "EntryInfoNode.h"

class CEntryInfoList {
public:
    CEntryInfoNode* m_node;

public:
    static void InjectHooks();

    void Flush();                          // 0x536E10
    void DeleteNode(CEntryInfoNode* node); // Most likely inlined in final exe
};

VALIDATE_SIZE(CEntryInfoList, 0x4);
