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
    static tTagDesc (&ms_tagDesc)[MAX_TAGS];
    static int32&       ms_numTags;
    static int32&       ms_numTagged;
    static RxPipeline*& ms_pPipeline;

public:
    static void InjectHooks();

public:
    static void     Init();
    static void     ShutdownForRestart();
    static CVector& GetTagPos(int32 iTag);
    static void     AddTag(CEntity* pEntity);
    static bool     IsTag(CEntity const* pEntity);
    static uint8    GetAlpha(CEntity* pEntity);
    static void     ResetAlpha(CEntity* pEntity);
    static int64_t  GetPercentageTaggedInArea(CRect* pArea);
    static int64_t  GetPercentageTagged();
    static void     UpdateNumTagged();
    static void     SetAlphaInArea(CRect* pArea, uint8 ucAlpha);
    static void     SetAlpha(CEntity* pEntity, uint8 ucAlpha);
    static CEntity* GetNearestTag(CVector const& vecPos);
    static void     SetupAtomic(RpAtomic* pAtomic);
    static void     RenderTagForPC(RpAtomic* pAtomic);
    static void     Save();
    static void     Load();

private:
    static void      SetAlpha(RpAtomic* pAtomic, uint8 ucAlpha);
    static uint8     GetAlpha(RpAtomic* pAtomic);
    static tTagDesc* FindTagDesc(CEntity* pEntity);
};
