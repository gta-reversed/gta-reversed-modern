/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

template <typename ObjectType, uint32 Capacity> class CStore {
public:
    uint32     m_nCount;
    ObjectType m_aObjects[Capacity];

public:
    CStore() {
        m_nCount = 0;
    }

    ObjectType& GetItemAtIndex(uint32 index) {
        return m_aObjects[index];
    }

    inline ObjectType& AddItem() {
        auto& obj = m_aObjects[m_nCount];
        ++m_nCount;
        return obj;
    }
};
