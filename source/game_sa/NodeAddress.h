/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CNodeAddress {
public:
    uint16 m_wAreaId{(uint16)-1u};
    uint16 m_wNodeId{(uint16)-1u};

    constexpr CNodeAddress() = default;
    constexpr CNodeAddress(uint16 areaId, uint16 nodeId) : m_wAreaId(areaId), m_wNodeId(nodeId) {}

    bool operator==(CNodeAddress const&) const = default;
    bool operator!=(CNodeAddress const&) const = default;

    inline bool IsAreaValid() {
        return m_wAreaId != (uint16)-1;
    }
    inline bool IsValid() {
        return m_wAreaId != (uint16)-1 || m_wNodeId != (uint16)-1;
    }
};

VALIDATE_SIZE(CNodeAddress, 0x4);
