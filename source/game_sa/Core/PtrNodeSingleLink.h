/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPtrNodeSingleLink {
public:
    void*               m_item;
    CPtrNodeSingleLink* m_next;

public:
    static void InjectHooks();

    static void* operator new(uint32 size);
    static void  operator delete(void* data);

    CPtrNodeSingleLink(void* item) : m_item(item) {}

    void AddToList(class CPtrListSingleLink* list);
};

VALIDATE_SIZE(CPtrNodeSingleLink, 8);
