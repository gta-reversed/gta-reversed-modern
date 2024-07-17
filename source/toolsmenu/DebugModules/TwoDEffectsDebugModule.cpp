#include <StdInc.h>
#include "TwoDEffectsDebugModule.hpp"
#include "CTeleportDebugModule.h"
#include "Lines.h"

namespace I = ImGui;

namespace {
static constexpr const char* s_2DEffectTypeNames[]{
    "LIGHT (0)",         
    "PARTICLE (1)",      
    "MISSING_OR_UNK (2)",
    "ATTRACTOR (3)",     
    "SUN_GLARE (4)",     
    "INTERIOR (5)",      
    "ENEX (6)",          
    "ROADSIGN (7)",      
    "TRIGGER_POINT (8)", 
    "COVER_POINT (9)",   
    "ESCALATOR (10)",     
};


static constexpr const char* s_PedAttractorTypeNames[]{
    "ATM (0)",
    "SEAT (1)",
    "STOP (2)",
    "PIZZA (3)",
    "SHELTER (4)",
    "TRIGGER_SCRIPT (5)",
    "LOOK_AT (6)",
    "SCRIPTED (7)",
    "PARK (8)",
    "STEP (9)",
};

static constexpr CRGBA s_ColorBy2DEffectType[]{
    0x8b4513ff, // LIGHT - saddlebrown
    0x006400ff, // PARTICLE - darkgreen
    0x000080ff, // MISSING_OR_UNK - navy
    0xff0000ff, // ATTRACTOR - red
    0xffd700ff, // SUN_GLARE - gold
    0x7cfc00ff, // INTERIOR - lawngreen
    0x00ffffff, // ENEX - aqua
    0xff00ffff, // ROADSIGN - fuchsia
    0x6495edff, // TRIGGER_POINT - cornflower
    0xff69b4ff, // COVER_POINT - hotpink
    0xffe4c4ff, // ESCALATOR - bisque
};

static constexpr CRGBA s_ColorForAttractorDirections[]{
    0x00FF00FF, // Queue dir - fuchsia
    0x00ffffff, // Use dir - aqua
    0xff69b4ff, // Forward dir - hotpink
};
enum {
    AQUEUE_DIR,
    AUSE_DIR,
    AFWD_DIR,
};

}; // namespace

namespace notsa { 
namespace debugmodules {
void TwoDEffectsDebugModule::RenderWindow() {
    const ::notsa::ui::ScopedWindow window{ "2D Effects", {700.f, 500.f}, m_IsOpen };
    if (!m_IsOpen) {
        return;
    }
    if (I::BeginChild("Settings", { 0.f, 100.f }, ImGuiChildFlags_Border)) {
        I::Checkbox("Bounding Boxes for all", &m_AllBBsEnabled);
        I::DragFloat("Range", &m_Range, 1.f, 10.f, 500.f, "%.2f");
        I::DragInt("Max Entities", &m_MaxEntities, 1.f, 10, SHRT_MAX); // SHRT_MAX because value is casted to int16 later
    }
    I::EndChild();

    UpdateEntitiesAndEffectsInRange();

    if (I::BeginChild("NearbyEffectsTable", {300.f, 0.f}, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX)) {
        RenderNearbyEffectsTable();
    }
    I::EndChild();

    I::SameLine();

    if (I::BeginChild("EntityDetails", {300.f, 0.f}, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX)) {
        if (m_SelectedFx) {
            RenderSelectedEffectDetails();
        }
    }
    I::EndChild();
}

void TwoDEffectsDebugModule::RenderMenuEntry() {
    notsa::ui::DoNestedMenuIL({ "Extra" }, [&] {
        I::MenuItem("2D Effects", nullptr, &m_IsOpen);
    });
    notsa::ui::DoNestedMenuIL({ "Visualization", "2D Effects"}, [&] {
        I::Checkbox("Bounding Boxes", &m_AllBBsEnabled);
    });
}

void TwoDEffectsDebugModule::Render3D() {
    if (m_AllBBsEnabled) {
        for (const auto& v : m_FxInRange) {
            RenderEffectBB(v);
        }
    } else if (m_SelectedFx) { // Otherwise just draw for the selected one
        RenderEffectBB(*m_SelectedFx);
    }
    if (m_SelectedFx) {
        RenderSelectedEffectDetails3D();
    }
}

void TwoDEffectsDebugModule::UpdateEntitiesAndEffectsInRange() {
    m_EntitiesInRange.clear();
    m_EntitiesInRange.resize((size_t)m_MaxEntities);
    int16 num = 0;
    CWorld::FindObjectsInRange(
        FindPlayerCoors(),
        m_Range,
        false,
        &num,
        (int16)m_MaxEntities,
        m_EntitiesInRange.data(),
        true,
        false,
        false,
        true,
        false
    );
    m_EntitiesInRange.resize((size_t)num);

    m_SelectedFx = std::nullopt;
    m_FxInRange.clear();
    m_FxInRange.reserve(m_EntitiesInRange.size() * 2);
    for (size_t eN = 0; eN < m_EntitiesInRange.size(); eN++) {
        auto* const       e  = m_EntitiesInRange[eN];
        const auto* const mi = e->GetModelInfo();
        for (size_t fxN = 0; fxN < mi->m_n2dfxCount; fxN++) {
            auto* const fx    = mi->Get2dEffect(fxN);
            const auto  fxPos = e->GetMatrix().TransformPoint(fx->m_pos);
            const auto  hash  = ImHashData(&fx, sizeof(&fx), ImHashData(&e, sizeof(&e)));
            const auto& entry = m_FxInRange.emplace_back(
                e,
                fx,
                fxPos,
                CVector::Dist(fxPos, FindPlayerCoors()),
                m_FxInRange.size(),
                hash
            );
            if (hash == m_SelectedFxHash) {
                m_SelectedFx = entry;
            }
        }
    }
    if (!m_SelectedFx) {
        m_SelectedFxHash = 0;
    }
}

void TwoDEffectsDebugModule::RenderNearbyEffectsTable() {
    if (!I::BeginTable(
        "2DEffects",
        5,
        ImGuiTableFlags_Sortable
        | ImGuiTableFlags_Resizable
        | ImGuiTableFlags_Reorderable
        | ImGuiTableFlags_BordersInnerH
        | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_SizingFixedFit
        | ImGuiTableFlags_SortMulti
    )) {
        return;
    }

    I::TableSetupColumn("#", ImGuiTableColumnFlags_NoResize, 20.f);
    I::TableSetupColumn("Color", ImGuiTableColumnFlags_NoResize | ImGuiTableColumnFlags_NoSort, 10.f);
    I::TableSetupColumn("Type", ImGuiTableColumnFlags_NoResize, 120.f);
    I::TableSetupColumn("Distance", ImGuiTableColumnFlags_NoResize, 90.f);
    I::TableSetupColumn("Entity", ImGuiTableColumnFlags_NoResize, 80.f);
    I::TableHeadersRow();

    // Sort data for displaying
    const auto specs = I::TableGetSortSpecs();
    rng::sort(m_FxInRange, [&](const InRange2DFx& a, const InRange2DFx& b) {
        for (auto i = 0; i < specs->SpecsCount; i++) {
            const auto spec = &specs->Specs[i];
            std::partial_ordering o;
            switch (spec->ColumnIndex) {
            case 0: o = a.TblIdx <=> b.TblIdx;             break; // #
            case 1:                                        break; // Color (not sortable)
            case 2: o = a.Fx->m_type <=> b.Fx->m_type;     break; // Type
            case 3: o = a.DistToPlayer <=> b.DistToPlayer; break; // Distance
            case 4: o = a.Entity <=> b.Entity;             break; // Entity
            }
            if (o != 0) {
                return spec->SortDirection == ImGuiSortDirection_Ascending
                    ? o < 0
                    : o > 0;
            }
        }
        return a.TblIdx > b.TblIdx;
    });

    // Render data now
    for (const auto& v : m_FxInRange) {
        I::PushID(v.Hash);
        I::BeginGroup();

        // # + Selector
        if (!I::TableNextColumn()) {
            break;
        }
        I::Text("%u", v.TblIdx);
        I::SameLine();
        if (I::Selectable("##s", m_SelectedFxHash && v.Hash == m_SelectedFxHash, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick)) {
            m_SelectedFx     = v;
            m_SelectedFxHash = v.Hash;
            if (I::IsMouseDoubleClicked(0)) {
                TeleportDebugModule::TeleportTo(v.FxPos, v.Entity->m_nAreaCode);
            }
        }

        // Color (For type)
        I::TableNextColumn();
        I::TableSetBgColor(ImGuiTableBgTarget_CellBg, s_ColorBy2DEffectType[v.Fx->m_type].ToIntABGR());

        // Type
        I::TableNextColumn();
        I::TextUnformatted(s_2DEffectTypeNames[v.Fx->m_type]);

        // Distance
        I::TableNextColumn();
        I::Text("%.3f", v.DistToPlayer);

        // Entity
        I::TableNextColumn();
        I::Text("%p", v.Entity);

        I::EndGroup();
        I::PopID();
    }

    I::EndTable();
}

void TwoDEffectsDebugModule::RenderSelectedEffectDetails() {
    const auto& selFx = *m_SelectedFx;

    I::Text("%-15s %s", "Type:", s_2DEffectTypeNames[selFx.Fx->m_type]);
    I::Text("%-15s %.3f", "Distance:", selFx.DistToPlayer);
    if (auto* const attr = C2dEffect::DynCast<C2dEffectPedAttractor>(selFx.Fx)) {
        I::Text("%-15s %s", "Attractor Type:", s_PedAttractorTypeNames[attr->m_nAttractorType]);
        I::Text("%-15s %s", "Script Name:", attr->m_szScriptName);
        I::Text("%-15s 0x%X", "Flags:", (uint32)attr->m_nFlags);

        const auto RenderTextForDir = [](const char* label, CVector dir, auto dirID) {
            I::PushStyleColor(ImGuiCol_Text, s_ColorForAttractorDirections[dirID].ToIntABGR());
            I::Text("%-15s {%2.f, %2.f, %2.f}", label, dir.x, dir.y, dir.z);
            I::PopStyleColor();
        };
        RenderTextForDir("Queue Dir:", CPedAttractorManager::ComputeEffectQueueDir(attr, selFx.Entity->GetMatrix()), AQUEUE_DIR);
        RenderTextForDir("Use Dir:", CPedAttractorManager::ComputeEffectUseDir(attr, selFx.Entity->GetMatrix()), AUSE_DIR);
        RenderTextForDir("Forward Dir:", CPedAttractorManager::ComputeEffectForwardDir(attr, selFx.Entity->GetMatrix()), AFWD_DIR);

        if (I::Button("Use")) {
            CStreaming::RequestModel(eModelID::MODEL_WFYSEX, STREAMING_PRIORITY_REQUEST);
            CStreaming::LoadAllRequestedModels(true);
            CPopulation::AddPedAtAttractor(
                eModelID::MODEL_WFYSEX,
                attr,
                selFx.FxPos,
                selFx.Entity,
                -1
            );
        }
    }
}

void TwoDEffectsDebugModule::RenderEffectBB(const InRange2DFx& fx) {
    constexpr float RADIUS = 0.25f;
    CBox{
        fx.FxPos - CVector{RADIUS},
        fx.FxPos + CVector{RADIUS},
    }.DrawWireFrame(
        fx.Hash == m_SelectedFxHash
            ? CRGBA{0x0, 0xFF, 0x0, 0xFF}
            : s_ColorBy2DEffectType[fx.Fx->m_type]
    );
}

void TwoDEffectsDebugModule::RenderSelectedEffectDetails3D() {
    const auto& selFx = *m_SelectedFx;

    if (auto* const attr = C2dEffect::DynCast<C2dEffectPedAttractor>(selFx.Fx)) {
        const auto attrPos = CPedAttractorManager::ComputeEffectPos(attr, selFx.Entity->GetMatrix());
        const auto RenderDirectionVector = [&](CVector dir, auto dirID) {
            CLines::RenderLineNoClipping(
                attrPos,
                attrPos + dir * 2.f,
                s_ColorForAttractorDirections[dirID].ToInt(),
                0xFFFFFFFF
            );
        };
        RenderDirectionVector(CPedAttractorManager::ComputeEffectQueueDir(attr, selFx.Entity->GetMatrix()), AQUEUE_DIR);
        RenderDirectionVector(CPedAttractorManager::ComputeEffectUseDir(attr, selFx.Entity->GetMatrix()), AUSE_DIR);
        RenderDirectionVector(CPedAttractorManager::ComputeEffectForwardDir(attr, selFx.Entity->GetMatrix()), AFWD_DIR);
    }
}

}; // namespace debugmodules
}; // namespace notsa
