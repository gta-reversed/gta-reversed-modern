/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#define INVALID_POOL_SLOT (-1)

/*
    R* terminology      Our terminology
    JustIndex           Index
    Index               Id
    Ref                 Handle/Ref
*/

union tPoolObjectFlags {
    struct {
        uint8 nId : 7;
        bool  bEmpty : 1;
    };

private:
    uint8 nValue;

public:
    void Init() {
        bEmpty = true;
        nId = 0;
    }

    uint8 IntValue() {
        return nValue;
    }
};

VALIDATE_SIZE(tPoolObjectFlags, 1);

template <class A, class B = A> class CPool {
public:
    B*                m_pObjects;
    tPoolObjectFlags* m_byteMap;
    int32             m_nSize;
    int32             m_nFirstFree;
    bool              m_bOwnsAllocations;
    bool              m_bIsLocked; // Seemingly not used anywhere, only toggled on/off

    // Default constructor for statically allocated pools
    CPool() {
        // Remember to call CPool::Init to fill in the fields!
        m_pObjects = nullptr;
        m_byteMap = nullptr;
        m_nSize = 0;
        m_bOwnsAllocations = false;
    }

    // Initializes pool
    CPool(int32 size, const char* name) {
        m_pObjects = static_cast<B*>(operator new(sizeof(B) * size));
        m_byteMap  = new tPoolObjectFlags[size]();
        m_nSize = size;
        m_nFirstFree = -1;
        m_bOwnsAllocations = true;
        for (auto i = 0; i < size; ++i) {
            m_byteMap[i].Init();
        }
    }

    ~CPool() {
        Flush();
    }

    // Initialises a pool with pre-allocated
    // To be called one-time-only for statically allocated pools.
    void Init(int32 size, void* objects, void* infos) {
        // Since we statically allocated the pools we do not deallocate.
        assert(m_pObjects == nullptr);
        m_pObjects = static_cast<B*>(objects);
        m_byteMap  = static_cast<tPoolObjectFlags*>(infos);
        m_nSize = size;
        m_nFirstFree = -1;
        m_bOwnsAllocations = false;
        for (auto i = 0; i < size; ++i) {
            m_byteMap[i].Init();
        }
    }

    // Shutdown pool
    void Flush() {
        if (m_bOwnsAllocations) {
            delete[] m_pObjects;
            delete[] m_byteMap;
        }
        m_pObjects = nullptr;
        m_byteMap = nullptr;
        m_nSize = 0;
        m_nFirstFree = 0;
    }

    // Clears pool
    void Clear() {
        for (auto i = 0; i < m_nSize; i++)
            m_byteMap[i].bEmpty = true;
    }

    auto GetSize() {
        return m_nSize;
    }

    // Returns if specified slot is free
    // 0x404940
    bool IsFreeSlotAtIndex(int32 idx) {
        return m_byteMap[idx].bEmpty;
    }

    // Returns slot index for this object
    int32 GetIndex(A* obj) {
        return reinterpret_cast<B*>(obj) - m_pObjects;
    }

    // Returns pointer to object by slot index
    A* GetAt(int32 index) {
        return !IsFreeSlotAtIndex(index) ? (A*)&m_pObjects[index] : nullptr;
    }

    // Marks slot as free / used (0x404970)
    void SetFreeAt(int32 idx, bool bFree) {
        m_byteMap[idx].bEmpty = bFree;
    }

    // Set new id for slot (0x54F9F0)
    void SetIdAt(int32 idx, uint8 id) {
        m_byteMap[idx].nId = id;
    }

    // Get id for slot (0x552200)
    uint8 GetIdAt(int32 idx) {
        return m_byteMap[idx].nId;
    }

    // Allocates object
    A* New() {
        bool bReachedTop = false;
        do {
            if (++m_nFirstFree >= m_nSize) {
                if (bReachedTop) {
                    m_nFirstFree = -1;
                    return nullptr;
                }
                bReachedTop = true;
                m_nFirstFree = 0;
            }
        } while (!m_byteMap[m_nFirstFree].bEmpty);
        m_byteMap[m_nFirstFree].bEmpty = false;
        ++m_byteMap[m_nFirstFree].nId;
        return &m_pObjects[m_nFirstFree];
    }

    // Allocates object at a specific index from a SCM handle (ref) (0x59F610)
    void CreateAtRef(int32 ref) {
        const auto slot = ref >> 8;
        m_byteMap[slot].bEmpty = false;
        m_byteMap[slot].nId = ref & 0x7F;
        m_nFirstFree = 0;
        while (!m_byteMap[m_nFirstFree].bEmpty)
            ++m_nFirstFree;
    }

    // 0x5A1C00
    A* New(int32 ref) {
        A* result = &m_pObjects[ref >> 8];
        CreateAtRef(ref);
        return result;
    }

    // Deallocates object
    void Delete(A* obj) {
        int32 index = GetIndex(obj);
        m_byteMap[index].bEmpty = true;
        if (index < m_nFirstFree)
            m_nFirstFree = index;
    }

    // Returns SCM handle (ref) for object (0x424160)
    int32 GetRef(A* obj) {
        return (GetIndex(obj) << 8) + m_byteMap[GetIndex(obj)].IntValue();
    }

    // Returns pointer to object by SCM handle (ref)
    A* GetAtRef(int32 ref) {
        int32 slotIndex = ref >> 8;
        return slotIndex >= 0
            && slotIndex < m_nSize
            && m_byteMap[slotIndex].IntValue() == (ref & 0xFF) ? reinterpret_cast<A*>(&m_pObjects[slotIndex]) : nullptr;
    }

    A* GetAtRefNoChecks(int32 ref) {
        int32 slotIndex = ref >> 8;
        return GetAt(slotIndex);
    }

    // 0x54F6B0
    auto GetNoOfUsedSpaces() {
        int32 counter = 0;
        for (auto i = 0; i < m_nSize; ++i) {
            if (!IsFreeSlotAtIndex(i))
                ++counter;
        }
        return counter;
    }

    auto GetNoOfFreeSpaces() {
        return m_nSize - GetNoOfUsedSpaces();
    }

    // 0x54F690
    auto GetObjectSize() {
        return sizeof(B);
    }

    // 0x5A1CD0
    bool IsObjectValid(A *obj) {
        auto slot = GetIndex(obj);
        return slot >= 0 &&
               slot < m_nSize &&
               !IsFreeSlotAtIndex(slot);
    }

    // Helper so we don't write memcpy manually
    void CopyItem(A* dest, A* src) {
        *reinterpret_cast<B*>(dest) = *reinterpret_cast<B*>(src);
    }
};

VALIDATE_SIZE(CPool<int32>, 0x14);
