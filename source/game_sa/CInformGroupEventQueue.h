#pragma once
class CEvent;
class CEntity;
class CPedGroup;
class CInformGroupEventQueue {
public:
    static bool Add(CEntity* pEntity, CPedGroup* pPedGroup, CEvent* pEvent);
};
