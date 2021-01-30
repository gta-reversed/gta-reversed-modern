/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CBaseModelInfo.h"
#include "RwObjectNameIdAssocation.h"

struct RwFrame;
struct RpAtomic;
struct RpClump;

struct tCompSearchStructByName {
    char* m_pName;
    RwFrame* m_pFrame;

    inline tCompSearchStructByName(char* name, RwFrame* frame) : m_pName(name), m_pFrame(frame) {}
};
struct tCompSearchStructById {
    int32_t m_nId;
    RwFrame* m_pFrame;

    inline tCompSearchStructById(int32_t id, RwFrame* frame) : m_nId(id), m_pFrame(frame) {}
};


class  CClumpModelInfo : public CBaseModelInfo {
public:
    CClumpModelInfo() : CBaseModelInfo() {}
public:
	union{
		char *m_animFileName;
		unsigned int m_dwAnimFileIndex;
	};

public:
    static void InjectHooks();

    // Overriden vtable methods
    ModelInfoType GetModelType() override;
    void Init() override;
    void Shutdown() override;
    void DeleteRwObject() override;
    unsigned int GetRwModelType() override;
    RwObject* CreateInstance() override;
    RwObject* CreateInstance(RwMatrix* matrix) override;
    void SetAnimFile(char const* filename) override;
    void ConvertAnimFileIndex() override;
    signed int GetAnimFileIndex() override;

	// Added vtable methods
    virtual CBox *GetBoundingBox();
    virtual void SetClump(RpClump *clump);

    // Reversed vtable methods
    ModelInfoType GetModelType_Reversed();
    void Init_Reversed();
    void Shutdown_Reversed();
    void DeleteRwObject_Reversed();
    unsigned int GetRwModelType_Reversed();
    RwObject* CreateInstance_Reversed();
    RwObject* CreateInstance_Reversed(RwMatrix* matrix);
    void SetAnimFile_Reversed(char const* filename);
    void ConvertAnimFileIndex_Reversed();
    signed int GetAnimFileIndex_Reversed();
    CBox* GetBoundingBox_Reversed();
    void SetClump_Reversed(RpClump* clump);

    // Class functions
    void SetFrameIds(RwObjectNameIdAssocation* data);

	// static functions
	static RpAtomic* SetAtomicRendererCB(RpAtomic *atomic, void *renderFunc);
    static RpAtomic* AtomicSetupLightingCB(RpAtomic* atomic, void* data);
    static RpAtomic* SetHierarchyForSkinAtomic(RpAtomic* pAtomic, void* data);
	/* struct tSearchData { char *name; RwFrame *result; };
	  returns 0 if we found frame, or last frame if we need to continue searching */
	static RwFrame *FindFrameFromNameCB(RwFrame *frame, void *searchData);
	static RwFrame *FindFrameFromNameWithoutIdCB(RwFrame *frame, void *searchData);
	static RwFrame *FindFrameFromIdCB(RwFrame *frame, void *searchData);
	static RwFrame *FillFrameArrayCB(RwFrame *frame, void *data);
	static RwFrame *GetFrameFromId(RpClump *clump, int id);
	static RwFrame *GetFrameFromName(RpClump *clump, char *name);
	static void FillFrameArray(RpClump *clump, RwFrame **frames);
};

void SetClumpModelInfoFlags(CClumpModelInfo* modelInfo, unsigned int dwFlags);

VALIDATE_SIZE(CClumpModelInfo, 0x24);
