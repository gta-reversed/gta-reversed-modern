#include "StdInc.h"

bool CNodeAddress::operatorEqual(CNodeAddress* rhs)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<bool, 0x420920, CNodeAddress*, CNodeAddress*>(this, rhs);
#else
    return this == rhs;
    //return this->m_wAreaId == rhs->m_wAreaId && this->m_wNodeId == rhs->m_wNodeId;
#endif
}

bool CNodeAddress::operator==(CNodeAddress const& rhs) const
{
    return m_wAreaId == rhs.m_wAreaId && m_wNodeId == rhs.m_wNodeId;
}

//420950
bool CNodeAddress::operator!=(CNodeAddress const& rhs) const
{
    return m_wAreaId != rhs.m_wAreaId || m_wNodeId != rhs.m_wNodeId;
}
