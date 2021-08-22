#include "StdInc.h"

int& CCredits::m_nCreditsStartTime = *(int*)0xC6E978;
bool& CCredits::m_bCreditsGoing = *(bool*)0xC6E97C;

//NOTSA
float CCredits::m_Position = 0.0f;
float CCredits::m_CurrentOffset = 0.0f;

void CCredits::InjectHooks() {
    ReversibleHooks::Install("CCredits", "Render", 0x53D5B0, &CCredits::Render);
//    ReversibleHooks::Install("CCredits", "PrintCreditText", 0x5A8660, &CCredits::PrintCreditText);
//    ReversibleHooks::Install("CCredits", "PrintCreditSpace", 0x5A87C0, &CCredits::PrintCreditSpace);
//    ReversibleHooks::Install("CCredits", "RenderCredits", 0x5A87F0, &CCredits::RenderCredits);
    ReversibleHooks::Install("CCredits", "Start", 0x7170E0, &CCredits::Start);
    ReversibleHooks::Install("CCredits", "Stop", 0x717100, &CCredits::Stop);
}

// 0x53D5B0
void CCredits::Render() {
    if (m_bCreditsGoing && !FrontEndMenuManager.m_bMenuActive) {
        RenderCredits();
    }
}

// 0x5A8660
void CCredits::PrintCreditText(float scaleX, float scaleY, const char *text, float &position, float currentOffset, bool highlighted) {
    plugin::CallMethod<0x5A8660, float, float, const char*, float&, float, bool>(scaleX, scaleY, text, position, currentOffset, highlighted);
}

// 0x5A87C0
void CCredits::PrintCreditSpace(float spaceSize, unsigned int &position) {

}

void CCredits::PrintCreditTextHelper(char *textKey, float scale, bool highlighted) {
    auto text = TheText.Get(textKey);
    CCredits::PrintCreditText(scale, scale, text, CCredits::m_Position, CCredits::m_CurrentOffset, highlighted);
}

// 0x5A87F0
void CCredits::RenderCredits() {
    float ScaleBig = 1.1f;
    float ScaleSmall = 0.78f;

    DefinedState2d();

    CCredits::m_Position = 0.0f;
    CCredits::m_CurrentOffset = float(CTimer::m_snTimeInMilliseconds - CCredits::m_nCreditsStartTime) * 0.0435f;
    
    CFont::SetBackground(false, false);
    CFont::SetCentreSize(float(RsGlobal.maximumWidth) * 0.92f);
    CFont::SetOrientation(ALIGN_CENTER);
    CFont::SetProportional(true);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetEdge(0);
    CFont::SetDropColor(CRGBA(0, 0, 255));

    PrintCreditTextHelper((char*)"CRED000", ScaleBig, true);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED001", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED002", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED003", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED004", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED005", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED006", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED007", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED008", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED009", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRD009A", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRD009B", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD009C", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD009D", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED019", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED020", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED010", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED011", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED012", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED013", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED014", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD014A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED015", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED016", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRD016A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED017", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED018", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED028", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED029", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED030", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED031", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED032", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED033", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED034", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED035", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED036", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED047", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED048", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED049", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED050", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED051", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED052", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED053", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED054", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED055", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED056", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED057", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED058", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED059", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED060", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED061", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED062", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED063", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED021", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED022", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED023", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED024", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED025", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED026", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED027", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED064", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED065", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED066", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED067", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED068", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED069", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED070", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED071", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED072", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED073", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED074", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED075", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED037", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED038", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED039", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED040", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED041", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED042", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED043", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED044", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED991", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED045", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED046", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED076", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED077", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED078", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED079", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED080", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED081", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED100", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED082", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED083", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED084", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED085", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED086", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED087", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED088", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED089", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED090", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED091", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED092", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED093", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED094", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED095", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED096", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED097", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED098", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED099", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED101", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED102", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED103", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED104", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED105", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED106", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED107", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED108", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED109", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED110", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED111", ScaleBig, true);
    CCredits::m_Position += 25.0f;

    PrintCreditTextHelper((char*)"CRED112", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED113", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED114", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED115", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED116", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED117", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED118", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED997", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD118A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED119", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED120", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED996", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD120A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED121", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD121A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED995", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED122", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED994", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED123", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED124", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED125", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED126", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD126A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD126B", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED127", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED128", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED129", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD129A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED130", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED131", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED132", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED133", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED134", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED992", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD134A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED135", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED136", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD136A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED137", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED138", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD138A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED139", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED140", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED141", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED993", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED142", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED143", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED144", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED145", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED146", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED147", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED148", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED149", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED150", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED151", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED152", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED153", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD153A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED154", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD154A", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED155", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED156", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED157", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED158", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED159", ScaleBig, false);
    CCredits::m_Position += 37.5f + 37.5f;

    PrintCreditTextHelper((char*)"CRED199", ScaleBig, true);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED200", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED201", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED202", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED203", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED204", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED205", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED206", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED207", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED208", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED209", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED210", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED211", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED212", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED213", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED214", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED215", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED216", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED217", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED218", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED219", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED220", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED221", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED222", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED223", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED224", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED225", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED226", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED227", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED228", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED229", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED230", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED231", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED232", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED233", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED234", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED235", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED236", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED237", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED238", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED239", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED240", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED241", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED242", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED243", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED244", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED245", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED246", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED247", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED248", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED249", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED250", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED251", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED252", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED253", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED254", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED255", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED256", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED257", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED258", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED259", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED260", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED261", ScaleBig, true);
    CCredits::m_Position += 25.0f;

    PrintCreditTextHelper((char*)"CRED262", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED263", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED264", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED265", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED266", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED267", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED999", ScaleBig, true);
    CCredits::m_Position += 25.0f;

    PrintCreditTextHelper((char*)"CRED998", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED268", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED269", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED270", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED271", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED272", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED273", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED274", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED275", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED276", ScaleBig, false);
    CCredits::m_Position += 37.5f + 37.5f;

    PrintCreditTextHelper((char*)"CRED277", ScaleBig, true);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED278", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED279", ScaleSmall, false);
    CCredits::m_Position += 12.5f;

    PrintCreditTextHelper((char*)"CRED280", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED281", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED282", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED283", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED284", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED285", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED286", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED287", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED288", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED289", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED290", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED291", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED292", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED293", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED294", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED295", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED296", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED297", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED298", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED299", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED300", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED301", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED302", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED303", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED304", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED305", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED306", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED307", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED308", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308A", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308B", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308C", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308D", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308E", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308F", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308G", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308H", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308I", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308J", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308K", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRD308L", ScaleSmall, false);
    CCredits::m_Position += 12.5f;

    PrintCreditTextHelper((char*)"CRD308M", ScaleSmall, false);
    CCredits::m_Position += 37.5f + 12.5f;

    PrintCreditTextHelper((char*)"CRD308N", ScaleSmall, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED309", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED310", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED311", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED312", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED313", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED314", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED315", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED316", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED317", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED318", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED319", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED320", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED321", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED322", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED323", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED324", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED325", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED326", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED327", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED328", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED329", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED330", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED331", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED332", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED333", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED334", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED335", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED336", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED337", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED338", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED339", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED340", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED341", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED342", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED343", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED344", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED345", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED346", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED347", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED348", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED349", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED350", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED351", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED352", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED353", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED354", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED355", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED356", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED357", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED358", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED359", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED360", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED361", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED362", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED363", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED364", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED365", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED366", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED367", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED368", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED369", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED370", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED371", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED372", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED373", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED374", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED375", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED376", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED377", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED378", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED379", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED380", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED381", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED382", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED383", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED384", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED385", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED386", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED387", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED388", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED389", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED390", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED391", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED392", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED393", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED394", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED395", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED396", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED397", ScaleSmall, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED398", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED399", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED400", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED401", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED402", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED403", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED404", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED405", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED406", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED407", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED408", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED409", ScaleBig, false);
    CCredits::m_Position += 12.5f;

    PrintCreditTextHelper((char*)"CRED410", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED411", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED412", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED413", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED414", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED415", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED416", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED417", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED418", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED419", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED420", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED421", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED422", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED423", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED424", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED425", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED426", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED427", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED428", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED429", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED430", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED431", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED432", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED433", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED434", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED435", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED436", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED437", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED438", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED439", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED440", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED441", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED442", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED443", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED444", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED445", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED446", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED447", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED448", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED449", ScaleSmall, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED450", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED451", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED452", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED453", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED454", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED455", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRD455A", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRD455B", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRD455C", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRD455D", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED456", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED457", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED458", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED459", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED460", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED461", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED462", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED463", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED464", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED465", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED466", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED467", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED468", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED469", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED470", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED471", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED472", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED473", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED474", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED475", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED476", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED477", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED478", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED479", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED480", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED481", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED482", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED483", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED484", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED485", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED486", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED487", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED488", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED489", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED490", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED491", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED492", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED493", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED494", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED495", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED496", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED497", ScaleSmall, false);
    PrintCreditTextHelper((char*)"CRED498", ScaleSmall, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED499", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED500", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED501", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED502", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED503", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED504", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED505", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED506", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED507", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED508", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED509", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED510", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED511", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED512", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED515", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED516", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED517", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED518", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED519", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED520", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED521", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED522", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED523", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED524", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED525", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED526", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED527", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED529", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED530", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED531", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED532", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED533", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED534", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED535", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED536", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED537", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED538", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED539", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED540", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED541", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD541A", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD541B", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRD541C", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED542", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED543", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED544", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED545", ScaleBig, false);
    CCredits::m_Position += 37.5f + 37.5f;

    PrintCreditTextHelper((char*)"CRED600", ScaleBig, true);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED601", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED602", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED603", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED604", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED605", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED606", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED607", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED608", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED609", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED610", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED611", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED612", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED613", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED614", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED615", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED616", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED617", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED618", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED619", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED620", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED621", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED622", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED623", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED624", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED625", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED626", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED627", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED628", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED629", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED630", ScaleBig, false);
    CCredits::m_Position += 37.5f;

    PrintCreditTextHelper((char*)"CRED700", ScaleBig, true);
    PrintCreditTextHelper((char*)"CRED701", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED702", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED703", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED704", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED705", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED706", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED707", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED708", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED709", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED710", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED711", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED712", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED713", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED714", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED715", ScaleBig, false);
    PrintCreditTextHelper((char*)"CRED716", ScaleBig, false);

    CFont::DrawFonts();
    if (TheCamera.m_bWideScreenOn) {
        TheCamera.DrawBordersForWideScreen();
    }

    if (CCredits::m_Position + RsGlobal.maximumHeight - CCredits::m_CurrentOffset < -10.0) {
        CCredits::m_bCreditsGoing = false;
    }
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
