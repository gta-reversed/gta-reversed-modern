#pragma once
#include "extensions/HeapPtrArray.hpp"

#ifdef USE_OPENAL
// This class has to be heap allocated! (with  new`)
class OALBase {
public:
    // Number of living `OALBase` object instances.
    static inline uint32 livingCount{};

    // To be garbage collected OpenAL objects.
    static inline HeapPtrArray<OALBase> trashCan{};

    uint32 m_refCount;

public:
    // NOTSA: possibly inlined in SA.
    OALBase();

    virtual ~OALBase();
    virtual void Release();

    // NOTSA
    virtual void AddRef();
};
#endif
