/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CPtrList.h"
#include "CPtrNodeSingleLink.h"

class  CPtrListSingleLink : public CPtrList {
public:
    inline CPtrNodeSingleLink *GetNode() {
        return reinterpret_cast<CPtrNodeSingleLink *>(pNode);
    }

    inline ~CPtrListSingleLink() {
        Flush();
    }

    void Flush();
    void AddItem(void* item);
    void DeleteItem(void* item);
};

VALIDATE_SIZE(CPtrListSingleLink, 4);