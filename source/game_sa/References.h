/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Reference.h"

#define MAX_NUM_REFERENCES 3000

class CReferences {
public:
    static CReference (&aRefs)[MAX_NUM_REFERENCES];
    static CReference*(&pEmptyList);

public:
    static void InjectHooks();

    static void   Init();
    static uint32 ListSize(CReference* ref);
    static void   RemoveReferencesToPlayer();
    static void   PruneAllReferencesInWorld();
};
