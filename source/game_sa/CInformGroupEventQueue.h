#pragma once
class CInformGroupEventQueue {
public:
    static bool Add(CEntity* pEntity, CPedGroup* pPedGroup, CEvent* pEvent);
};