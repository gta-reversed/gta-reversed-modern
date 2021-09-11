/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPtrList.h"
#include "CPtrNodeSingleLink.h"

class CPtrListSingleLink : public CPtrList {
public:
    inline CPtrNodeSingleLink *GetNode() {
        return reinterpret_cast<CPtrNodeSingleLink *>(pNode);
    }

    inline ~CPtrListSingleLink() {
        Flush();
    }

public:
    static void InjectHooks();
    void Flush();
    CPtrNodeSingleLink* AddItem(void* item);
    void DeleteItem(void* item);
    void DeleteNode(CPtrNodeSingleLink* node, CPtrNodeSingleLink* lastNode); //Most likely inlined in the final exe,
};

VALIDATE_SIZE(CPtrListSingleLink, 4);
