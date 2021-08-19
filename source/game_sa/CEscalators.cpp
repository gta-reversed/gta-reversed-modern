#include "StdInc.h"

CEscalator(&CEscalators::aEscalators)[NUM_ESCALATORS] = *(CEscalator(*)[NUM_ESCALATORS])0xC6E9A8;

void CEscalators::InjectHooks() {
    ReversibleHooks::Install("CEscalators", "Shutdown", 0x717940, &CEscalators::Shutdown);
    ReversibleHooks::Install("CEscalators", "Init", 0x717C50, &CEscalators::Init);
    ReversibleHooks::Install("CEscalators", "AddOne", 0x717C90, &CEscalators::AddOne);
    ReversibleHooks::Install("CEscalators", "Update", 0x718580, &CEscalators::Update);
}

// 0x717940
void CEscalators::Shutdown() {
    for (int32_t i = 0; i < NUM_ESCALATORS; ++i) {
        CEscalator& escalator = aEscalators[i];

        escalator.SwitchOff();
        escalator.m_bExist = 0;
    }
}

// 0x717C50
void CEscalators::Init() {
    Shutdown();

    for (int32_t i = 0; i < NUM_ESCALATORS; ++i) {
        aEscalators[i].SwitchOff();
    }
}

// 0x717C90
void CEscalators::AddOne(CVector const& vecStart, CVector const& vecBottom, CVector const& vecEnd, CVector const& vecTop, bool bMoveDown, CEntity* pEntity) {
    for (int32_t i = 0; i < NUM_ESCALATORS; ++i) {
        CEscalator& escalator = aEscalators[i];

        if (!escalator.m_bExist) {
            escalator.AddThisOne(vecStart, vecBottom, vecEnd, vecTop, bMoveDown, pEntity);
            break;
        }
    }
}

// 0x718580
void CEscalators::Update() {
    if (CReplay::Mode != REPLAY_MODE_1) {
        for (int32_t i = 0; i < NUM_ESCALATORS; ++i) {
            CEscalator& escalator = aEscalators[i];

            if (escalator.m_bExist)
                escalator.Update();
        }
    }
}
