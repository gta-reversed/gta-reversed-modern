#include "StdInc.h"

CLoadMonitor& g_LoadMonitor = *reinterpret_cast<CLoadMonitor*> (0xB72978);

void CLoadMonitor::InjectHooks() {
    RH_ScopedClass(CLoadMonitor);
    RH_ScopedCategoryGlobal();

RH_ScopedInstall(Constructor, 0x53CFA0, { .reversed = false });
RH_ScopedInstall(Destructor, 0x856430, { .reversed = false });
RH_ScopedInstall(BeginFrame, 0x53D030, { .reversed = false });
RH_ScopedInstall(EndFrame, 0x53D0B0, { .reversed = false });
RH_ScopedInstall(StartTimer, 0x53D050, { .reversed = false });
RH_ScopedInstall(EndTimer, 0x53D070, { .reversed = false });
}

// 0x53CFA0
CLoadMonitor::CLoadMonitor() {
    plugin::CallMethod<0x53CFA0, CLoadMonitor*> (this);
}

CLoadMonitor* CLoadMonitor::Constructor() {
    this->CLoadMonitor::CLoadMonitor();
    return this;
}

CLoadMonitor* CLoadMonitor::Destructor() {
    this->CLoadMonitor::~CLoadMonitor();
    return this;
}

// 0x53D030
void CLoadMonitor::BeginFrame() {
    plugin::CallMethod<0x53D030, CLoadMonitor*> (this);
}

// 0x53D0B0
void CLoadMonitor::EndFrame() {
    plugin::CallMethod<0x53D0B0, CLoadMonitor*> (this);
}

// 0x53D050
void CLoadMonitor::StartTimer(uint32 timerIndex) {
    plugin::CallMethod<0x53D050, CLoadMonitor*, uint32> (this, timerIndex);
}

// 0x53D070
void CLoadMonitor::EndTimer(uint32 timerIndex) {
    plugin::CallMethod<0x53D070, CLoadMonitor*, uint32>(this, timerIndex);
}
