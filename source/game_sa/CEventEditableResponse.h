#pragma once
#include "CEvent.h"

class CEventEditableResponse : public CEvent {
public:
    bool m_bAddToEventGroup;
    bool field_D;
    unsigned short m_taskId;
    short field_10;
    unsigned short field_12;

    CEventEditableResponse();
    ~CEventEditableResponse();

    CEvent* Clone() override;
    bool HasEditableResponse() override;
    virtual CEventEditableResponse* CloneEditable() = 0;

    CEvent* Clone_Reversed();
    bool HasEditableResponse_Reversed() { return true; }
};

VALIDATE_SIZE(CEventEditableResponse, 0x14);