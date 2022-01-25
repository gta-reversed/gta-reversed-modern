#pragma once

struct tTagDesc {
    CEntity* m_pEntity;
    uint8    m_nAlpha;
    uint8    _pad[3];
};

class CTagManager {
public:
    static constexpr uint8  ALPHA_TAGGED = 228;
    static constexpr uint32 MAX_TAGS = 150;

    static tTagDesc     (&ms_tagDesc)[MAX_TAGS];
    static int32&       ms_numTags;
    static int32&       ms_numTagged;
    static RxPipeline*& ms_pPipeline;

public:
    static void InjectHooks();

public:
    static void     Init();
    static void     ShutdownForRestart();
    static CVector& GetTagPos(int32 iTag);
    static void     AddTag(CEntity* entity);
    static bool     IsTag(const CEntity* entity);
    static uint8    GetAlpha(CEntity* entity);
    static void     ResetAlpha(CEntity* entity);
    static int64_t  GetPercentageTaggedInArea(CRect* area);
    static int64_t  GetPercentageTagged();
    static void     UpdateNumTagged();
    static void     SetAlphaInArea(CRect* area, uint8 ucAlpha);
    static void     SetAlpha(CEntity* entity, uint8 ucAlpha);
    static CEntity* GetNearestTag(const CVector& vecPos);
    static void     SetupAtomic(RpAtomic* atomic);
    static void     RenderTagForPC(RpAtomic* atomic);
    static void     Save();
    static void     Load();

private:
    static void      SetAlpha(RpAtomic* atomic, uint8 ucAlpha);
    static uint8     GetAlpha(RpAtomic* atomic);
    static tTagDesc* FindTagDesc(CEntity* entity);
};
