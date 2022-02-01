#include "StdInc.h"

// 0x420920
bool CNodeAddress::operatorEqual(CNodeAddress* rhs)
{
    return this == rhs;
}

bool CNodeAddress::operator==(CNodeAddress const& rhs) const
{
    return m_wAreaId == rhs.m_wAreaId && m_wNodeId == rhs.m_wNodeId;
}

// 0x420950
bool CNodeAddress::operator!=(CNodeAddress const& rhs) const
{
    return m_wAreaId != rhs.m_wAreaId || m_wNodeId != rhs.m_wNodeId;
}
