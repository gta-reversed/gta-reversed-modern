#pragma once

class CPtrListDoubleLink;
class CPtrNodeDoubleLink;
class CRepeatSector;

class CEntryInfoNode {
public:
    CPtrListDoubleLink* m_doubleLinkList;
    CPtrNodeDoubleLink* m_doubleLink;
    CRepeatSector*      m_repeatSector;
    CEntryInfoNode*     m_previous;
    CEntryInfoNode*     m_next;

public:
    static void InjectHooks();

    static void* operator new(unsigned size);
    static void  operator delete(void* ptr, size_t sz);

    void         AddToList(CEntryInfoNode* pNext); // Fully inlined in final game

    // NOTSA
    CEntryInfoNode* GetNext() const { return m_next; }
};

VALIDATE_SIZE(CEntryInfoNode, 0x14);
