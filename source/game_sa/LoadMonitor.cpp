#include "StdInc.h"

CLoadMonitor& g_LoadMonitor = *reinterpret_cast<CLoadMonitor*> (0xB72978);

void CLoadMonitor::InjectHooks() {
//    ReversibleHooks::Install("CLoadMonitor", "Constructor", 0x53CFA0, &CLoadMonitor::Constructor);
//    ReversibleHooks::Install("CLoadMonitor", "Destructor", 0x856430, &CLoadMonitor::Destructor);
//    ReversibleHooks::Install("CLoadMonitor", "BeginFrame", 0x53D030, &CLoadMonitor::BeginFrame);
//    ReversibleHooks::Install("CLoadMonitor", "EndFrame", 0x53D0B0, &CLoadMonitor::EndFrame);
//    ReversibleHooks::Install("CLoadMonitor", "StartTimer", 0x53D050, &CLoadMonitor::StartTimer);
//    ReversibleHooks::Install("CLoadMonitor", "EndTimer", 0x53D070, &CLoadMonitor::EndTimer);
}

// 0x53CFA0
CLoadMonitor::CLoadMonitor() {
    plugin::CallMethod<0x53CFA0, CLoadMonitor*> (this);
}

CLoadMonitor* CLoadMonitor::Constructor() {
    this->CLoadMonitor::CLoadMonitor();
    return this;
}

// 0x856430
CLoadMonitor::~CLoadMonitor() {
    // NOP
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
