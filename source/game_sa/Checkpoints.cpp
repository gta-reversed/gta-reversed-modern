#include "StdInc.h"

#include "Checkpoints.h"
#include "Checkpoint.h"

void CCheckpoints::InjectHooks() {
    RH_ScopedClass(CCheckpoints);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x722880);
    RH_ScopedInstall(Shutdown, 0x7228F0);
    RH_ScopedInstall(Update, 0x7229C0);
    RH_ScopedInstall(Render, 0x726060);
    RH_ScopedInstall(PlaceMarker, 0x722C40);
    RH_ScopedInstall(DeleteCP, 0x722FC0);
    RH_ScopedInstall(SetHeading, 0x722970);
    RH_ScopedInstall(UpdatePos, 0x722900);
}

// 0x722880
void CCheckpoints::Init() {
    rng::for_each(m_aCheckPtArray, &CCheckpoint::Init);
    NumActiveCPts = 0;
}

// 0x7228F0
void CCheckpoints::Shutdown() {
    // NOP
}

// NOTSA
CCheckpoint* CCheckpoints::FindById(uint32 id) {
    for (auto& checkpoint : m_aCheckPtArray) {
        if (checkpoint.m_ID == id) {
            return &checkpoint;
        }
    }
    return nullptr;
}

// 0x722970
void CCheckpoints::SetHeading(uint32 id, float angle) {
    if (auto* checkpoint = FindById(id)) {
        checkpoint->m_Fwd.x = std::cos(DegreesToRadians(angle));
        checkpoint->m_Fwd.y = std::sin(DegreesToRadians(angle));
        checkpoint->m_Fwd.Normalise();
    }
}

// 0x7229C0
void CCheckpoints::Update() {
    rng::for_each(m_aCheckPtArray, &CCheckpoint::Update);
}

// 0x722C40
CCheckpoint* CCheckpoints::PlaceMarker(
    uint32 id,
    notsa::WEnumU16<eCheckpointType> type,
    const CVector& pos,
    const CVector& direction,
    float size,
    CRGBA color, // Originally 4 separate uint8's
    uint16 pulsePeriod,
    float pulseFraction,
    int16 rotateRate
) {
    CCheckpoint* cp{};

    const auto cpDistToPlayer3D = CVector::Dist(pos, FindPlayerCentreOfWorld(0));

    if (cp = FindById(id)) { // 0x722CA1 - re-use existing
        assert(cp->m_IsUsed); // NOTE: OG code checked for this, but `FindById` doesn't

        switch (type) {
        case eCheckpointType::TORUS:
        case eCheckpointType::TORUSROT:
        case eCheckpointType::TORUS_UPDOWN: {
            if (CVector2D::DistSqr(pos, FindPlayerCoors()) <= sq(2.f)) {
                type = type == eCheckpointType::TORUS_UPDOWN
                    ? eCheckpointType::TORUS_DOWN
                    : eCheckpointType::TORUSTHROUGH;
            }
            break;
        }
        }
    } else {
        //> 0x722D7A - Try finding an unused one
        for (auto& v : m_aCheckPtArray) {
            if (v.m_Type == eCheckpointType::NA) {
                cp = &v;
                break;
            }
        }

        //> 0x722DA6 - Find furthest one from player and use that
        if (!cp) {
            for (auto& v : m_aCheckPtArray) {
                if (cpDistToPlayer3D < v.m_DistToCam3D && (!cp || v.m_DistToCam3D > cp->m_DistToCam3D)) { // NOTE/BUG: Not checking if the cp is in use!
                    cp = &v;
                }
            }

            // This is useless, as the `Type` is overwritten below by the initialization code anyways....
            //if (cp) {
            //    cp->m_Type = eCheckpointType::NA; // No fucking clue what this NA type is for
            //}
        }

    }

    if (cp) { // 0x722F07
        cp->m_DistToCam3D   = cpDistToPlayer3D;
        cp->m_Colour        = color;
        cp->m_Size          = size;
        cp->m_RotateRate    = rotateRate;
        cp->m_Pos           = pos;
        cp->m_Fwd           = (direction - pos).Normalized();
        cp->m_ID            = id;
        cp->m_Type          = type;
        cp->m_PulsePeriod   = pulsePeriod;
        cp->m_IsUsed        = true;
        cp->m_PulseFraction = pulseFraction;
    }

    return cp; // May be null
}

// 0x722900
void CCheckpoints::UpdatePos(uint32 id, const CVector& posn) {
    if (const auto cp = FindById(id)) {
        cp->SetPosition(posn);
    }
}

// 0x722FC0
void CCheckpoints::DeleteCP(uint32 id, uint16 type) {
    for (auto& cp : m_aCheckPtArray) {
        if (cp.m_IsUsed && cp.m_ID == id && cp.m_Type == (eCheckpointType)type) {
            cp.MarkAsDeleted();
        }
    }
}

// 0x726060
void CCheckpoints::Render() {
    ZoneScoped;

    for (auto& checkpoint : m_aCheckPtArray) {
        if (checkpoint.m_IsUsed) {
            checkpoint.Render();
        }
    }
    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
}
