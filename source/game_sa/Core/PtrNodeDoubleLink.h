/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPtrNodeDoubleLink {
public:
    void*               m_item;
    CPtrNodeDoubleLink* m_next;
    CPtrNodeDoubleLink* m_prev;

public:
    static void InjectHooks();

    CPtrNodeDoubleLink(void* item) { m_item = item; }

    static void* operator new(unsigned size);
    static void  operator delete(void* ptr, size_t sz);

    void AddToList(class CPtrListDoubleLink* list);
};

VALIDATE_SIZE(CPtrNodeDoubleLink, 0xC);
