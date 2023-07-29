/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

template <typename T>
class CLink {
public:
    T         data;
    CLink<T>* prev;
    CLink<T>* next;

    void Remove() {
        next->prev = prev;
        prev->next = next;
    }

    void Insert(CLink<T>* link) {
        link->next = next;
        next->prev = link;
        link->prev = this;
        next = link;
    }
};

VALIDATE_SIZE(CLink<void*>, 0xC);
