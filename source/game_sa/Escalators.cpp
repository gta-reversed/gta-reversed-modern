#include "StdInc.h"

#include "Escalators.h"
#include "Escalator.h"

CEscalator(&CEscalators::aEscalators)[NUM_ESCALATORS] = *(CEscalator(*)[NUM_ESCALATORS])0xC6E9A8;

void CEscalators::InjectHooks() {
    Install("CEscalators", "Init", 0x717C50, &CEscalators::Init);
    Install("CEscalators", "Shutdown", 0x717940, &CEscalators::Shutdown);
    Install("CEscalators", "AddOne", 0x717C90, &CEscalators::AddOne);
    Install("CEscalators", "Update", 0x718580, &CEscalators::Update);
}

// 0x717940
void CEscalators::Shutdown() {
    for (CEscalator& escalator : aEscalators) {
        escalator.SwitchOff();
        escalator.m_bExist = false;
    }
}

// 0x717C50
void CEscalators::Init() {
    Shutdown();

    for (CEscalator& escalator : aEscalators) {
        escalator.SwitchOff();
    }
}

// 0x717C90
void CEscalators::AddOne(const CVector& vecStart, const CVector& vecBottom, const CVector& vecEnd, const CVector& vecTop, bool bMoveDown, CEntity* pEntity) {
    for (CEscalator& escalator : aEscalators) {
        if (!escalator.m_bExist) {
            escalator.AddThisOne(vecStart, vecBottom, vecEnd, vecTop, bMoveDown, pEntity);
            break;
        }
    }
}

// 0x718580
void CEscalators::Update() {
    if (CReplay::Mode != REPLAY_MODE_1) {
        for (CEscalator& escalator : aEscalators) {
            if (escalator.m_bExist)
                escalator.Update();
        }
    }
}
