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

    void Flush();
    void AddItem(void* item);
    void DeleteItem(void* item);
};

VALIDATE_SIZE(CPtrListDoubleLink, 4);