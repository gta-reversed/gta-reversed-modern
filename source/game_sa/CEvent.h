#pragma once
#include "PluginBase.h"

class CEvent 
{
public:
    unsigned int vmt;

    static void* operator_new();
};

VALIDATE_SIZE(CEvent, 0x4);
