#include "StdInc.h"

CInterestingEvents& g_InterestingEvents = *(CInterestingEvents*)0xC0B058;

void CInterestingEvents::InjectHooks() {
//    ReversibleHooks::Install("CInterestingEvents", "Constructor", 0x6023A0, &CInterestingEvents::Constructor);
//    ReversibleHooks::Install("CInterestingEvents", "Destructor", 0x856880, &CInterestingEvents::Destructor);
//    ReversibleHooks::Install("CInterestingEvents", "Add", 0x602590, &CInterestingEvents::Add);
//    ReversibleHooks::Install("CInterestingEvents", "ScanForNearbyEntities", 0x605A30, &CInterestingEvents::ScanForNearbyEntities);
//    ReversibleHooks::Install("CInterestingEvents", "GetInterestingEvent", 0x6028A0, &CInterestingEvents::GetInterestingEvent);
//    ReversibleHooks::Install("CInterestingEvents", "InvalidateEvent", 0x602960, &CInterestingEvents::InvalidateEvent);
//    ReversibleHooks::Install("CInterestingEvents", "InvalidateNonVisibleEvents", 0x6029C0, &CInterestingEvents::InvalidateNonVisibleEvents);
}

// 0x6023A0
CInterestingEvents::CInterestingEvents() {
    plugin::CallMethod<0x6023A0, CInterestingEvents*>(this);
}

CInterestingEvents* CInterestingEvents::Constructor() {
    this->CInterestingEvents::CInterestingEvents();
    return this;
}

// 0x856880
CInterestingEvents::~CInterestingEvents() {
    plugin::CallMethod<0x856880, CInterestingEvents*>(this);
}

CInterestingEvents* CInterestingEvents::Destructor() {
    this->CInterestingEvents::~CInterestingEvents();
    return this;
}

// 0x602590
void CInterestingEvents::Add(CInterestingEvents::EType type, CEntity* entity) {
    plugin::CallMethod<0x602590, CInterestingEvents*, CInterestingEvents::EType, CEntity*>(this, type, entity);
}

// 0x605A30
void CInterestingEvents::ScanForNearbyEntities() {
    plugin::CallMethod<0x605A30, CInterestingEvents*>(this);
}

// 0x6028A0
void CInterestingEvents::GetInterestingEvent() {
    plugin::CallMethod<0x6028A0, CInterestingEvents*>(this);
}

// 0x602960
void CInterestingEvents::InvalidateEvent(const void* interestingEvent) {
    plugin::CallMethod<0x602960, CInterestingEvents*, const void*>(this, interestingEvent);
}

// 0x6029C0
void CInterestingEvents::InvalidateNonVisibleEvents() {
    plugin::CallMethod<0x6029C0, CInterestingEvents*>(this);
}
