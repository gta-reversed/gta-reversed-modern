/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PtrList.h"
#include "PtrNodeSingleLink.h"

class CPtrListSingleLink : public CPtrList {
public:
    ~CPtrListSingleLink() { Flush(); }

    static void InjectHooks();

    void Flush();
    CPtrNodeSingleLink* AddItem(void* item);
    void DeleteItem(void* item);
    void DeleteNode(CPtrNodeSingleLink* node, CPtrNodeSingleLink* lastNode); // Most likely inlined in the final exe,

    CPtrNodeSingleLink* GetNode() { return reinterpret_cast<CPtrNodeSingleLink*>(m_node); }
};

VALIDATE_SIZE(CPtrListSingleLink, 4);
