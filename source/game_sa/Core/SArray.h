/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

template <typename T>
struct SArray /* : public std::vector<T> */ {
    /* allocator<_Ty>*/ void *allocator; // MSVC 6.0 STL vector
    /* iterator      */ T *_First;       //
    /* iterator      */ T *_Last;        //
    /* iterator      */ T *_End;         //
private:
    SArray() {}
    SArray(SArray const &) {}
    ~SArray() {}
    void operator=(SArray const &) {}
};

VALIDATE_SIZE(SArray<int>, 0x10);