/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CNodeAddress {
public:
    int16 m_wAreaId;
    int16 m_wNodeId;

    CNodeAddress() : m_wAreaId(-1), m_wNodeId(-1) {}

    bool operatorEqual(CNodeAddress* rhs);

    bool operator==(CNodeAddress const& rhs) const;
    bool operator!=(CNodeAddress const& rhs) const;
};

VALIDATE_SIZE(CNodeAddress, 0x4);
