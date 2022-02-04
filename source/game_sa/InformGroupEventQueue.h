#pragma once

class CEvent;
class CEntity;
class CPedGroup;

class CInformGroupEventQueue {
public:
    static void InjectHooks();

    static void Init();
    static bool Add(CEntity* entity, CPedGroup* pedGroup, CEvent* event);
    static void Flush();
    static void Process();
};
