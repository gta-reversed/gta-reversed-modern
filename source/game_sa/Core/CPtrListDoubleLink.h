/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CPtrList.h"
#include "CPtrNodeDoubleLink.h"

class  CPtrListDoubleLink : public CPtrList {
public:
    inline CPtrNodeDoubleLink *GetNode() {
        return reinterpret_cast<CPtrNodeDoubleLink *>(pNode);
    }

    inline ~CPtrListDoubleLink() {
        Flush();
    }

    inline CPtrListDoubleLink() { pNode->pItem = nullptr; }

public:
    static void InjectHooks();

    void Flush();
    CPtrNodeDoubleLink* AddItem(void* item);
    void DeleteItem(void* item);
    void DeleteNode(CPtrNodeDoubleLink* node); //Most likely inlined in the final exe, this code is used in multiple places
};

VALIDATE_SIZE(CPtrListDoubleLink, 4);
