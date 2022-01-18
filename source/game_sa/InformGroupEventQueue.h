#pragma once

class CEvent;
class CEntity;
class CPedGroup;

class CInformGroupEventQueue {
public:
    static void InjectHooks();

    static void Init();
    static bool Add(CEntity* pEntity, CPedGroup* pPedGroup, CEvent* pEvent);
    static void Flush();
    static void Process();
};
