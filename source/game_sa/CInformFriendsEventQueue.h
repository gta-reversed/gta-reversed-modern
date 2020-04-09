#pragma once

class CEntity;
class CEvent;

class CInformFriendsEventQueue {
public:
    static bool Add(CEntity* pEntity, CEvent* pEvent);
};