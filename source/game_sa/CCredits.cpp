#include "StdInc.h"

int& CCredits::m_nCreditsStartTime = *(int*)0xC6E978;
bool& CCredits::m_bCreditsGoing = *(bool*)0xC6E97C;

//NOTSA
float CCredits::m_Position = 0.0f;
float CCredits::m_CurrentOffset = 0.0f;

void CCredits::InjectHooks() {
    ReversibleHooks::Install("CCredits", "Render", 0x53D5B0, &CCredits::Render);
    ReversibleHooks::Install("CCredits", "PrintCreditText", 0x5A8660, &CCredits::PrintCreditText);
    ReversibleHooks::Install("CCredits", "PrintCreditSpace", 0x5A87C0, &CCredits::PrintCreditSpace);
    ReversibleHooks::Install("CCredits", "RenderCredits", 0x5A87F0, &CCredits::RenderCredits);
    ReversibleHooks::Install("CCredits", "Start", 0x7170E0, &CCredits::Start);
    ReversibleHooks::Install("CCredits", "Stop", 0x717100, &CCredits::Stop);
}

// 0x7170E0
void CCredits::Start() {
    m_bCreditsGoing = true;
    m_nCreditsStartTime = CTimer::m_snTimeInMilliseconds;
}

// 0x717100
void CCredits::Stop() {
    m_bCreditsGoing = false;
}

// 0x53D5B0
void CCredits::Render() {
    if (m_bCreditsGoing && !FrontEndMenuManager.m_bMenuActive) {
        RenderCredits();
    }
}

// 0x5A8660
void CCredits::PrintCreditText(float scaleX, float scaleY, const char* text, float& position, float currentOffset, bool highlighted) {
    const float minPosY = 20.0f;
    float pos = position + SCREEN_HEIGHT + minPosY - currentOffset;
    if (pos > minPosY && pos < SCREEN_HEIGHT - minPosY) {
        CFont::SetScale(scaleX, scaleY);
        CFont::SetColor({0, 0, 0, 255});
        CFont::PrintString((SCREEN_WIDTH / 2.0f), pos, text);

        if (highlighted)
            CFont::SetColor({255, 255, 255, 255});
        else
            CFont::SetColor({210, 210, 210, 210});

        CFont::PrintString((SCREEN_WIDTH / 2.0f - 1), pos - 1.0f, text);
    }
    position += scaleY * minPosY;
}

// 0x5A87C0
void CCredits::PrintCreditSpace(float spaceSize, float& position) {
    position = (spaceSize * 25.0f + position);
}

void CCredits::PrintCreditTextHelper(const char* textKey, float scale, bool highlighted) {
    auto text = TheText.Get(textKey);
    CCredits::PrintCreditText(scale, scale, text, CCredits::m_Position, CCredits::m_CurrentOffset, highlighted);
}

// 0x5A87F0
void CCredits::RenderCredits() {
    static constexpr float ScaleBig = 1.1f;
    static constexpr float ScaleSmall = 0.78f;
    static constexpr float magic = 0.0435f;
    static constexpr float magic_092f = 0.92f;

    DefinedState2d();

    m_Position = 0.0f;
    m_CurrentOffset = float(CTimer::m_snTimeInMilliseconds - CCredits::m_nCreditsStartTime) * magic;
    
    CFont::SetBackground(false, false);
    CFont::SetCentreSize(SCREEN_WIDTH * magic_092f);
    CFont::SetOrientation(ALIGN_CENTER);
    CFont::SetProportional(true);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetEdge(0);
    CFont::SetDropColor(CRGBA(0, 0, 255));

    PrintCreditTextHelper("CRED000", ScaleBig, true);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED001", ScaleBig, true);
    PrintCreditTextHelper("CRED002", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED003", ScaleBig, true);
    PrintCreditTextHelper("CRED004", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED005", ScaleBig, true);
    PrintCreditTextHelper("CRED006", ScaleBig, false);
    PrintCreditTextHelper("CRED007", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED008", ScaleBig, true);
    PrintCreditTextHelper("CRED009", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRD009A", ScaleBig, true);
    PrintCreditTextHelper("CRD009B", ScaleBig, false);
    PrintCreditTextHelper("CRD009C", ScaleBig, false);
    PrintCreditTextHelper("CRD009D", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED019", ScaleBig, true);
    PrintCreditTextHelper("CRED020", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED010", ScaleBig, true);
    PrintCreditTextHelper("CRED011", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED012", ScaleBig, true);
    PrintCreditTextHelper("CRED013", ScaleBig, false);
    PrintCreditTextHelper("CRED014", ScaleBig, false);
    PrintCreditTextHelper("CRD014A", ScaleBig, false);
    PrintCreditTextHelper("CRED015", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED016", ScaleBig, true);
    PrintCreditTextHelper("CRD016A", ScaleBig, false);
    PrintCreditTextHelper("CRED017", ScaleBig, false);
    PrintCreditTextHelper("CRED018", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED028", ScaleBig, true);
    PrintCreditTextHelper("CRED029", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED030", ScaleBig, true);
    PrintCreditTextHelper("CRED031", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED032", ScaleBig, true);
    PrintCreditTextHelper("CRED033", ScaleBig, false);
    PrintCreditTextHelper("CRED034", ScaleBig, false);
    PrintCreditTextHelper("CRED035", ScaleBig, false);
    PrintCreditTextHelper("CRED036", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED047", ScaleBig, true);
    PrintCreditTextHelper("CRED048", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED049", ScaleBig, true);
    PrintCreditTextHelper("CRED050", ScaleBig, false);
    PrintCreditTextHelper("CRED051", ScaleBig, false);
    PrintCreditTextHelper("CRED052", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED053", ScaleBig, true);
    PrintCreditTextHelper("CRED054", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED055", ScaleBig, true);
    PrintCreditTextHelper("CRED056", ScaleBig, false);
    PrintCreditTextHelper("CRED057", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED058", ScaleBig, true);
    PrintCreditTextHelper("CRED059", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED060", ScaleBig, true);
    PrintCreditTextHelper("CRED061", ScaleBig, false);
    PrintCreditTextHelper("CRED062", ScaleBig, false);
    PrintCreditTextHelper("CRED063", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED021", ScaleBig, true);
    PrintCreditTextHelper("CRED022", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED023", ScaleBig, true);
    PrintCreditTextHelper("CRED024", ScaleBig, false);
    PrintCreditTextHelper("CRED025", ScaleBig, false);
    PrintCreditTextHelper("CRED026", ScaleBig, false);
    PrintCreditTextHelper("CRED027", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED064", ScaleBig, true);
    PrintCreditTextHelper("CRED065", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED066", ScaleBig, true);
    PrintCreditTextHelper("CRED067", ScaleBig, false);
    PrintCreditTextHelper("CRED068", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED069", ScaleBig, true);
    PrintCreditTextHelper("CRED070", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED071", ScaleBig, true);
    PrintCreditTextHelper("CRED072", ScaleBig, false);
    PrintCreditTextHelper("CRED073", ScaleBig, false);
    PrintCreditTextHelper("CRED074", ScaleBig, false);
    PrintCreditTextHelper("CRED075", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED037", ScaleBig, true);
    PrintCreditTextHelper("CRED038", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED039", ScaleBig, true);
    PrintCreditTextHelper("CRED040", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED041", ScaleBig, true);
    PrintCreditTextHelper("CRED042", ScaleBig, false);
    PrintCreditTextHelper("CRED043", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED044", ScaleBig, true);
    PrintCreditTextHelper("CRED991", ScaleBig, false);
    PrintCreditTextHelper("CRED045", ScaleBig, false);
    PrintCreditTextHelper("CRED046", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED076", ScaleBig, true);
    PrintCreditTextHelper("CRED077", ScaleBig, false);
    PrintCreditTextHelper("CRED078", ScaleBig, false);
    PrintCreditTextHelper("CRED079", ScaleBig, false);
    PrintCreditTextHelper("CRED080", ScaleBig, false);
    PrintCreditTextHelper("CRED081", ScaleBig, false);
    PrintCreditTextHelper("CRED100", ScaleBig, false);
    PrintCreditTextHelper("CRED082", ScaleBig, false);
    PrintCreditTextHelper("CRED083", ScaleBig, false);
    PrintCreditTextHelper("CRED084", ScaleBig, false);
    PrintCreditTextHelper("CRED085", ScaleBig, false);
    PrintCreditTextHelper("CRED086", ScaleBig, false);
    PrintCreditTextHelper("CRED087", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED088", ScaleBig, true);
    PrintCreditTextHelper("CRED089", ScaleBig, false);
    PrintCreditTextHelper("CRED090", ScaleBig, false);
    PrintCreditTextHelper("CRED091", ScaleBig, false);
    PrintCreditTextHelper("CRED092", ScaleBig, false);
    PrintCreditTextHelper("CRED093", ScaleBig, false);
    PrintCreditTextHelper("CRED094", ScaleBig, false);
    PrintCreditTextHelper("CRED095", ScaleBig, false);
    PrintCreditTextHelper("CRED096", ScaleBig, false);
    PrintCreditTextHelper("CRED097", ScaleBig, false);
    PrintCreditTextHelper("CRED098", ScaleBig, false);
    PrintCreditTextHelper("CRED099", ScaleBig, false);
    PrintCreditTextHelper("CRED101", ScaleBig, false);
    PrintCreditTextHelper("CRED102", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED103", ScaleBig, true);
    PrintCreditTextHelper("CRED104", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED105", ScaleBig, true);
    PrintCreditTextHelper("CRED106", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED107", ScaleBig, true);
    PrintCreditTextHelper("CRED108", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED109", ScaleBig, true);
    PrintCreditTextHelper("CRED110", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED111", ScaleBig, true);
    CCredits::m_Position += 25.0f;

    PrintCreditTextHelper("CRED112", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED113", ScaleBig, true);
    PrintCreditTextHelper("CRED114", ScaleBig, false);
    PrintCreditTextHelper("CRED115", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED116", ScaleBig, true);
    PrintCreditTextHelper("CRED117", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED118", ScaleBig, true);
    PrintCreditTextHelper("CRED997", ScaleBig, false);
    PrintCreditTextHelper("CRD118A", ScaleBig, false);
    PrintCreditTextHelper("CRED119", ScaleBig, false);
    PrintCreditTextHelper("CRED120", ScaleBig, false);
    PrintCreditTextHelper("CRED996", ScaleBig, false);
    PrintCreditTextHelper("CRD120A", ScaleBig, false);
    PrintCreditTextHelper("CRED121", ScaleBig, false);
    PrintCreditTextHelper("CRD121A", ScaleBig, false);
    PrintCreditTextHelper("CRED995", ScaleBig, false);
    PrintCreditTextHelper("CRED122", ScaleBig, false);
    PrintCreditTextHelper("CRED994", ScaleBig, false);
    PrintCreditTextHelper("CRED123", ScaleBig, false);
    PrintCreditTextHelper("CRED124", ScaleBig, false);
    PrintCreditTextHelper("CRED125", ScaleBig, false);
    PrintCreditTextHelper("CRED126", ScaleBig, false);
    PrintCreditTextHelper("CRD126A", ScaleBig, false);
    PrintCreditTextHelper("CRD126B", ScaleBig, false);
    PrintCreditTextHelper("CRED127", ScaleBig, false);
    PrintCreditTextHelper("CRED128", ScaleBig, false);
    PrintCreditTextHelper("CRED129", ScaleBig, false);
    PrintCreditTextHelper("CRD129A", ScaleBig, false);
    PrintCreditTextHelper("CRED130", ScaleBig, false);
    PrintCreditTextHelper("CRED131", ScaleBig, false);
    PrintCreditTextHelper("CRED132", ScaleBig, false);
    PrintCreditTextHelper("CRED133", ScaleBig, false);
    PrintCreditTextHelper("CRED134", ScaleBig, false);
    PrintCreditTextHelper("CRED992", ScaleBig, false);
    PrintCreditTextHelper("CRD134A", ScaleBig, false);
    PrintCreditTextHelper("CRED135", ScaleBig, false);
    PrintCreditTextHelper("CRED136", ScaleBig, false);
    PrintCreditTextHelper("CRD136A", ScaleBig, false);
    PrintCreditTextHelper("CRED137", ScaleBig, false);
    PrintCreditTextHelper("CRED138", ScaleBig, false);
    PrintCreditTextHelper("CRD138A", ScaleBig, false);
    PrintCreditTextHelper("CRED139", ScaleBig, false);
    PrintCreditTextHelper("CRED140", ScaleBig, false);
    PrintCreditTextHelper("CRED141", ScaleBig, false);
    PrintCreditTextHelper("CRED993", ScaleBig, false);
    PrintCreditTextHelper("CRED142", ScaleBig, false);
    PrintCreditTextHelper("CRED143", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED144", ScaleBig, true);
    PrintCreditTextHelper("CRED145", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED146", ScaleBig, true);
    PrintCreditTextHelper("CRED147", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED148", ScaleBig, true);
    PrintCreditTextHelper("CRED149", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED150", ScaleBig, true);
    PrintCreditTextHelper("CRED151", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED152", ScaleBig, true);
    PrintCreditTextHelper("CRED153", ScaleBig, false);
    PrintCreditTextHelper("CRD153A", ScaleBig, false);
    PrintCreditTextHelper("CRED154", ScaleBig, false);
    PrintCreditTextHelper("CRD154A", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED155", ScaleBig, true);
    PrintCreditTextHelper("CRED156", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED157", ScaleBig, true);
    PrintCreditTextHelper("CRED158", ScaleBig, false);
    PrintCreditTextHelper("CRED159", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED199", ScaleBig, true);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED200", ScaleBig, true);
    PrintCreditTextHelper("CRED201", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED202", ScaleBig, true);
    PrintCreditTextHelper("CRED203", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED204", ScaleBig, true);
    PrintCreditTextHelper("CRED205", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED206", ScaleBig, true);
    PrintCreditTextHelper("CRED207", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED208", ScaleBig, true);
    PrintCreditTextHelper("CRED209", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED210", ScaleBig, true);
    PrintCreditTextHelper("CRED211", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED212", ScaleBig, true);
    PrintCreditTextHelper("CRED213", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED214", ScaleBig, true);
    PrintCreditTextHelper("CRED215", ScaleBig, false);
    PrintCreditTextHelper("CRED216", ScaleBig, false);
    PrintCreditTextHelper("CRED217", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED218", ScaleBig, true);
    PrintCreditTextHelper("CRED219", ScaleBig, false);
    PrintCreditTextHelper("CRED220", ScaleBig, false);
    PrintCreditTextHelper("CRED221", ScaleBig, false);
    PrintCreditTextHelper("CRED222", ScaleBig, false);
    PrintCreditTextHelper("CRED223", ScaleBig, false);
    PrintCreditTextHelper("CRED224", ScaleBig, false);
    PrintCreditTextHelper("CRED225", ScaleBig, false);
    PrintCreditTextHelper("CRED226", ScaleBig, false);
    PrintCreditTextHelper("CRED227", ScaleBig, false);
    PrintCreditTextHelper("CRED228", ScaleBig, false);
    PrintCreditTextHelper("CRED229", ScaleBig, false);
    PrintCreditTextHelper("CRED230", ScaleBig, false);
    PrintCreditTextHelper("CRED231", ScaleBig, false);
    PrintCreditTextHelper("CRED232", ScaleBig, false);
    PrintCreditTextHelper("CRED233", ScaleBig, false);
    PrintCreditTextHelper("CRED234", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED235", ScaleBig, true);
    PrintCreditTextHelper("CRED236", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED237", ScaleBig, true);
    PrintCreditTextHelper("CRED238", ScaleBig, false);
    PrintCreditTextHelper("CRED239", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED240", ScaleBig, true);
    PrintCreditTextHelper("CRED241", ScaleBig, false);
    PrintCreditTextHelper("CRED242", ScaleBig, false);
    PrintCreditTextHelper("CRED243", ScaleBig, false);
    PrintCreditTextHelper("CRED244", ScaleBig, false);
    PrintCreditTextHelper("CRED245", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED246", ScaleBig, true);
    PrintCreditTextHelper("CRED247", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED248", ScaleBig, true);
    PrintCreditTextHelper("CRED249", ScaleBig, false);
    PrintCreditTextHelper("CRED250", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED251", ScaleBig, true);
    PrintCreditTextHelper("CRED252", ScaleBig, false);
    PrintCreditTextHelper("CRED253", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED254", ScaleBig, true);
    PrintCreditTextHelper("CRED255", ScaleBig, false);
    PrintCreditTextHelper("CRED256", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED257", ScaleBig, true);
    PrintCreditTextHelper("CRED258", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED259", ScaleBig, true);
    PrintCreditTextHelper("CRED260", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED261", ScaleBig, true);
    CCredits::m_Position += 25.0f;

    PrintCreditTextHelper("CRED262", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED263", ScaleBig, true);
    PrintCreditTextHelper("CRED264", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED265", ScaleBig, true);
    PrintCreditTextHelper("CRED266", ScaleBig, false);
    PrintCreditTextHelper("CRED267", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED999", ScaleBig, true);
    CCredits::m_Position += 25.0f;

    PrintCreditTextHelper("CRED998", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED268", ScaleBig, true);
    PrintCreditTextHelper("CRED269", ScaleBig, false);
    PrintCreditTextHelper("CRED270", ScaleBig, false);
    PrintCreditTextHelper("CRED271", ScaleBig, false);
    PrintCreditTextHelper("CRED272", ScaleBig, false);
    PrintCreditTextHelper("CRED273", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED274", ScaleBig, true);
    PrintCreditTextHelper("CRED275", ScaleBig, false);
    PrintCreditTextHelper("CRED276", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED277", ScaleBig, true);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED278", ScaleBig, true);
    PrintCreditTextHelper("CRED279", ScaleSmall, false);
    CCredits::PrintCreditSpace(0.5f, m_Position);

    PrintCreditTextHelper("CRED280", ScaleSmall, false);
    PrintCreditTextHelper("CRED281", ScaleSmall, false);
    PrintCreditTextHelper("CRED282", ScaleSmall, false);
    PrintCreditTextHelper("CRED283", ScaleSmall, false);
    PrintCreditTextHelper("CRED284", ScaleSmall, false);
    PrintCreditTextHelper("CRED285", ScaleSmall, false);
    PrintCreditTextHelper("CRED286", ScaleSmall, false);
    PrintCreditTextHelper("CRED287", ScaleSmall, false);
    PrintCreditTextHelper("CRED288", ScaleSmall, false);
    PrintCreditTextHelper("CRED289", ScaleSmall, false);
    PrintCreditTextHelper("CRED290", ScaleSmall, false);
    PrintCreditTextHelper("CRED291", ScaleSmall, false);
    PrintCreditTextHelper("CRED292", ScaleSmall, false);
    PrintCreditTextHelper("CRED293", ScaleSmall, false);
    PrintCreditTextHelper("CRED294", ScaleSmall, false);
    PrintCreditTextHelper("CRED295", ScaleSmall, false);
    PrintCreditTextHelper("CRED296", ScaleSmall, false);
    PrintCreditTextHelper("CRED297", ScaleSmall, false);
    PrintCreditTextHelper("CRED298", ScaleSmall, false);
    PrintCreditTextHelper("CRED299", ScaleSmall, false);
    PrintCreditTextHelper("CRED300", ScaleSmall, false);
    PrintCreditTextHelper("CRED301", ScaleSmall, false);
    PrintCreditTextHelper("CRED302", ScaleSmall, false);
    PrintCreditTextHelper("CRED303", ScaleSmall, false);
    PrintCreditTextHelper("CRED304", ScaleSmall, false);
    PrintCreditTextHelper("CRED305", ScaleSmall, false);
    PrintCreditTextHelper("CRED306", ScaleSmall, false);
    PrintCreditTextHelper("CRED307", ScaleSmall, false);
    PrintCreditTextHelper("CRED308", ScaleSmall, false);
    PrintCreditTextHelper("CRD308A", ScaleSmall, false);
    PrintCreditTextHelper("CRD308B", ScaleSmall, false);
    PrintCreditTextHelper("CRD308C", ScaleSmall, false);
    PrintCreditTextHelper("CRD308D", ScaleSmall, false);
    PrintCreditTextHelper("CRD308E", ScaleSmall, false);
    PrintCreditTextHelper("CRD308F", ScaleSmall, false);
    PrintCreditTextHelper("CRD308G", ScaleSmall, false);
    PrintCreditTextHelper("CRD308H", ScaleSmall, false);
    PrintCreditTextHelper("CRD308I", ScaleSmall, false);
    PrintCreditTextHelper("CRD308J", ScaleSmall, false);
    PrintCreditTextHelper("CRD308K", ScaleSmall, false);
    PrintCreditTextHelper("CRD308L", ScaleSmall, false);
    CCredits::PrintCreditSpace(0.5f, m_Position);

    PrintCreditTextHelper("CRD308M", ScaleSmall, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);
    CCredits::PrintCreditSpace(0.5f, m_Position);

    PrintCreditTextHelper("CRD308N", ScaleSmall, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED309", ScaleBig, true);
    PrintCreditTextHelper("CRED310", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED311", ScaleBig, true);
    PrintCreditTextHelper("CRED312", ScaleBig, false);
    PrintCreditTextHelper("CRED313", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED314", ScaleBig, true);
    PrintCreditTextHelper("CRED315", ScaleSmall, false);
    PrintCreditTextHelper("CRED316", ScaleSmall, false);
    PrintCreditTextHelper("CRED317", ScaleSmall, false);
    PrintCreditTextHelper("CRED318", ScaleSmall, false);
    PrintCreditTextHelper("CRED319", ScaleSmall, false);
    PrintCreditTextHelper("CRED320", ScaleSmall, false);
    PrintCreditTextHelper("CRED321", ScaleSmall, false);
    PrintCreditTextHelper("CRED322", ScaleSmall, false);
    PrintCreditTextHelper("CRED323", ScaleSmall, false);
    PrintCreditTextHelper("CRED324", ScaleSmall, false);
    PrintCreditTextHelper("CRED325", ScaleSmall, false);
    PrintCreditTextHelper("CRED326", ScaleSmall, false);
    PrintCreditTextHelper("CRED327", ScaleSmall, false);
    PrintCreditTextHelper("CRED328", ScaleSmall, false);
    PrintCreditTextHelper("CRED329", ScaleSmall, false);
    PrintCreditTextHelper("CRED330", ScaleSmall, false);
    PrintCreditTextHelper("CRED331", ScaleSmall, false);
    PrintCreditTextHelper("CRED332", ScaleSmall, false);
    PrintCreditTextHelper("CRED333", ScaleSmall, false);
    PrintCreditTextHelper("CRED334", ScaleSmall, false);
    PrintCreditTextHelper("CRED335", ScaleSmall, false);
    PrintCreditTextHelper("CRED336", ScaleSmall, false);
    PrintCreditTextHelper("CRED337", ScaleSmall, false);
    PrintCreditTextHelper("CRED338", ScaleSmall, false);
    PrintCreditTextHelper("CRED339", ScaleSmall, false);
    PrintCreditTextHelper("CRED340", ScaleSmall, false);
    PrintCreditTextHelper("CRED341", ScaleSmall, false);
    PrintCreditTextHelper("CRED342", ScaleSmall, false);
    PrintCreditTextHelper("CRED343", ScaleSmall, false);
    PrintCreditTextHelper("CRED344", ScaleSmall, false);
    PrintCreditTextHelper("CRED345", ScaleSmall, false);
    PrintCreditTextHelper("CRED346", ScaleSmall, false);
    PrintCreditTextHelper("CRED347", ScaleSmall, false);
    PrintCreditTextHelper("CRED348", ScaleSmall, false);
    PrintCreditTextHelper("CRED349", ScaleSmall, false);
    PrintCreditTextHelper("CRED350", ScaleSmall, false);
    PrintCreditTextHelper("CRED351", ScaleSmall, false);
    PrintCreditTextHelper("CRED352", ScaleSmall, false);
    PrintCreditTextHelper("CRED353", ScaleSmall, false);
    PrintCreditTextHelper("CRED354", ScaleSmall, false);
    PrintCreditTextHelper("CRED355", ScaleSmall, false);
    PrintCreditTextHelper("CRED356", ScaleSmall, false);
    PrintCreditTextHelper("CRED357", ScaleSmall, false);
    PrintCreditTextHelper("CRED358", ScaleSmall, false);
    PrintCreditTextHelper("CRED359", ScaleSmall, false);
    PrintCreditTextHelper("CRED360", ScaleSmall, false);
    PrintCreditTextHelper("CRED361", ScaleSmall, false);
    PrintCreditTextHelper("CRED362", ScaleSmall, false);
    PrintCreditTextHelper("CRED363", ScaleSmall, false);
    PrintCreditTextHelper("CRED364", ScaleSmall, false);
    PrintCreditTextHelper("CRED365", ScaleSmall, false);
    PrintCreditTextHelper("CRED366", ScaleSmall, false);
    PrintCreditTextHelper("CRED367", ScaleSmall, false);
    PrintCreditTextHelper("CRED368", ScaleSmall, false);
    PrintCreditTextHelper("CRED369", ScaleSmall, false);
    PrintCreditTextHelper("CRED370", ScaleSmall, false);
    PrintCreditTextHelper("CRED371", ScaleSmall, false);
    PrintCreditTextHelper("CRED372", ScaleSmall, false);
    PrintCreditTextHelper("CRED373", ScaleSmall, false);
    PrintCreditTextHelper("CRED374", ScaleSmall, false);
    PrintCreditTextHelper("CRED375", ScaleSmall, false);
    PrintCreditTextHelper("CRED376", ScaleSmall, false);
    PrintCreditTextHelper("CRED377", ScaleSmall, false);
    PrintCreditTextHelper("CRED378", ScaleSmall, false);
    PrintCreditTextHelper("CRED379", ScaleSmall, false);
    PrintCreditTextHelper("CRED380", ScaleSmall, false);
    PrintCreditTextHelper("CRED381", ScaleSmall, false);
    PrintCreditTextHelper("CRED382", ScaleSmall, false);
    PrintCreditTextHelper("CRED383", ScaleSmall, false);
    PrintCreditTextHelper("CRED384", ScaleSmall, false);
    PrintCreditTextHelper("CRED385", ScaleSmall, false);
    PrintCreditTextHelper("CRED386", ScaleSmall, false);
    PrintCreditTextHelper("CRED387", ScaleSmall, false);
    PrintCreditTextHelper("CRED388", ScaleSmall, false);
    PrintCreditTextHelper("CRED389", ScaleSmall, false);
    PrintCreditTextHelper("CRED390", ScaleSmall, false);
    PrintCreditTextHelper("CRED391", ScaleSmall, false);
    PrintCreditTextHelper("CRED392", ScaleSmall, false);
    PrintCreditTextHelper("CRED393", ScaleSmall, false);
    PrintCreditTextHelper("CRED394", ScaleSmall, false);
    PrintCreditTextHelper("CRED395", ScaleSmall, false);
    PrintCreditTextHelper("CRED396", ScaleSmall, false);
    PrintCreditTextHelper("CRED397", ScaleSmall, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED398", ScaleBig, true);
    PrintCreditTextHelper("CRED399", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED400", ScaleBig, true);
    PrintCreditTextHelper("CRED401", ScaleBig, false);
    PrintCreditTextHelper("CRED402", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED403", ScaleBig, true);
    PrintCreditTextHelper("CRED404", ScaleBig, false);
    PrintCreditTextHelper("CRED405", ScaleBig, false);
    PrintCreditTextHelper("CRED406", ScaleBig, false);
    PrintCreditTextHelper("CRED407", ScaleBig, false);
    PrintCreditTextHelper("CRED408", ScaleBig, false);
    PrintCreditTextHelper("CRED409", ScaleBig, false);
    CCredits::PrintCreditSpace(0.5f, m_Position);

    PrintCreditTextHelper("CRED410", ScaleBig, true);
    PrintCreditTextHelper("CRED411", ScaleBig, false);
    PrintCreditTextHelper("CRED412", ScaleBig, false);
    PrintCreditTextHelper("CRED413", ScaleBig, false);
    PrintCreditTextHelper("CRED414", ScaleBig, false);
    PrintCreditTextHelper("CRED415", ScaleBig, false);
    PrintCreditTextHelper("CRED416", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED417", ScaleBig, true);
    PrintCreditTextHelper("CRED418", ScaleSmall, false);
    PrintCreditTextHelper("CRED419", ScaleSmall, false);
    PrintCreditTextHelper("CRED420", ScaleSmall, false);
    PrintCreditTextHelper("CRED421", ScaleSmall, false);
    PrintCreditTextHelper("CRED422", ScaleSmall, false);
    PrintCreditTextHelper("CRED423", ScaleSmall, false);
    PrintCreditTextHelper("CRED424", ScaleSmall, false);
    PrintCreditTextHelper("CRED425", ScaleSmall, false);
    PrintCreditTextHelper("CRED426", ScaleSmall, false);
    PrintCreditTextHelper("CRED427", ScaleSmall, false);
    PrintCreditTextHelper("CRED428", ScaleSmall, false);
    PrintCreditTextHelper("CRED429", ScaleSmall, false);
    PrintCreditTextHelper("CRED430", ScaleSmall, false);
    PrintCreditTextHelper("CRED431", ScaleSmall, false);
    PrintCreditTextHelper("CRED432", ScaleSmall, false);
    PrintCreditTextHelper("CRED433", ScaleSmall, false);
    PrintCreditTextHelper("CRED434", ScaleSmall, false);
    PrintCreditTextHelper("CRED435", ScaleSmall, false);
    PrintCreditTextHelper("CRED436", ScaleSmall, false);
    PrintCreditTextHelper("CRED437", ScaleSmall, false);
    PrintCreditTextHelper("CRED438", ScaleSmall, false);
    PrintCreditTextHelper("CRED439", ScaleSmall, false);
    PrintCreditTextHelper("CRED440", ScaleSmall, false);
    PrintCreditTextHelper("CRED441", ScaleSmall, false);
    PrintCreditTextHelper("CRED442", ScaleSmall, false);
    PrintCreditTextHelper("CRED443", ScaleSmall, false);
    PrintCreditTextHelper("CRED444", ScaleSmall, false);
    PrintCreditTextHelper("CRED445", ScaleSmall, false);
    PrintCreditTextHelper("CRED446", ScaleSmall, false);
    PrintCreditTextHelper("CRED447", ScaleSmall, false);
    PrintCreditTextHelper("CRED448", ScaleSmall, false);
    PrintCreditTextHelper("CRED449", ScaleSmall, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED450", ScaleBig, true);
    PrintCreditTextHelper("CRED451", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED452", ScaleBig, true);
    PrintCreditTextHelper("CRED453", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED454", ScaleBig, true);
    PrintCreditTextHelper("CRED455", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRD455A", ScaleBig, true);
    PrintCreditTextHelper("CRD455B", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRD455C", ScaleBig, true);
    PrintCreditTextHelper("CRD455D", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED456", ScaleBig, true);
    PrintCreditTextHelper("CRED457", ScaleSmall, false);
    PrintCreditTextHelper("CRED458", ScaleSmall, false);
    PrintCreditTextHelper("CRED459", ScaleSmall, false);
    PrintCreditTextHelper("CRED460", ScaleSmall, false);
    PrintCreditTextHelper("CRED461", ScaleSmall, false);
    PrintCreditTextHelper("CRED462", ScaleSmall, false);
    PrintCreditTextHelper("CRED463", ScaleSmall, false);
    PrintCreditTextHelper("CRED464", ScaleSmall, false);
    PrintCreditTextHelper("CRED465", ScaleSmall, false);
    PrintCreditTextHelper("CRED466", ScaleSmall, false);
    PrintCreditTextHelper("CRED467", ScaleSmall, false);
    PrintCreditTextHelper("CRED468", ScaleSmall, false);
    PrintCreditTextHelper("CRED469", ScaleSmall, false);
    PrintCreditTextHelper("CRED470", ScaleSmall, false);
    PrintCreditTextHelper("CRED471", ScaleSmall, false);
    PrintCreditTextHelper("CRED472", ScaleSmall, false);
    PrintCreditTextHelper("CRED473", ScaleSmall, false);
    PrintCreditTextHelper("CRED474", ScaleSmall, false);
    PrintCreditTextHelper("CRED475", ScaleSmall, false);
    PrintCreditTextHelper("CRED476", ScaleSmall, false);
    PrintCreditTextHelper("CRED477", ScaleSmall, false);
    PrintCreditTextHelper("CRED478", ScaleSmall, false);
    PrintCreditTextHelper("CRED479", ScaleSmall, false);
    PrintCreditTextHelper("CRED480", ScaleSmall, false);
    PrintCreditTextHelper("CRED481", ScaleSmall, false);
    PrintCreditTextHelper("CRED482", ScaleSmall, false);
    PrintCreditTextHelper("CRED483", ScaleSmall, false);
    PrintCreditTextHelper("CRED484", ScaleSmall, false);
    PrintCreditTextHelper("CRED485", ScaleSmall, false);
    PrintCreditTextHelper("CRED486", ScaleSmall, false);
    PrintCreditTextHelper("CRED487", ScaleSmall, false);
    PrintCreditTextHelper("CRED488", ScaleSmall, false);
    PrintCreditTextHelper("CRED489", ScaleSmall, false);
    PrintCreditTextHelper("CRED490", ScaleSmall, false);
    PrintCreditTextHelper("CRED491", ScaleSmall, false);
    PrintCreditTextHelper("CRED492", ScaleSmall, false);
    PrintCreditTextHelper("CRED493", ScaleSmall, false);
    PrintCreditTextHelper("CRED494", ScaleSmall, false);
    PrintCreditTextHelper("CRED495", ScaleSmall, false);
    PrintCreditTextHelper("CRED496", ScaleSmall, false);
    PrintCreditTextHelper("CRED497", ScaleSmall, false);
    PrintCreditTextHelper("CRED498", ScaleSmall, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED499", ScaleBig, true);
    PrintCreditTextHelper("CRED500", ScaleBig, false);
    PrintCreditTextHelper("CRED501", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED502", ScaleBig, true);
    PrintCreditTextHelper("CRED503", ScaleBig, false);
    PrintCreditTextHelper("CRED504", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED505", ScaleBig, true);
    PrintCreditTextHelper("CRED506", ScaleBig, false);
    PrintCreditTextHelper("CRED507", ScaleBig, false);
    PrintCreditTextHelper("CRED508", ScaleBig, false);
    PrintCreditTextHelper("CRED509", ScaleBig, false);
    PrintCreditTextHelper("CRED510", ScaleBig, false);
    PrintCreditTextHelper("CRED511", ScaleBig, false);
    PrintCreditTextHelper("CRED512", ScaleBig, false);
    PrintCreditTextHelper("CRED515", ScaleBig, false);
    PrintCreditTextHelper("CRED516", ScaleBig, false);
    PrintCreditTextHelper("CRED517", ScaleBig, false);
    PrintCreditTextHelper("CRED518", ScaleBig, false);
    PrintCreditTextHelper("CRED519", ScaleBig, false);
    PrintCreditTextHelper("CRED520", ScaleBig, false);
    PrintCreditTextHelper("CRED521", ScaleBig, false);
    PrintCreditTextHelper("CRED522", ScaleBig, false);
    PrintCreditTextHelper("CRED523", ScaleBig, false);
    PrintCreditTextHelper("CRED524", ScaleBig, false);
    PrintCreditTextHelper("CRED525", ScaleBig, false);
    PrintCreditTextHelper("CRED526", ScaleBig, false);
    PrintCreditTextHelper("CRED527", ScaleBig, false);
    PrintCreditTextHelper("CRED529", ScaleBig, false);
    PrintCreditTextHelper("CRED530", ScaleBig, false);
    PrintCreditTextHelper("CRED531", ScaleBig, false);
    PrintCreditTextHelper("CRED532", ScaleBig, false);
    PrintCreditTextHelper("CRED533", ScaleBig, false);
    PrintCreditTextHelper("CRED534", ScaleBig, false);
    PrintCreditTextHelper("CRED535", ScaleBig, false);
    PrintCreditTextHelper("CRED536", ScaleBig, false);
    PrintCreditTextHelper("CRED537", ScaleBig, false);
    PrintCreditTextHelper("CRED538", ScaleBig, false);
    PrintCreditTextHelper("CRED539", ScaleBig, false);
    PrintCreditTextHelper("CRED540", ScaleBig, false);
    PrintCreditTextHelper("CRED541", ScaleBig, false);
    PrintCreditTextHelper("CRD541A", ScaleBig, false);
    PrintCreditTextHelper("CRD541B", ScaleBig, false);
    PrintCreditTextHelper("CRD541C", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED542", ScaleBig, true);
    PrintCreditTextHelper("CRED543", ScaleBig, false);
    PrintCreditTextHelper("CRED544", ScaleBig, false);
    PrintCreditTextHelper("CRED545", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED600", ScaleBig, true);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED601", ScaleBig, true);
    PrintCreditTextHelper("CRED602", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED603", ScaleBig, true);
    PrintCreditTextHelper("CRED604", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED605", ScaleBig, true);
    PrintCreditTextHelper("CRED606", ScaleBig, false);
    PrintCreditTextHelper("CRED607", ScaleBig, false);
    PrintCreditTextHelper("CRED608", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED609", ScaleBig, true);
    PrintCreditTextHelper("CRED610", ScaleBig, false);
    PrintCreditTextHelper("CRED611", ScaleBig, false);
    PrintCreditTextHelper("CRED612", ScaleBig, false);
    PrintCreditTextHelper("CRED613", ScaleBig, false);
    PrintCreditTextHelper("CRED614", ScaleBig, false);
    PrintCreditTextHelper("CRED615", ScaleBig, false);
    PrintCreditTextHelper("CRED616", ScaleBig, false);
    PrintCreditTextHelper("CRED617", ScaleBig, false);
    PrintCreditTextHelper("CRED618", ScaleBig, false);
    PrintCreditTextHelper("CRED619", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED620", ScaleBig, true);
    PrintCreditTextHelper("CRED621", ScaleBig, false);
    PrintCreditTextHelper("CRED622", ScaleBig, false);
    PrintCreditTextHelper("CRED623", ScaleBig, false);
    PrintCreditTextHelper("CRED624", ScaleBig, false);
    PrintCreditTextHelper("CRED625", ScaleBig, false);
    PrintCreditTextHelper("CRED626", ScaleBig, false);
    PrintCreditTextHelper("CRED627", ScaleBig, false);
    PrintCreditTextHelper("CRED628", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED629", ScaleBig, true);
    PrintCreditTextHelper("CRED630", ScaleBig, false);
    CCredits::PrintCreditSpace(1.5f, m_Position);

    PrintCreditTextHelper("CRED700", ScaleBig, true);
    PrintCreditTextHelper("CRED701", ScaleBig, false);
    PrintCreditTextHelper("CRED702", ScaleBig, false);
    PrintCreditTextHelper("CRED703", ScaleBig, false);
    PrintCreditTextHelper("CRED704", ScaleBig, false);
    PrintCreditTextHelper("CRED705", ScaleBig, false);
    PrintCreditTextHelper("CRED706", ScaleBig, false);
    PrintCreditTextHelper("CRED707", ScaleBig, false);
    PrintCreditTextHelper("CRED708", ScaleBig, false);
    PrintCreditTextHelper("CRED709", ScaleBig, false);
    PrintCreditTextHelper("CRED710", ScaleBig, false);
    PrintCreditTextHelper("CRED711", ScaleBig, false);
    PrintCreditTextHelper("CRED712", ScaleBig, false);
    PrintCreditTextHelper("CRED713", ScaleBig, false);
    PrintCreditTextHelper("CRED714", ScaleBig, false);
    PrintCreditTextHelper("CRED715", ScaleBig, false);
    PrintCreditTextHelper("CRED716", ScaleBig, false);

    CFont::DrawFonts();
    if (TheCamera.m_bWideScreenOn) {
        TheCamera.DrawBordersForWideScreen();
    }

    if (CCredits::m_Position + SCREEN_HEIGHT - CCredits::m_CurrentOffset < -10.0f) {
        CCredits::m_bCreditsGoing = false;
    }
}
