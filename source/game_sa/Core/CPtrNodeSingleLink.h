/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPtrNodeSingleLink {
public:
    void*               pItem;
    CPtrNodeSingleLink* pNext;

public:
    static void InjectHooks();

    static void* operator new(uint32 size);
    static void  operator delete(void* data);

    inline CPtrNodeSingleLink(void* item) : pItem(item) {}

    void AddToList(class CPtrListSingleLink* list);
};

VALIDATE_SIZE(CPtrNodeSingleLink, 8);
