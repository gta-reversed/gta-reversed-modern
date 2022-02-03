#pragma once

class CEntity;
class CEvent;

class CInformFriendsEventQueue {
public:
    static void InjectHooks();

    CInformFriendsEventQueue() = default;
    ~CInformFriendsEventQueue() = default;

    static void Init();
    static void Flush();
    static bool Add(CEntity* entity, CEvent* event);
    static void Process();
};
