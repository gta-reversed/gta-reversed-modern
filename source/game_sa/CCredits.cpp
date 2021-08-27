#include "StdInc.h"

#include "CCredits.h"

uint32_t& CCredits::CreditsStartTime = *(uint32_t*)0xC6E978;
bool& CCredits::bCreditsGoing = *(bool*)0xC6E97C;

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
    bCreditsGoing = true;
    CreditsStartTime = CTimer::GetTimeInMilliseconds();
}

// 0x717100
void CCredits::Stop() {
    bCreditsGoing = false;
}

// 0x53D5B0
void CCredits::Render() {
    if (bCreditsGoing && !FrontEndMenuManager.m_bMenuActive) {
        RenderCredits();
    }
}

// 0x5A8660
void CCredits::PrintCreditText(float scaleX, float scaleY, const char* text, uint32_t& position, float currentOffset, bool highlighted) {
    const uint32_t minPosY = 20;
    const float    pos = position + SCREEN_HEIGHT + minPosY - currentOffset;

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

    position += (uint32_t)scaleY * minPosY;
}

// 0x5A87C0
void CCredits::PrintCreditSpace(float spaceSize, uint32_t& position) {
    position += (uint32_t)(spaceSize * 25.0f);
}

// 0x5A87F0
void CCredits::RenderCredits() {
    constexpr float SPACE_SMALL  = 0.5f;
    constexpr float SPACE_NORMAL = 1.0f;
    constexpr float SPACE_BIG    = 1.5f;

    constexpr float SCALE_SMALL = 0.78f;
    constexpr float SCALE_BIG = 1.1f;

    DefinedState2d();

    uint32_t lineOffset = 0;
    float    scrollOffset = float(CTimer::GetTimeInMilliseconds() - CreditsStartTime) * 0.0435f;
    
    CFont::SetBackground(false, false);
    CFont::SetCentreSize(SCREEN_WIDTH * 0.92f);
    CFont::SetOrientation(ALIGN_CENTER);
    CFont::SetProportional(true);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetEdge(0);
    CFont::SetDropColor(CRGBA(0, 0, 255));

    const auto PrintCreditText_ = [&](const char* textKey, float scale, bool highlighted) {
        auto text = TheText.Get(textKey);
        PrintCreditText(scale, scale, text, lineOffset, scrollOffset, highlighted);
    };

    PrintCreditText_("CRED000", SCALE_BIG, true);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED001", SCALE_BIG, true);
    PrintCreditText_("CRED002", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED003", SCALE_BIG, true);
    PrintCreditText_("CRED004", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED005", SCALE_BIG, true);
    PrintCreditText_("CRED006", SCALE_BIG, false);
    PrintCreditText_("CRED007", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED008", SCALE_BIG, true);
    PrintCreditText_("CRED009", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRD009A", SCALE_BIG, true);
    PrintCreditText_("CRD009B", SCALE_BIG, false);
    PrintCreditText_("CRD009C", SCALE_BIG, false);
    PrintCreditText_("CRD009D", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED019", SCALE_BIG, true);
    PrintCreditText_("CRED020", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED010", SCALE_BIG, true);
    PrintCreditText_("CRED011", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED012", SCALE_BIG, true);
    PrintCreditText_("CRED013", SCALE_BIG, false);
    PrintCreditText_("CRED014", SCALE_BIG, false);
    PrintCreditText_("CRD014A", SCALE_BIG, false);
    PrintCreditText_("CRED015", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED016", SCALE_BIG, true);
    PrintCreditText_("CRD016A", SCALE_BIG, false);
    PrintCreditText_("CRED017", SCALE_BIG, false);
    PrintCreditText_("CRED018", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED028", SCALE_BIG, true);
    PrintCreditText_("CRED029", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED030", SCALE_BIG, true);
    PrintCreditText_("CRED031", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED032", SCALE_BIG, true);
    PrintCreditText_("CRED033", SCALE_BIG, false);
    PrintCreditText_("CRED034", SCALE_BIG, false);
    PrintCreditText_("CRED035", SCALE_BIG, false);
    PrintCreditText_("CRED036", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED047", SCALE_BIG, true);
    PrintCreditText_("CRED048", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED049", SCALE_BIG, true);
    PrintCreditText_("CRED050", SCALE_BIG, false);
    PrintCreditText_("CRED051", SCALE_BIG, false);
    PrintCreditText_("CRED052", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED053", SCALE_BIG, true);
    PrintCreditText_("CRED054", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED055", SCALE_BIG, true);
    PrintCreditText_("CRED056", SCALE_BIG, false);
    PrintCreditText_("CRED057", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED058", SCALE_BIG, true);
    PrintCreditText_("CRED059", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED060", SCALE_BIG, true);
    PrintCreditText_("CRED061", SCALE_BIG, false);
    PrintCreditText_("CRED062", SCALE_BIG, false);
    PrintCreditText_("CRED063", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED021", SCALE_BIG, true);
    PrintCreditText_("CRED022", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED023", SCALE_BIG, true);
    PrintCreditText_("CRED024", SCALE_BIG, false);
    PrintCreditText_("CRED025", SCALE_BIG, false);
    PrintCreditText_("CRED026", SCALE_BIG, false);
    PrintCreditText_("CRED027", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED064", SCALE_BIG, true);
    PrintCreditText_("CRED065", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED066", SCALE_BIG, true);
    PrintCreditText_("CRED067", SCALE_BIG, false);
    PrintCreditText_("CRED068", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED069", SCALE_BIG, true);
    PrintCreditText_("CRED070", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED071", SCALE_BIG, true);
    PrintCreditText_("CRED072", SCALE_BIG, false);
    PrintCreditText_("CRED073", SCALE_BIG, false);
    PrintCreditText_("CRED074", SCALE_BIG, false);
    PrintCreditText_("CRED075", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED037", SCALE_BIG, true);
    PrintCreditText_("CRED038", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED039", SCALE_BIG, true);
    PrintCreditText_("CRED040", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED041", SCALE_BIG, true);
    PrintCreditText_("CRED042", SCALE_BIG, false);
    PrintCreditText_("CRED043", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED044", SCALE_BIG, true);
    PrintCreditText_("CRED991", SCALE_BIG, false);
    PrintCreditText_("CRED045", SCALE_BIG, false);
    PrintCreditText_("CRED046", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED076", SCALE_BIG, true);
    PrintCreditText_("CRED077", SCALE_BIG, false);
    PrintCreditText_("CRED078", SCALE_BIG, false);
    PrintCreditText_("CRED079", SCALE_BIG, false);
    PrintCreditText_("CRED080", SCALE_BIG, false);
    PrintCreditText_("CRED081", SCALE_BIG, false);
    PrintCreditText_("CRED100", SCALE_BIG, false);
    PrintCreditText_("CRED082", SCALE_BIG, false);
    PrintCreditText_("CRED083", SCALE_BIG, false);
    PrintCreditText_("CRED084", SCALE_BIG, false);
    PrintCreditText_("CRED085", SCALE_BIG, false);
    PrintCreditText_("CRED086", SCALE_BIG, false);
    PrintCreditText_("CRED087", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED088", SCALE_BIG, true);
    PrintCreditText_("CRED089", SCALE_BIG, false);
    PrintCreditText_("CRED090", SCALE_BIG, false);
    PrintCreditText_("CRED091", SCALE_BIG, false);
    PrintCreditText_("CRED092", SCALE_BIG, false);
    PrintCreditText_("CRED093", SCALE_BIG, false);
    PrintCreditText_("CRED094", SCALE_BIG, false);
    PrintCreditText_("CRED095", SCALE_BIG, false);
    PrintCreditText_("CRED096", SCALE_BIG, false);
    PrintCreditText_("CRED097", SCALE_BIG, false);
    PrintCreditText_("CRED098", SCALE_BIG, false);
    PrintCreditText_("CRED099", SCALE_BIG, false);
    PrintCreditText_("CRED101", SCALE_BIG, false);
    PrintCreditText_("CRED102", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED103", SCALE_BIG, true);
    PrintCreditText_("CRED104", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED105", SCALE_BIG, true);
    PrintCreditText_("CRED106", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED107", SCALE_BIG, true);
    PrintCreditText_("CRED108", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED109", SCALE_BIG, true);
    PrintCreditText_("CRED110", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED111", SCALE_BIG, true);
    PrintCreditSpace(SPACE_NORMAL, lineOffset);

    PrintCreditText_("CRED112", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED113", SCALE_BIG, true);
    PrintCreditText_("CRED114", SCALE_BIG, false);
    PrintCreditText_("CRED115", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED116", SCALE_BIG, true);
    PrintCreditText_("CRED117", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED118", SCALE_BIG, true);
    PrintCreditText_("CRED997", SCALE_BIG, false);
    PrintCreditText_("CRD118A", SCALE_BIG, false);
    PrintCreditText_("CRED119", SCALE_BIG, false);
    PrintCreditText_("CRED120", SCALE_BIG, false);
    PrintCreditText_("CRED996", SCALE_BIG, false);
    PrintCreditText_("CRD120A", SCALE_BIG, false);
    PrintCreditText_("CRED121", SCALE_BIG, false);
    PrintCreditText_("CRD121A", SCALE_BIG, false);
    PrintCreditText_("CRED995", SCALE_BIG, false);
    PrintCreditText_("CRED122", SCALE_BIG, false);
    PrintCreditText_("CRED994", SCALE_BIG, false);
    PrintCreditText_("CRED123", SCALE_BIG, false);
    PrintCreditText_("CRED124", SCALE_BIG, false);
    PrintCreditText_("CRED125", SCALE_BIG, false);
    PrintCreditText_("CRED126", SCALE_BIG, false);
    PrintCreditText_("CRD126A", SCALE_BIG, false);
    PrintCreditText_("CRD126B", SCALE_BIG, false);
    PrintCreditText_("CRED127", SCALE_BIG, false);
    PrintCreditText_("CRED128", SCALE_BIG, false);
    PrintCreditText_("CRED129", SCALE_BIG, false);
    PrintCreditText_("CRD129A", SCALE_BIG, false);
    PrintCreditText_("CRED130", SCALE_BIG, false);
    PrintCreditText_("CRED131", SCALE_BIG, false);
    PrintCreditText_("CRED132", SCALE_BIG, false);
    PrintCreditText_("CRED133", SCALE_BIG, false);
    PrintCreditText_("CRED134", SCALE_BIG, false);
    PrintCreditText_("CRED992", SCALE_BIG, false);
    PrintCreditText_("CRD134A", SCALE_BIG, false);
    PrintCreditText_("CRED135", SCALE_BIG, false);
    PrintCreditText_("CRED136", SCALE_BIG, false);
    PrintCreditText_("CRD136A", SCALE_BIG, false);
    PrintCreditText_("CRED137", SCALE_BIG, false);
    PrintCreditText_("CRED138", SCALE_BIG, false);
    PrintCreditText_("CRD138A", SCALE_BIG, false);
    PrintCreditText_("CRED139", SCALE_BIG, false);
    PrintCreditText_("CRED140", SCALE_BIG, false);
    PrintCreditText_("CRED141", SCALE_BIG, false);
    PrintCreditText_("CRED993", SCALE_BIG, false);
    PrintCreditText_("CRED142", SCALE_BIG, false);
    PrintCreditText_("CRED143", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED144", SCALE_BIG, true);
    PrintCreditText_("CRED145", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED146", SCALE_BIG, true);
    PrintCreditText_("CRED147", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED148", SCALE_BIG, true);
    PrintCreditText_("CRED149", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED150", SCALE_BIG, true);
    PrintCreditText_("CRED151", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED152", SCALE_BIG, true);
    PrintCreditText_("CRED153", SCALE_BIG, false);
    PrintCreditText_("CRD153A", SCALE_BIG, false);
    PrintCreditText_("CRED154", SCALE_BIG, false);
    PrintCreditText_("CRD154A", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED155", SCALE_BIG, true);
    PrintCreditText_("CRED156", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED157", SCALE_BIG, true);
    PrintCreditText_("CRED158", SCALE_BIG, false);
    PrintCreditText_("CRED159", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED199", SCALE_BIG, true);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED200", SCALE_BIG, true);
    PrintCreditText_("CRED201", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED202", SCALE_BIG, true);
    PrintCreditText_("CRED203", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED204", SCALE_BIG, true);
    PrintCreditText_("CRED205", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED206", SCALE_BIG, true);
    PrintCreditText_("CRED207", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED208", SCALE_BIG, true);
    PrintCreditText_("CRED209", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED210", SCALE_BIG, true);
    PrintCreditText_("CRED211", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED212", SCALE_BIG, true);
    PrintCreditText_("CRED213", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED214", SCALE_BIG, true);
    PrintCreditText_("CRED215", SCALE_BIG, false);
    PrintCreditText_("CRED216", SCALE_BIG, false);
    PrintCreditText_("CRED217", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED218", SCALE_BIG, true);
    PrintCreditText_("CRED219", SCALE_BIG, false);
    PrintCreditText_("CRED220", SCALE_BIG, false);
    PrintCreditText_("CRED221", SCALE_BIG, false);
    PrintCreditText_("CRED222", SCALE_BIG, false);
    PrintCreditText_("CRED223", SCALE_BIG, false);
    PrintCreditText_("CRED224", SCALE_BIG, false);
    PrintCreditText_("CRED225", SCALE_BIG, false);
    PrintCreditText_("CRED226", SCALE_BIG, false);
    PrintCreditText_("CRED227", SCALE_BIG, false);
    PrintCreditText_("CRED228", SCALE_BIG, false);
    PrintCreditText_("CRED229", SCALE_BIG, false);
    PrintCreditText_("CRED230", SCALE_BIG, false);
    PrintCreditText_("CRED231", SCALE_BIG, false);
    PrintCreditText_("CRED232", SCALE_BIG, false);
    PrintCreditText_("CRED233", SCALE_BIG, false);
    PrintCreditText_("CRED234", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED235", SCALE_BIG, true);
    PrintCreditText_("CRED236", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED237", SCALE_BIG, true);
    PrintCreditText_("CRED238", SCALE_BIG, false);
    PrintCreditText_("CRED239", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED240", SCALE_BIG, true);
    PrintCreditText_("CRED241", SCALE_BIG, false);
    PrintCreditText_("CRED242", SCALE_BIG, false);
    PrintCreditText_("CRED243", SCALE_BIG, false);
    PrintCreditText_("CRED244", SCALE_BIG, false);
    PrintCreditText_("CRED245", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED246", SCALE_BIG, true);
    PrintCreditText_("CRED247", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED248", SCALE_BIG, true);
    PrintCreditText_("CRED249", SCALE_BIG, false);
    PrintCreditText_("CRED250", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED251", SCALE_BIG, true);
    PrintCreditText_("CRED252", SCALE_BIG, false);
    PrintCreditText_("CRED253", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED254", SCALE_BIG, true);
    PrintCreditText_("CRED255", SCALE_BIG, false);
    PrintCreditText_("CRED256", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED257", SCALE_BIG, true);
    PrintCreditText_("CRED258", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED259", SCALE_BIG, true);
    PrintCreditText_("CRED260", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED261", SCALE_BIG, true);
    PrintCreditSpace(SPACE_NORMAL, lineOffset);

    PrintCreditText_("CRED262", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED263", SCALE_BIG, true);
    PrintCreditText_("CRED264", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED265", SCALE_BIG, true);
    PrintCreditText_("CRED266", SCALE_BIG, false);
    PrintCreditText_("CRED267", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED999", SCALE_BIG, true);
    PrintCreditSpace(SPACE_NORMAL, lineOffset);

    PrintCreditText_("CRED998", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED268", SCALE_BIG, true);
    PrintCreditText_("CRED269", SCALE_BIG, false);
    PrintCreditText_("CRED270", SCALE_BIG, false);
    PrintCreditText_("CRED271", SCALE_BIG, false);
    PrintCreditText_("CRED272", SCALE_BIG, false);
    PrintCreditText_("CRED273", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED274", SCALE_BIG, true);
    PrintCreditText_("CRED275", SCALE_BIG, false);
    PrintCreditText_("CRED276", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED277", SCALE_BIG, true);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED278", SCALE_BIG, true);
    PrintCreditText_("CRED279", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_SMALL, lineOffset);

    PrintCreditText_("CRED280", SCALE_SMALL, false);
    PrintCreditText_("CRED281", SCALE_SMALL, false);
    PrintCreditText_("CRED282", SCALE_SMALL, false);
    PrintCreditText_("CRED283", SCALE_SMALL, false);
    PrintCreditText_("CRED284", SCALE_SMALL, false);
    PrintCreditText_("CRED285", SCALE_SMALL, false);
    PrintCreditText_("CRED286", SCALE_SMALL, false);
    PrintCreditText_("CRED287", SCALE_SMALL, false);
    PrintCreditText_("CRED288", SCALE_SMALL, false);
    PrintCreditText_("CRED289", SCALE_SMALL, false);
    PrintCreditText_("CRED290", SCALE_SMALL, false);
    PrintCreditText_("CRED291", SCALE_SMALL, false);
    PrintCreditText_("CRED292", SCALE_SMALL, false);
    PrintCreditText_("CRED293", SCALE_SMALL, false);
    PrintCreditText_("CRED294", SCALE_SMALL, false);
    PrintCreditText_("CRED295", SCALE_SMALL, false);
    PrintCreditText_("CRED296", SCALE_SMALL, false);
    PrintCreditText_("CRED297", SCALE_SMALL, false);
    PrintCreditText_("CRED298", SCALE_SMALL, false);
    PrintCreditText_("CRED299", SCALE_SMALL, false);
    PrintCreditText_("CRED300", SCALE_SMALL, false);
    PrintCreditText_("CRED301", SCALE_SMALL, false);
    PrintCreditText_("CRED302", SCALE_SMALL, false);
    PrintCreditText_("CRED303", SCALE_SMALL, false);
    PrintCreditText_("CRED304", SCALE_SMALL, false);
    PrintCreditText_("CRED305", SCALE_SMALL, false);
    PrintCreditText_("CRED306", SCALE_SMALL, false);
    PrintCreditText_("CRED307", SCALE_SMALL, false);
    PrintCreditText_("CRED308", SCALE_SMALL, false);
    PrintCreditText_("CRD308A", SCALE_SMALL, false);
    PrintCreditText_("CRD308B", SCALE_SMALL, false);
    PrintCreditText_("CRD308C", SCALE_SMALL, false);
    PrintCreditText_("CRD308D", SCALE_SMALL, false);
    PrintCreditText_("CRD308E", SCALE_SMALL, false);
    PrintCreditText_("CRD308F", SCALE_SMALL, false);
    PrintCreditText_("CRD308G", SCALE_SMALL, false);
    PrintCreditText_("CRD308H", SCALE_SMALL, false);
    PrintCreditText_("CRD308I", SCALE_SMALL, false);
    PrintCreditText_("CRD308J", SCALE_SMALL, false);
    PrintCreditText_("CRD308K", SCALE_SMALL, false);
    PrintCreditText_("CRD308L", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_SMALL, lineOffset);

    PrintCreditText_("CRD308M", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);
    PrintCreditSpace(SPACE_SMALL, lineOffset);

    PrintCreditText_("CRD308N", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED309", SCALE_BIG, true);
    PrintCreditText_("CRED310", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED311", SCALE_BIG, true);
    PrintCreditText_("CRED312", SCALE_BIG, false);
    PrintCreditText_("CRED313", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED314", SCALE_BIG, true);
    PrintCreditText_("CRED315", SCALE_SMALL, false);
    PrintCreditText_("CRED316", SCALE_SMALL, false);
    PrintCreditText_("CRED317", SCALE_SMALL, false);
    PrintCreditText_("CRED318", SCALE_SMALL, false);
    PrintCreditText_("CRED319", SCALE_SMALL, false);
    PrintCreditText_("CRED320", SCALE_SMALL, false);
    PrintCreditText_("CRED321", SCALE_SMALL, false);
    PrintCreditText_("CRED322", SCALE_SMALL, false);
    PrintCreditText_("CRED323", SCALE_SMALL, false);
    PrintCreditText_("CRED324", SCALE_SMALL, false);
    PrintCreditText_("CRED325", SCALE_SMALL, false);
    PrintCreditText_("CRED326", SCALE_SMALL, false);
    PrintCreditText_("CRED327", SCALE_SMALL, false);
    PrintCreditText_("CRED328", SCALE_SMALL, false);
    PrintCreditText_("CRED329", SCALE_SMALL, false);
    PrintCreditText_("CRED330", SCALE_SMALL, false);
    PrintCreditText_("CRED331", SCALE_SMALL, false);
    PrintCreditText_("CRED332", SCALE_SMALL, false);
    PrintCreditText_("CRED333", SCALE_SMALL, false);
    PrintCreditText_("CRED334", SCALE_SMALL, false);
    PrintCreditText_("CRED335", SCALE_SMALL, false);
    PrintCreditText_("CRED336", SCALE_SMALL, false);
    PrintCreditText_("CRED337", SCALE_SMALL, false);
    PrintCreditText_("CRED338", SCALE_SMALL, false);
    PrintCreditText_("CRED339", SCALE_SMALL, false);
    PrintCreditText_("CRED340", SCALE_SMALL, false);
    PrintCreditText_("CRED341", SCALE_SMALL, false);
    PrintCreditText_("CRED342", SCALE_SMALL, false);
    PrintCreditText_("CRED343", SCALE_SMALL, false);
    PrintCreditText_("CRED344", SCALE_SMALL, false);
    PrintCreditText_("CRED345", SCALE_SMALL, false);
    PrintCreditText_("CRED346", SCALE_SMALL, false);
    PrintCreditText_("CRED347", SCALE_SMALL, false);
    PrintCreditText_("CRED348", SCALE_SMALL, false);
    PrintCreditText_("CRED349", SCALE_SMALL, false);
    PrintCreditText_("CRED350", SCALE_SMALL, false);
    PrintCreditText_("CRED351", SCALE_SMALL, false);
    PrintCreditText_("CRED352", SCALE_SMALL, false);
    PrintCreditText_("CRED353", SCALE_SMALL, false);
    PrintCreditText_("CRED354", SCALE_SMALL, false);
    PrintCreditText_("CRED355", SCALE_SMALL, false);
    PrintCreditText_("CRED356", SCALE_SMALL, false);
    PrintCreditText_("CRED357", SCALE_SMALL, false);
    PrintCreditText_("CRED358", SCALE_SMALL, false);
    PrintCreditText_("CRED359", SCALE_SMALL, false);
    PrintCreditText_("CRED360", SCALE_SMALL, false);
    PrintCreditText_("CRED361", SCALE_SMALL, false);
    PrintCreditText_("CRED362", SCALE_SMALL, false);
    PrintCreditText_("CRED363", SCALE_SMALL, false);
    PrintCreditText_("CRED364", SCALE_SMALL, false);
    PrintCreditText_("CRED365", SCALE_SMALL, false);
    PrintCreditText_("CRED366", SCALE_SMALL, false);
    PrintCreditText_("CRED367", SCALE_SMALL, false);
    PrintCreditText_("CRED368", SCALE_SMALL, false);
    PrintCreditText_("CRED369", SCALE_SMALL, false);
    PrintCreditText_("CRED370", SCALE_SMALL, false);
    PrintCreditText_("CRED371", SCALE_SMALL, false);
    PrintCreditText_("CRED372", SCALE_SMALL, false);
    PrintCreditText_("CRED373", SCALE_SMALL, false);
    PrintCreditText_("CRED374", SCALE_SMALL, false);
    PrintCreditText_("CRED375", SCALE_SMALL, false);
    PrintCreditText_("CRED376", SCALE_SMALL, false);
    PrintCreditText_("CRED377", SCALE_SMALL, false);
    PrintCreditText_("CRED378", SCALE_SMALL, false);
    PrintCreditText_("CRED379", SCALE_SMALL, false);
    PrintCreditText_("CRED380", SCALE_SMALL, false);
    PrintCreditText_("CRED381", SCALE_SMALL, false);
    PrintCreditText_("CRED382", SCALE_SMALL, false);
    PrintCreditText_("CRED383", SCALE_SMALL, false);
    PrintCreditText_("CRED384", SCALE_SMALL, false);
    PrintCreditText_("CRED385", SCALE_SMALL, false);
    PrintCreditText_("CRED386", SCALE_SMALL, false);
    PrintCreditText_("CRED387", SCALE_SMALL, false);
    PrintCreditText_("CRED388", SCALE_SMALL, false);
    PrintCreditText_("CRED389", SCALE_SMALL, false);
    PrintCreditText_("CRED390", SCALE_SMALL, false);
    PrintCreditText_("CRED391", SCALE_SMALL, false);
    PrintCreditText_("CRED392", SCALE_SMALL, false);
    PrintCreditText_("CRED393", SCALE_SMALL, false);
    PrintCreditText_("CRED394", SCALE_SMALL, false);
    PrintCreditText_("CRED395", SCALE_SMALL, false);
    PrintCreditText_("CRED396", SCALE_SMALL, false);
    PrintCreditText_("CRED397", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED398", SCALE_BIG, true);
    PrintCreditText_("CRED399", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED400", SCALE_BIG, true);
    PrintCreditText_("CRED401", SCALE_BIG, false);
    PrintCreditText_("CRED402", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED403", SCALE_BIG, true);
    PrintCreditText_("CRED404", SCALE_BIG, false);
    PrintCreditText_("CRED405", SCALE_BIG, false);
    PrintCreditText_("CRED406", SCALE_BIG, false);
    PrintCreditText_("CRED407", SCALE_BIG, false);
    PrintCreditText_("CRED408", SCALE_BIG, false);
    PrintCreditText_("CRED409", SCALE_BIG, false);
    PrintCreditSpace(SPACE_SMALL, lineOffset);

    PrintCreditText_("CRED410", SCALE_BIG, true);
    PrintCreditText_("CRED411", SCALE_BIG, false);
    PrintCreditText_("CRED412", SCALE_BIG, false);
    PrintCreditText_("CRED413", SCALE_BIG, false);
    PrintCreditText_("CRED414", SCALE_BIG, false);
    PrintCreditText_("CRED415", SCALE_BIG, false);
    PrintCreditText_("CRED416", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED417", SCALE_BIG, true);
    PrintCreditText_("CRED418", SCALE_SMALL, false);
    PrintCreditText_("CRED419", SCALE_SMALL, false);
    PrintCreditText_("CRED420", SCALE_SMALL, false);
    PrintCreditText_("CRED421", SCALE_SMALL, false);
    PrintCreditText_("CRED422", SCALE_SMALL, false);
    PrintCreditText_("CRED423", SCALE_SMALL, false);
    PrintCreditText_("CRED424", SCALE_SMALL, false);
    PrintCreditText_("CRED425", SCALE_SMALL, false);
    PrintCreditText_("CRED426", SCALE_SMALL, false);
    PrintCreditText_("CRED427", SCALE_SMALL, false);
    PrintCreditText_("CRED428", SCALE_SMALL, false);
    PrintCreditText_("CRED429", SCALE_SMALL, false);
    PrintCreditText_("CRED430", SCALE_SMALL, false);
    PrintCreditText_("CRED431", SCALE_SMALL, false);
    PrintCreditText_("CRED432", SCALE_SMALL, false);
    PrintCreditText_("CRED433", SCALE_SMALL, false);
    PrintCreditText_("CRED434", SCALE_SMALL, false);
    PrintCreditText_("CRED435", SCALE_SMALL, false);
    PrintCreditText_("CRED436", SCALE_SMALL, false);
    PrintCreditText_("CRED437", SCALE_SMALL, false);
    PrintCreditText_("CRED438", SCALE_SMALL, false);
    PrintCreditText_("CRED439", SCALE_SMALL, false);
    PrintCreditText_("CRED440", SCALE_SMALL, false);
    PrintCreditText_("CRED441", SCALE_SMALL, false);
    PrintCreditText_("CRED442", SCALE_SMALL, false);
    PrintCreditText_("CRED443", SCALE_SMALL, false);
    PrintCreditText_("CRED444", SCALE_SMALL, false);
    PrintCreditText_("CRED445", SCALE_SMALL, false);
    PrintCreditText_("CRED446", SCALE_SMALL, false);
    PrintCreditText_("CRED447", SCALE_SMALL, false);
    PrintCreditText_("CRED448", SCALE_SMALL, false);
    PrintCreditText_("CRED449", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED450", SCALE_BIG, true);
    PrintCreditText_("CRED451", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED452", SCALE_BIG, true);
    PrintCreditText_("CRED453", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED454", SCALE_BIG, true);
    PrintCreditText_("CRED455", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRD455A", SCALE_BIG, true);
    PrintCreditText_("CRD455B", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRD455C", SCALE_BIG, true);
    PrintCreditText_("CRD455D", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED456", SCALE_BIG, true);
    PrintCreditText_("CRED457", SCALE_SMALL, false);
    PrintCreditText_("CRED458", SCALE_SMALL, false);
    PrintCreditText_("CRED459", SCALE_SMALL, false);
    PrintCreditText_("CRED460", SCALE_SMALL, false);
    PrintCreditText_("CRED461", SCALE_SMALL, false);
    PrintCreditText_("CRED462", SCALE_SMALL, false);
    PrintCreditText_("CRED463", SCALE_SMALL, false);
    PrintCreditText_("CRED464", SCALE_SMALL, false);
    PrintCreditText_("CRED465", SCALE_SMALL, false);
    PrintCreditText_("CRED466", SCALE_SMALL, false);
    PrintCreditText_("CRED467", SCALE_SMALL, false);
    PrintCreditText_("CRED468", SCALE_SMALL, false);
    PrintCreditText_("CRED469", SCALE_SMALL, false);
    PrintCreditText_("CRED470", SCALE_SMALL, false);
    PrintCreditText_("CRED471", SCALE_SMALL, false);
    PrintCreditText_("CRED472", SCALE_SMALL, false);
    PrintCreditText_("CRED473", SCALE_SMALL, false);
    PrintCreditText_("CRED474", SCALE_SMALL, false);
    PrintCreditText_("CRED475", SCALE_SMALL, false);
    PrintCreditText_("CRED476", SCALE_SMALL, false);
    PrintCreditText_("CRED477", SCALE_SMALL, false);
    PrintCreditText_("CRED478", SCALE_SMALL, false);
    PrintCreditText_("CRED479", SCALE_SMALL, false);
    PrintCreditText_("CRED480", SCALE_SMALL, false);
    PrintCreditText_("CRED481", SCALE_SMALL, false);
    PrintCreditText_("CRED482", SCALE_SMALL, false);
    PrintCreditText_("CRED483", SCALE_SMALL, false);
    PrintCreditText_("CRED484", SCALE_SMALL, false);
    PrintCreditText_("CRED485", SCALE_SMALL, false);
    PrintCreditText_("CRED486", SCALE_SMALL, false);
    PrintCreditText_("CRED487", SCALE_SMALL, false);
    PrintCreditText_("CRED488", SCALE_SMALL, false);
    PrintCreditText_("CRED489", SCALE_SMALL, false);
    PrintCreditText_("CRED490", SCALE_SMALL, false);
    PrintCreditText_("CRED491", SCALE_SMALL, false);
    PrintCreditText_("CRED492", SCALE_SMALL, false);
    PrintCreditText_("CRED493", SCALE_SMALL, false);
    PrintCreditText_("CRED494", SCALE_SMALL, false);
    PrintCreditText_("CRED495", SCALE_SMALL, false);
    PrintCreditText_("CRED496", SCALE_SMALL, false);
    PrintCreditText_("CRED497", SCALE_SMALL, false);
    PrintCreditText_("CRED498", SCALE_SMALL, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED499", SCALE_BIG, true);
    PrintCreditText_("CRED500", SCALE_BIG, false);
    PrintCreditText_("CRED501", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED502", SCALE_BIG, true);
    PrintCreditText_("CRED503", SCALE_BIG, false);
    PrintCreditText_("CRED504", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED505", SCALE_BIG, true);
    PrintCreditText_("CRED506", SCALE_BIG, false);
    PrintCreditText_("CRED507", SCALE_BIG, false);
    PrintCreditText_("CRED508", SCALE_BIG, false);
    PrintCreditText_("CRED509", SCALE_BIG, false);
    PrintCreditText_("CRED510", SCALE_BIG, false);
    PrintCreditText_("CRED511", SCALE_BIG, false);
    PrintCreditText_("CRED512", SCALE_BIG, false);
    PrintCreditText_("CRED515", SCALE_BIG, false);
    PrintCreditText_("CRED516", SCALE_BIG, false);
    PrintCreditText_("CRED517", SCALE_BIG, false);
    PrintCreditText_("CRED518", SCALE_BIG, false);
    PrintCreditText_("CRED519", SCALE_BIG, false);
    PrintCreditText_("CRED520", SCALE_BIG, false);
    PrintCreditText_("CRED521", SCALE_BIG, false);
    PrintCreditText_("CRED522", SCALE_BIG, false);
    PrintCreditText_("CRED523", SCALE_BIG, false);
    PrintCreditText_("CRED524", SCALE_BIG, false);
    PrintCreditText_("CRED525", SCALE_BIG, false);
    PrintCreditText_("CRED526", SCALE_BIG, false);
    PrintCreditText_("CRED527", SCALE_BIG, false);
    PrintCreditText_("CRED529", SCALE_BIG, false);
    PrintCreditText_("CRED530", SCALE_BIG, false);
    PrintCreditText_("CRED531", SCALE_BIG, false);
    PrintCreditText_("CRED532", SCALE_BIG, false);
    PrintCreditText_("CRED533", SCALE_BIG, false);
    PrintCreditText_("CRED534", SCALE_BIG, false);
    PrintCreditText_("CRED535", SCALE_BIG, false);
    PrintCreditText_("CRED536", SCALE_BIG, false);
    PrintCreditText_("CRED537", SCALE_BIG, false);
    PrintCreditText_("CRED538", SCALE_BIG, false);
    PrintCreditText_("CRED539", SCALE_BIG, false);
    PrintCreditText_("CRED540", SCALE_BIG, false);
    PrintCreditText_("CRED541", SCALE_BIG, false);
    PrintCreditText_("CRD541A", SCALE_BIG, false);
    PrintCreditText_("CRD541B", SCALE_BIG, false);
    PrintCreditText_("CRD541C", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED542", SCALE_BIG, true);
    PrintCreditText_("CRED543", SCALE_BIG, false);
    PrintCreditText_("CRED544", SCALE_BIG, false);
    PrintCreditText_("CRED545", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED600", SCALE_BIG, true);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED601", SCALE_BIG, true);
    PrintCreditText_("CRED602", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED603", SCALE_BIG, true);
    PrintCreditText_("CRED604", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED605", SCALE_BIG, true);
    PrintCreditText_("CRED606", SCALE_BIG, false);
    PrintCreditText_("CRED607", SCALE_BIG, false);
    PrintCreditText_("CRED608", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED609", SCALE_BIG, true);
    PrintCreditText_("CRED610", SCALE_BIG, false);
    PrintCreditText_("CRED611", SCALE_BIG, false);
    PrintCreditText_("CRED612", SCALE_BIG, false);
    PrintCreditText_("CRED613", SCALE_BIG, false);
    PrintCreditText_("CRED614", SCALE_BIG, false);
    PrintCreditText_("CRED615", SCALE_BIG, false);
    PrintCreditText_("CRED616", SCALE_BIG, false);
    PrintCreditText_("CRED617", SCALE_BIG, false);
    PrintCreditText_("CRED618", SCALE_BIG, false);
    PrintCreditText_("CRED619", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED620", SCALE_BIG, true);
    PrintCreditText_("CRED621", SCALE_BIG, false);
    PrintCreditText_("CRED622", SCALE_BIG, false);
    PrintCreditText_("CRED623", SCALE_BIG, false);
    PrintCreditText_("CRED624", SCALE_BIG, false);
    PrintCreditText_("CRED625", SCALE_BIG, false);
    PrintCreditText_("CRED626", SCALE_BIG, false);
    PrintCreditText_("CRED627", SCALE_BIG, false);
    PrintCreditText_("CRED628", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED629", SCALE_BIG, true);
    PrintCreditText_("CRED630", SCALE_BIG, false);
    PrintCreditSpace(SPACE_BIG, lineOffset);

    PrintCreditText_("CRED700", SCALE_BIG, true);
    PrintCreditText_("CRED701", SCALE_BIG, false);
    PrintCreditText_("CRED702", SCALE_BIG, false);
    PrintCreditText_("CRED703", SCALE_BIG, false);
    PrintCreditText_("CRED704", SCALE_BIG, false);
    PrintCreditText_("CRED705", SCALE_BIG, false);
    PrintCreditText_("CRED706", SCALE_BIG, false);
    PrintCreditText_("CRED707", SCALE_BIG, false);
    PrintCreditText_("CRED708", SCALE_BIG, false);
    PrintCreditText_("CRED709", SCALE_BIG, false);
    PrintCreditText_("CRED710", SCALE_BIG, false);
    PrintCreditText_("CRED711", SCALE_BIG, false);
    PrintCreditText_("CRED712", SCALE_BIG, false);
    PrintCreditText_("CRED713", SCALE_BIG, false);
    PrintCreditText_("CRED714", SCALE_BIG, false);
    PrintCreditText_("CRED715", SCALE_BIG, false);
    PrintCreditText_("CRED716", SCALE_BIG, false);

    CFont::DrawFonts();
    if (TheCamera.m_bWideScreenOn) {
        TheCamera.DrawBordersForWideScreen();
    }

    if (lineOffset + SCREEN_HEIGHT - scrollOffset < -10.0f) {
        bCreditsGoing = false;
    }
}
