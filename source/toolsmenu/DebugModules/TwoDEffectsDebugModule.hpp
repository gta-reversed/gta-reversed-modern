#pragma once

#include "DebugModule.h"

namespace notsa { 
namespace debugmodules {
class TwoDEffectsDebugModule final : public DebugModule {
    struct TwoDFxInRange {
        CEntity*   Entity; //!< The entity this fx belongs to
        C2dEffect* Fx;     //!< The 2D effect
        CVector    Pos;    //!< The world position of the fx (Calculated using the entity's matrix)
        size_t     Idx;    //!< Index in the entity's ModelInfo effect list
    };

public:
    void RenderWindow() override;
    void RenderMenuEntry() override;

    NOTSA_IMPLEMENT_DEBUG_MODULE_SERIALIZATION(TwoDEffectsDebugModule, m_IsOpen);

private:
    void UpdateEntitiesInRange();
    void RenderNearbyEffectsTable();

private:
    bool                                        m_IsOpen{};
    int                                         m_MaxEntities{ 512 };
    float                                       m_Range{ 100.f };
    std::vector<CEntity*>                       m_EntitiesInRange{};
    std::vector<std::pair<CEntity*, C2dEffect>> m_FxInRange{};           //!< All effects of the entitites in range
    C2dEffect*                                  m_SelectedFx{};          //!< The selected fx. Only valid iff `m_IsSelectedFxInRange`!
    bool                                        m_IsSelectedFxInRange{}; //!< If the selected fx is in range
};
}; // namespace debugmodules
}; // namespace notsa
