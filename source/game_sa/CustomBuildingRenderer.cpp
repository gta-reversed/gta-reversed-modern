#include "StdInc.h"

#include "CCustomBuildingRenderer.h"

#include "CCustomBuildingDNPipeline.h"
#include "CCustomBuildingPipeline.h"

void CCustomBuildingRenderer::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CCustomBuildingRenderer", "Initialise", 0x5D7EC0, &CCustomBuildingRenderer::Initialise);
    Install("CCustomBuildingRenderer", "Shutdown", 0x5D7EE0, &CCustomBuildingRenderer::Shutdown);
    Install("CCustomBuildingRenderer", "PluginAttach", 0x5D7EF0, &CCustomBuildingRenderer::PluginAttach);
    // Install("CCustomBuildingRenderer", "AtomicSetup", 0x5D7F00, &CCustomBuildingRenderer::AtomicSetup);
    // Install("CCustomBuildingRenderer", "IsCBPCPipelineAttached", 0x5D7F40, &CCustomBuildingRenderer::IsCBPCPipelineAttached);
    // Install("CCustomBuildingRenderer", "UpdateDayNightBalanceParam", 0x5D7F80, &CCustomBuildingRenderer::UpdateDayNightBalanceParam);
    // Install("CCustomBuildingRenderer", "Update", 0x5D8050, &CCustomBuildingRenderer::Update);
}

// 0x5D7EC0
bool CCustomBuildingRenderer::Initialise() {
    auto pipe = CCustomBuildingPipeline::CreatePipe();
    if (pipe)
        return CCustomBuildingDNPipeline::CreatePipe();

    return pipe;
}

// 0x5D7EE0
void CCustomBuildingRenderer::Shutdown() {
    CCustomBuildingPipeline::DestroyPipe();
    CCustomBuildingDNPipeline::DestroyPipe();
}

// 0x5D7EF0
bool CCustomBuildingRenderer::PluginAttach() {
    return CCustomBuildingDNPipeline::ExtraVertColourPluginAttach();
}

// 0x5D7F00
void CCustomBuildingRenderer::AtomicSetup(RpAtomic* atomic) {
    plugin::Call<0x5D7F00, RpAtomic*>(atomic);
}

// 0x5D7F40
bool CCustomBuildingRenderer::IsCBPCPipelineAttached(RpAtomic* atomic) {
    return plugin::CallAndReturn<bool, 0x5D7F40, RpAtomic*>(atomic);
}

// 0x5D7F80
void CCustomBuildingRenderer::UpdateDayNightBalanceParam() {
    plugin::Call<0x5D7F80>();
    /*
    const auto minutes = (float)CClock::GetMinutesToday();

    const auto six_hours = 360.0f;
    if (minutes < six_hours) {
        CCustomBuildingDNPipeline::m_fDNBalanceParam = 1.0f;
        return;
    }

    const auto seven_hours = 420.0f;
    if (minutes < seven_hours) {
        CCustomBuildingDNPipeline::m_fDNBalanceParam = float(seven_hours - minutes) / 60.0f;
        return;
    }

    const auto twenty_hours = 1200.0f;
    if (minutes < twenty_hours) {
        CCustomBuildingDNPipeline::m_fDNBalanceParam = 0.0f;
        return;
    }

    const auto twenty_one_hour = 1260.0f;
    if (minutes >= twenty_one_hour)
        CCustomBuildingDNPipeline::m_fDNBalanceParam = 1.0f;
    else
        CCustomBuildingDNPipeline::m_fDNBalanceParam = 1.0f - float(twenty_one_hour - minutes) / 60.0f;
    */
}

// 0x5D8050
void CCustomBuildingRenderer::Update() {
    plugin::Call<0x5D8050>();

    /*
    void sub_5D6830(int a1) {
        static uint32 dword_C02C14, dword_C02C18 = 0;

        dword_C02C14 = (dword_C02C14 + 1) & 15;
        dword_C02C18 = a1;
    }

    CCustomBuildingRenderer::UpdateDayNightBalanceParam();
    sub_5D6830(0);
    */
}
