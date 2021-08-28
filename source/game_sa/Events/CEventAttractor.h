#include "CEventEditableResponse.h"

class C2dEffect;
class CEntity;

class CEventAttractor : public CEventEditableResponse
{
public:
    C2dEffect* m_2dEffect;
    CEntity* m_entity;
    bool m_bAvoidLookingAtAttractor;

    static void InjectHooks();

    CEventAttractor(C2dEffect* effect, CEntity* entity, bool bAvoidLookingAtAttractor);
    ~CEventAttractor();
private:
    CEventAttractor* Constructor(C2dEffect* effect, CEntity* entity, bool bAvoidLookingAtAttractor);
public:
    eEventType GetEventType() override { return EVENT_ATTRACTOR; }
    int GetEventPriority() override { return 0; }
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    CEventEditableResponse* CloneEditable_Reversed();
    static bool IsEffectActive(CEntity* entity, C2dEffect const* effect);
};

VALIDATE_SIZE(CEventAttractor, 0x20);

class CEventScriptedAttractor : public CEventAttractor {
public:

    static void InjectHooks();

    CEventScriptedAttractor(C2dEffect* the2dEffect, CEntity* entity, bool bAvoidLookingAtAttractor);
    ~CEventScriptedAttractor() {}
private:
    CEventScriptedAttractor* Constructor(C2dEffect* the2dEffect, CEntity* entity, bool bAvoidLookingAtAttractor);
public:
    eEventType GetEventType() override { return EVENT_SCRIPTED_ATTRACTOR; }
    CEventScriptedAttractor* CloneEditable() override { return new CEventScriptedAttractor(m_2dEffect, m_entity, false); }

};


