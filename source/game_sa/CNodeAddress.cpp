#include "StdInc.h"

bool CNodeAddress::operatorEqual(CNodeAddress* rhs)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<bool, 0x420920, CNodeAddress*, CNodeAddress*>(this, rhs);
#else
    return this->m_wAreaId == rhs->m_wAreaId && this->m_wNodeId == rhs->m_wNodeId;
#endif
}