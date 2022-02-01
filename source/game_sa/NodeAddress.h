/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CNodeAddress {
public:
    int16 m_wAreaId{-1};
    int16 m_wNodeId{-1};

    constexpr CNodeAddress() = default;

    bool operator==(CNodeAddress const&) const = default;
    bool operator!=(CNodeAddress const&) const = default;
};

VALIDATE_SIZE(CNodeAddress, 0x4);
