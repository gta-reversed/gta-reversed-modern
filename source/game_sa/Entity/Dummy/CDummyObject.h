/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CDummy.h"


class  CDummyObject : public CDummy {
public:
    CDummyObject() : CDummy() {}
    explicit CDummyObject(CObject* pObj);

public:
    static void InjectHooks();

    CObject* CreateObject();
    void UpdateFromObject(CObject* pObject);
};


VALIDATE_SIZE(CDummyObject, 0x38);
