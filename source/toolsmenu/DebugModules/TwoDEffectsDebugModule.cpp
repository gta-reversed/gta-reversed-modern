#include <StdInc.h>
#include "TwoDEffectsDebugModule.hpp"

namespace G = ImGui;

static constexpr const char* s_2DEffectTypeNames[]{
    "LIGHT",         
    "PARTICLE",      
    "MISSING_OR_UNK",
    "ATTRACTOR",     
    "SUN_GLARE",     
    "INTERIOR",      
    "ENEX",          
    "ROADSIGN",      
    "TRIGGER_POINT", 
    "COVER_POINT",   
    "ESCALATOR",     
};

namespace notsa { 
namespace debugmodules {
void TwoDEffectsDebugModule::RenderWindow() {
    const ::notsa::ui::ScopedWindow window{ "2D Effects", {}, m_IsOpen };
    if (!m_IsOpen) {
        return;
    }
    const auto plyr = FindPlayerPed();

    UpdateEntitiesInRange();

    G::BeginChild("EntitiesTable", { 200.f, 0.f }, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
    RenderNearbyEffectsTable();
    G::EndChild();


}

void TwoDEffectsDebugModule::RenderMenuEntry() {
    notsa::ui::DoNestedMenuIL({ "Extra" }, [&] {
        G::MenuItem("2D Effects", nullptr, &m_IsOpen);
    });
}
void TwoDEffectsDebugModule::UpdateEntitiesInRange() {
    m_EntitiesInRange.clear();
    m_EntitiesInRange.resize(m_MaxEntities);
    int16 num = 0;
    CWorld::FindObjectsInRange(
        FindPlayerCoors(),
        m_MaxEntities,
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

    m_FxInRange.clear();
    m_FxInRange.reserve(m_EntitiesInRange.size() * 2);
    for (size_t eN = 0; eN < m_EntitiesInRange.size(); eN++) {
        const auto* const e  = m_EntitiesInRange[eN];
        const auto* const mi = e->GetModelInfo();
        for (size_t fxN = 0; fxN < mi->m_n2dfxCount; fxN++) {
            m_FxInRange.emplace_back(e, mi->Get2dEffect(fxN));
        }
    }
}

void TwoDEffectsDebugModule::RenderNearbyEffectsTable() {
    if (!G::BeginTable("2DEffects", 4, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_ScrollY)) {
        return;
    }

    m_IsSelectedFxInRange = false;

    G::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed);
    G::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);
    G::TableSetupColumn("Entity", ImGuiTableColumnFlags_WidthFixed);
    G::TableSetupColumn("Distance", ImGuiTableColumnFlags_WidthFixed);
    G::TableHeadersRow();

    for (size_t eN = 0; eN < m_EntitiesInRange.size(); eN++) {
        auto* const e  = m_EntitiesInRange[eN];
        auto* const mi = e->GetModelInfo();

        G::PushID(e);
        for (size_t fxN = 0; fxN < mi->m_n2dfxCount; fxN++) {
            const auto* const fx = mi->Get2dEffect(fxN);

            G::PushID(fxN);
            G::BeginGroup();


            // # + Selector
            G::TableNextColumn();
            char label[32];
            *std::format_to(label, "{}", eN + fxN) = 0;
            const auto isSelected = fx == m_SelectedFx;
            G::Selectable(label, isSelected, ImGuiSelectableFlags_SpanAllColumns);
            m_IsSelectedFxInRange |= isSelected;

            // Type
            G::TableNextColumn();
            G::Text("%s", s_2DEffectTypeNames[fx->m_type]);

            // Entity
            G::TableNextColumn();
            G::Text("%p", e);

            // Distance
            G::TableNextColumn();
            G::Text("%.3f", CVector::Dist(e->GetMatrix().TransformPoint(fx->m_pos), FindPlayerCoors()));

            G::EndGroup();
            G::PopID();
        }
    }
}
}; // namespace debugmodules
}; // namespace notsa
