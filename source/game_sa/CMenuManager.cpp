/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CMenuManager& FrontEndMenuManager = *(CMenuManager*)0xBA6748;

bool& CMenuManager::bInvertMouseX = *(bool*)0xBA6744;
bool& CMenuManager::bInvertMouseY = *(bool*)0xBA6745;

int& CMenuManager::nLastMenuPage = *(int*)0x8CDFF0;

void CMenuManager::InjectHooks()
{
    HookInstall(0x57B440, &CMenuManager::Process);
}

// class functions
CMenuManager::CMenuManager()
{
    ((void(__thiscall*)(CMenuManager*))0x574350)(this);
}

CMenuManager::~CMenuManager()
{
    ((void(__thiscall*)(CMenuManager*))0x579440)(this);
}

void CMenuManager::Process()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CMenuManager*))0x57B440)(this);
#else
    if (m_bMenuActive)
    {
        ProcessStreaming(m_bAllStreamingStuffLoaded);
        UserInput();
        ProcessFileActions();
        D3DResourceSystem::TidyUpD3DIndexBuffers(1);
        D3DResourceSystem::TidyUpD3DTextures(1);
    }
    CheckForMenuClosing();
#endif
}

//573CF0
void CMenuManager::ProcessStreaming(char bImmediately)
{
    ((void(__thiscall*)(CMenuManager*, char))0x573CF0)(this, bImmediately);
}

//57FD70
void CMenuManager::UserInput()
{
    ((void(__thiscall*)(CMenuManager*))0x57FD70)(this);
}

//576B70
void CMenuManager::CheckForMenuClosing()
{
    ((void(__thiscall*)(CMenuManager*))0x576B70)(this);
}

//578D60
void CMenuManager::ProcessFileActions()
{
    ((void(__thiscall*)(CMenuManager*))0x578D60)(this);
}

void CMenuManager::DrawWindow(const CRect& coords, const char* pKey, unsigned char nColour, CRGBA backColor, bool Unused, bool bBackground) {
    ((void(__thiscall*)(CMenuManager*, const CRect&, const char*, unsigned char, CRGBA, bool, bool))0x573EE0)(this, coords, pKey, nColour, backColor, Unused, bBackground);
}

char CMenuManager::SwitchToNewScreen(char page) {
    return ((char(__thiscall*)(CMenuManager*, char))0x573680)(this, page);
}

void CMenuManager::SaveSettings() {
    ((void(__thiscall*)(CMenuManager*))0x57C660)(this);
}

char CMenuManager::InitialiseChangedLanguageSettings(char a2) {
    return ((char(__thiscall*)(CMenuManager*, char))0x573260)(this, a2);
}

void CMenuManager::ScrollRadioStations(char numStations) {
    ((void(__thiscall*)(CMenuManager*, char))0x573A00)(this, numStations);
}

void CMenuManager::ProcessMissionPackNewGame() {
    ((void(__thiscall*)(CMenuManager*))0x57D520)(this);
}

signed int CMenuManager::DoSettingsBeforeStartingAGame() {
    return ((signed int(__thiscall*)(CMenuManager*))0x573330)(this);
}

char CMenuManager::SetDefaultPreferences(eMenuPage page) {
    return ((char(__thiscall*)(CMenuManager*, eMenuPage))0x573AE0)(this, page);
}

char CMenuManager::PrintMap()
{
    return ((char(__thiscall*)(CMenuManager*))0x575130)(this);
}

char CMenuManager::PrintStats()
{
    return ((char(__thiscall*)(CMenuManager*))0x574900)(this);
}

char CMenuManager::PrintBriefs()
{
    return ((char(__thiscall*)(CMenuManager*))0x576320)(this);
}

char CMenuManager::DrawControllerSetupScreen()
{
    return ((char(__thiscall*)(CMenuManager*))0x57F300)(this);
}

bool CMenuManager::CheckMissionPackValidMenu()
{
    return plugin::CallMethodAndReturn<bool, 0x57D720, CMenuManager*>(this);
}
