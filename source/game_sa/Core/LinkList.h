/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Link.h"

template <typename T> class CLinkList {
public:
    CLink<T>  usedListHead;
    CLink<T>  usedListTail;
    CLink<T>  freeListHead;
    CLink<T>  freeListTail;
    CLink<T>* links;

    void* operator new(unsigned size) {
        return ((void*(__cdecl*)(uint32))0x821195)(size);
    }

    void operator delete(void* object) {
        ((void(__cdecl*)(void*))0x8213AE)(object);
    }

    void Init(int32 count) {
        usedListHead.next = &usedListTail;
        usedListTail.prev = &usedListHead;
        freeListHead.next = &freeListTail;
        freeListTail.prev = &freeListHead;
        links = new CLink<T>[count];
        for (int32 i = count - 1; i >= 0; i--) {
            freeListHead.Insert(&links[i]);
        }
    }

    void Shutdown() {
        delete[] links;
        links = nullptr;
    }

    CLink<T>* Insert(T const& data) {
        CLink<T>* link = freeListHead.next;
        if (link == &freeListTail)
            return nullptr;
        link->data = data;
        link->Remove();
        usedListHead.Insert(link);
        return link;
    }

    CLink<T>* InsertSorted(T const& data) {
        CLink<T>* i = nullptr;
        for (i = usedListHead.next; i != &usedListTail; i = i->next) {
            if (i->data.m_distance >= data.m_distance)
                break;
        }
        CLink<T>* link = freeListHead.next;
        if (link == &freeListTail)
            return nullptr;
        link->data = data;
        link->Remove();
        i->prev->Insert(link);
        return link;
    }

    void Clear() {
        for (CLink<T>* link = usedListHead.next; link != &usedListTail; link = usedListHead.next) {
            Remove(link);
        }
    }

    void Remove(CLink<T>* link) {
        link->Remove();
        freeListHead.Insert(link);
    }

    auto GetTail() { return usedListTail.prev; }
    auto GetHead() { return usedListHead.next; }
};

VALIDATE_SIZE(CLinkList<void*>, 0x34);
