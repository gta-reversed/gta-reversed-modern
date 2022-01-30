#include "StdInc.h"

#include "EntryExit.h"

bool& CEntryExit::ms_bWarping = *(bool*)0x96A7B8;
CObject*& CEntryExit::ms_pDoor = *(CObject**)0x96A7BC;
CEntryExit*& CEntryExit::ms_spawnPoint = *(CEntryExit**)0x96A7C0;

void CEntryExit::InjectHooks() {
    RH_ScopedClass(CEntryExit);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GenerateAmbientPeds, 0x43E8B0);
    RH_ScopedInstall(GetEntryExitToDisplayNameOf, 0x43E650, { .reversed = false });
    RH_ScopedInstall(GetPositionRelativeToOutsideWorld, 0x43EA00, { .reversed = false });
    RH_ScopedInstall(FindValidTeleportPoint, 0x43EAF0, { .reversed = false });
    RH_ScopedInstall(IsInArea, 0x43E460, { .reversed = false });
    RH_ScopedInstall(TransitionStarted, 0x43FFD0, { .reversed = false });
    RH_ScopedInstall(TransitionFinished, 0x4404A0, { .reversed = false });
    RH_ScopedInstall(RequestObjectsInFrustum, 0x43E690);
    RH_ScopedInstall(RequestAmbientPeds, 0x43E6D0);
    RH_ScopedInstall(WarpGangWithPlayer, 0x43F1F0, { .reversed = false });
    RH_ScopedInstall(ProcessStealableObjects, 0x43E990, { .reversed = false });
}

// 0x43E8B0
void CEntryExit::GenerateAmbientPeds(const CVector& posn) {
    CPopulation::bInPoliceStation = false;
    if (CGame::currArea) {
        if (_stricmp("POLICE1", m_szName) == 0 ||
            _stricmp("POLICE2", m_szName) == 0 ||
            _stricmp("POLICE3", m_szName) == 0 ||
            _stricmp("POLICE4", m_szName) == 0
        ) {
            CPopulation::bInPoliceStation = true;
        }
        auto numPedsToSpawn = m_pLink ? m_pLink->m_nNumberOfPeds : m_nNumberOfPeds;
        CPopulation::NumberOfPedsInUseInterior = numPedsToSpawn;
        CPopulation::PopulateInterior(numPedsToSpawn, posn);
    } else {
        CPopulation::NumberOfPedsInUseInterior = 0;
        float exitAngle = DegreesToRadians(ms_spawnPoint->m_fExitAngle);
        CPopulation::CreateWaitingCoppers(posn, exitAngle);
    }
}

// 0x43E650
CEntryExit* CEntryExit::GetEntryExitToDisplayNameOf() {
    return plugin::CallMethodAndReturn<CEntryExit*, 0x43E650, CEntryExit*>(this);
}

// 0x43EA00
void CEntryExit::GetPositionRelativeToOutsideWorld(CVector& outPos) {
    plugin::CallMethod<0x43EA00, CEntryExit*, CVector&>(this, outPos);
}

// 0x43EAF0
void CEntryExit::FindValidTeleportPoint(CVector* point) {
    plugin::CallMethod<0x43EAF0, CEntryExit*>(this);
}

// 0x43E460
bool CEntryExit::IsInArea(const CVector& position) {
    return plugin::CallMethodAndReturn<bool, 0x43E460, CEntryExit*, const CVector&>(this, position);
}

// 0x43FFD0
bool CEntryExit::TransitionStarted(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x43FFD0, CEntryExit*, CPed*>(this, ped);
}

// 0x4404A0
bool CEntryExit::TransitionFinished(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x4404A0, CEntryExit*, CPed*>(this, ped);
}

// 0x43E6D0
void CEntryExit::RequestAmbientPeds() {
    if (!CGame::CanSeeOutSideFromCurrArea()) {
        CStreaming::RemoveDodgyPedsFromRandomSlots();
        return;
    }

    if (_stricmp("bar1", m_szName) == 0) {
        int32 peds[] = {
            MODEL_BFYRI, MODEL_OFYST, MODEL_WFYST, MODEL_WMYST,
            MODEL_BMYRI, MODEL_BMYST, MODEL_OMOST, MODEL_OMYST,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("strip2", m_szName) == 0) {
        int32 peds[] = {
            MODEL_SBFYSTR, MODEL_SWFYSTR, MODEL_INVALID, MODEL_INVALID,
            MODEL_INVALID, MODEL_INVALID, MODEL_INVALID, MODEL_INVALID,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("LAstrip", m_szName) == 0) {
        int32 peds[] = {
            MODEL_VWFYST1, MODEL_VBFYST2, MODEL_VHFYST3, MODEL_INVALID,
            MODEL_INVALID, MODEL_INVALID, MODEL_INVALID, MODEL_INVALID,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("MAFCAS", m_szName) == 0) {
        int32 peds[] = {
            MODEL_BFORI, MODEL_HFYRI, MODEL_OMYRI, MODEL_WMYRI,
            MODEL_OFYST, MODEL_VHMYELV, MODEL_WMOST, MODEL_BMORI,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }

    if (_stricmp("TRICAS", m_szName) == 0) {
        int32 peds[] = {
            MODEL_BFYRI, MODEL_BMYRI, MODEL_HFORI, MODEL_HMORI,
            MODEL_WMORI, MODEL_WFYRI, MODEL_OMOST, MODEL_VBMYELV,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }
}
// 0x43E690
void CEntryExit::RequestObjectsInFrustum() const {
    CRenderer::RequestObjectsInDirection(ms_spawnPoint->m_vecExitPos, m_fExitAngle, 0);
}

// 0x43F1F0
void CEntryExit::WarpGangWithPlayer(CPed* ped) {
    plugin::CallMethod<0x43F1F0, CEntryExit*, CPed*>(this, ped);
}

// 0x43E990
void CEntryExit::ProcessStealableObjects(CPed* ped) {
    plugin::CallMethod<0x43E990, CEntryExit*, CPed*>(this, ped);
