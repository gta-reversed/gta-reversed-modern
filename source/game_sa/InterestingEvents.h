#pragma once

class CInterestingEvents {
public:
    enum EType {

    };

public:
    static void InjectHooks();

    CInterestingEvents();
    CInterestingEvents* Constructor();

    ~CInterestingEvents();
    CInterestingEvents* Destructor();

    void Add(CInterestingEvents::EType type, CEntity* entity);
    void ScanForNearbyEntities();
    void GetInterestingEvent();
    void InvalidateEvent(const void* interestingEvent);
    void InvalidateNonVisibleEvents();
};

extern CInterestingEvents& g_InterestingEvents;
