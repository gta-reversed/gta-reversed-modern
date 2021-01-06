#pragma once
#include "PluginBase.h"

struct tTagDesc {
    CEntity* m_pEntity;
    unsigned char m_nAlpha;
    unsigned char _pad[3];
};

class CTagManager {
public:
    static constexpr unsigned char ALPHA_TAGGED = 228;
    static constexpr unsigned int MAX_TAGS = 150;
    static tTagDesc(&ms_tagDesc)[MAX_TAGS];
    static int& ms_numTags;
    static int& ms_numTagged;
    static RxPipeline* &ms_pPipeline;

public:
    static void InjectHooks();

public:
    static void Init();
    static void ShutdownForRestart();
    static CVector& GetTagPos(int iTag);
    static void AddTag(CEntity* pEntity);
    static bool IsTag(CEntity const* pEntity);
    static unsigned char GetAlpha(CEntity* pEntity);
    static void ResetAlpha(CEntity* pEntity);
    static int64_t GetPercentageTaggedInArea(CRect* pArea);
    static int64_t GetPercentageTagged();
    static void UpdateNumTagged();
    static void SetAlphaInArea(CRect* pArea, unsigned char ucAlpha);
    static void SetAlpha(CEntity* pEntity, unsigned char ucAlpha);
    static CEntity* GetNearestTag(CVector const& vecPos);
    static void SetupAtomic(RpAtomic* pAtomic);
    static void RenderTagForPC(RpAtomic* pAtomic);
    static void Save();
    static void Load();

private:
    static void SetAlpha(RpAtomic* pAtomic, unsigned char ucAlpha);
    static unsigned char GetAlpha(RpAtomic* pAtomic);
    static tTagDesc* FindTagDesc(CEntity* pEntity);

};
