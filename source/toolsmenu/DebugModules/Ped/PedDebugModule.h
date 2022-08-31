#pragma once

namespace PedDebugModule {
// TODO: move to detail
struct PedInfo {
    CPed* ped{};
    CVector posWorld{};
    CVector posScreen{};
};

class Tasks {
public:
    void ProcessPed(CPed&);

private:
    void ProcessTask(CTask* task);
    void ProcessTaskCategory(const char* label, const auto& tasks);
};

class General {
public:
    void ProcessPed(CPed&);
};

class PerPedDebug {
public:
    void ProcessImGui();
    void ProcessRender();

private:
    void ProcessPed(PedInfo&);
private:
    float  m_collapseToggleDist{20.f};
    float  m_drawDist{ 200.f };
    bool    m_visible{};
    bool    m_autoCollapse{};
    Tasks   m_tasksDebug{};
    General m_generalDebug{};
};

class Module {
public:
    void ProcessImGui();
    void ProcessRender();

private:
    void ProcessPed(CPed&);

private:
    PerPedDebug m_perPedDebug{};
};
};
