#include "StdInc.h"

CEventEditableResponse::CEventEditableResponse() {
    m_bAddToEventGroup = true;
    m_taskId = TASK_NONE;
    field_10 = -1;
}

CEventEditableResponse::~CEventEditableResponse() {
    // nothing here
}

CEvent* CEventEditableResponse::Clone() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CEvent * (__thiscall*)(CEvent*))0x420ED0)(this);
#else
    return CEventEditableResponse::Clone_Reversed();
#endif
}

bool CEventEditableResponse::HasEditableResponse() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CEvent*))0x420EF0)(this);
#else
    return CEventEditableResponse::HasEditableResponse_Reversed();
#endif
}

CEvent* CEventEditableResponse::Clone_Reversed() {
    CEventEditableResponse* pClonedEvent = CloneEditable();
    pClonedEvent->m_taskId = m_taskId;
    pClonedEvent->field_10 = field_10;
    pClonedEvent->m_bAddToEventGroup = m_bAddToEventGroup;
    return pClonedEvent;
}