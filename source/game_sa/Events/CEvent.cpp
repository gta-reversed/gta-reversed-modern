#include "StdInc.h"

void CEvent::InjectHooks()
{
    HookInstall(0x4ABFC0, &CEvent::Constructor);
    HookInstall(0x4AC050, &CEvent::CalcSoundLevelIncrement);
    HookInstall(0x4B2850, &CEvent::GetSoundLevel);
}

void CEventRevived::InjectHooks()
{
    HookInstall(0x4AEC50, &CEventRevived::Constructor);
    HookInstall(0x4AECB0, &CEventRevived::AffectsPed_Reversed);
}

CEvent::CEvent() {
    m_nTimeActive = 0;
    m_bValid = false;
}

CEvent::~CEvent() {
    // nothing here
}

CEvent* CEvent::Constructor()
{
    this->CEvent::CEvent();
    return this;
}

float CEvent::GetSoundLevel(CEntity* entity, CVector& position)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<float, 0x4B2850, CEvent*, CEntity*, CVector&>(this, entity, position);
#else
    if ((entity && entity != GetSourceEntity()) || GetLocalSoundLevel() == 0.0f)
        return 0.0f;

    float level = 1000.0f;
    if (GetEventType() == EVENT_SOUND_QUIET) {
        CVector& sourcePos = static_cast<CEventSoundQuiet*>(this)->m_position;
        level = std::min((position - sourcePos).Magnitude(), 1.0f);
    }
    else if (GetSourceEntity()) {
        CVector& sourcePos = GetSourceEntity()->GetPosition();
        level = std::min((position - sourcePos).Magnitude(), 1.0f);
    }
    return (GetLocalSoundLevel() - (log10f(level * level) * 10.0f)) - (level / 100.0f);
#endif
}

float CEvent::CalcSoundLevelIncrement(float level1, float level2)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<float, 0x4AC050, float, float>(level1, level2);
#else
    if (level2 == 0.0f)
        return 0.0f;
    if (level1 == 0.0f)
        return level2;
    level1 = powf(10.0f, level1 * 0.1f);
    level2 = powf(10.0f, level2 * 0.1f);
    return log10f((level1 + level2) / level1) * 10.0f;
#endif
}

CEventRevived* CEventRevived::Constructor()
{
    this->CEventRevived::CEventRevived();
    return this;
}

bool CEventRevived::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AECB0, CEventRevived*, CPed*>(this, ped);
#else
    return CEventRevived::AffectsPed_Reversed(ped);
#endif
}

bool CEventRevived::AffectsPed_Reversed(CPed* ped)
{
    if (ped->m_nCreatedBy == PED_MISSION)
        return false;
    return !ped->IsAlive();
}

