#include "StdInc.h"

#include "MenuManager.h"
#include "MenuManager_Internal.h"

/*!
 * @addr 0x57FD70
 */
void CMenuManager::UserInput() {
    { // NOTSA
    const auto pad = CPad::GetPad();
    if (pad->IsStandardKeyJustPressed('q') || pad->IsStandardKeyJustPressed('Q')) {
        CFont::PrintString(50, 250, "switched");
        ReversibleHooks::SwitchHook("DisplaySlider");
    }
    }

    plugin::CallMethod<0x57FD70, CMenuManager*>(this);
}

/*!
 * @addr 0x57B480
 */
void CMenuManager::ProcessUserInput(bool downPressed, bool upPressed, bool acceptPressed, bool cancelPressed, int8 pressedLR) {
    plugin::CallMethod<0x57B480, CMenuManager*, bool, bool, bool, int8>(this, downPressed, upPressed, acceptPressed, cancelPressed, pressedLR);
}

/*!
 * @addr 0x5773D0
 */
void CMenuManager::AdditionalOptionInput(bool* upPressed, bool* downPressed) {
    plugin::CallMethod<0x5773D0, CMenuManager*, bool*, bool*>(this, upPressed, downPressed);
}

/*!
 * @addr 0x57EF50
 */
void CMenuManager::RedefineScreenUserInput(bool* accept, bool* cancel) {
    plugin::CallMethod<0x57EF50, CMenuManager*, bool*, bool*>(this, accept, cancel);
}

/*!
 * @addr 0x57E4D0
 */
bool CMenuManager::CheckRedefineControlInput() {
    return plugin::CallMethodAndReturn<bool, 0x57E4D0, CMenuManager*>(this);
}

// value: -1 or 1
// 0x573440
void CMenuManager::CheckSliderMovement(int8 value) {
    return plugin::CallMethod<0x573440, CMenuManager*, int8>(this, value);

    tMenuScreen* screen   = &aScreens[m_nCurrentScreen];
    tMenuScreenItem* item = &screen->m_aItems[m_nCurrentScreenItem];

    switch (item->m_nActionType) {
    case MENU_ACTION_BRIGHTNESS:
#ifdef FIX_BUGS
        m_PrefsBrightness += value * (384 / 16); // todo: 
#else
        m_PrefsBrightness += value * 24.19f;
#endif
        m_PrefsBrightness = std::clamp(m_PrefsBrightness, 0, 384);
        break;
    case MENU_ACTION_RADIO_VOL: {
        m_nRadioVolume += 4 * value;
        m_nRadioVolume = std::clamp<int8>(m_nRadioVolume, 0, 64);
        AudioEngine.SetMusicMasterVolume(m_nRadioVolume);
        SaveSettings();
        break;
    }
    case MENU_ACTION_SFX_VOL: {
        m_nSfxVolume += 4 * value;
        m_nSfxVolume = std::clamp<int8>(m_nSfxVolume, 0, 64);
        AudioEngine.SetEffectsMasterVolume(m_nSfxVolume);
        SaveSettings();
        break;
    }
    case MENU_ACTION_DRAW_DIST: {
        constexpr auto step = 7.0f / 128.0f;
        float newDist = value <= 0 ? m_fDrawDistance - step : m_fDrawDistance + step;
        m_fDrawDistance = std::clamp(newDist, 0.925f, 1.8f);

        CRenderer::ms_lodDistScale = m_fDrawDistance;
        SaveSettings();
        break;
    }
    case MENU_ACTION_MOUSE_SENS:
        // todo: [0.00813f; 0.0055f]
        CCamera::m_fMouseAccelHorzntl;
#ifdef FIX_BUGS
        CCamera::m_fMouseAccelVertical = CCamera::m_fMouseAccelHorzntl;
#endif
        SaveSettings();
        break;
    default:
        return;
    }
}

// 0x573840
bool CMenuManager::CheckFrontEndUpInput() {
    return plugin::CallMethodAndReturn<bool, 0x573840, CMenuManager*>(this);
}

// 0x5738B0
bool CMenuManager::CheckFrontEndDownInput() {
    return plugin::CallMethodAndReturn<bool, 0x5738B0, CMenuManager*>(this);
}

// 0x573920
bool CMenuManager::CheckFrontEndLeftInput() {
    return plugin::CallMethodAndReturn<bool, 0x573920, CMenuManager*>(this);
}

// 0x573990
bool CMenuManager::CheckFrontEndRightInput() {
    return plugin::CallMethodAndReturn<bool, 0x573990, CMenuManager*>(this);
}

// 0x576B70
bool CMenuManager::CheckForMenuClosing() {
    return plugin::CallMethodAndReturn<bool, 0x576B70, CMenuManager*>(this);
}

// 0x57C4F0
bool CMenuManager::CheckHover(int32 left, int32 right, int32 top, int32 bottom) const {
    // CSprite2d::DrawRect(CRect(left, top, right, bottom), CRGBA(255, 0, 0, 255));
    return (
        m_nMousePosX > left  &&
        m_nMousePosX < right &&
        m_nMousePosY > top   &&
        m_nMousePosY < bottom
    );
}

// 0x57D720
bool CMenuManager::CheckMissionPackValidMenu() {
    return plugin::CallMethodAndReturn<bool, 0x57D720, CMenuManager*>(this);
}

// 0x57DB20
bool CMenuManager::CheckCodesForControls(int32 a1) {
    return plugin::CallMethodAndReturn<bool, 0x57DB20, CMenuManager*>(this, a1);
}
