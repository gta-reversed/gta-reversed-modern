#pragma once

class CEntity;
class CEvent;

class CInformFriendsEventQueue {
public:
    static void InjectHooks();

    CInformFriendsEventQueue();
    CInformFriendsEventQueue* Constructor();

    ~CInformFriendsEventQueue();
    CInformFriendsEventQueue* Destructor();

    static void Init();
    static void Flush();
    static bool Add(CEntity* pEntity, CEvent* pEvent);
    static void Process();
};
