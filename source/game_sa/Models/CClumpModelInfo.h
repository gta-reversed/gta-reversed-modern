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


class  CClumpModelInfo : public CBaseModelInfo {
public:
	union{
		char *m_animFileName;
		unsigned int m_dwAnimFileIndex;
	};

	// vtable

	CBox *GetBoundingBox();
	void SetClump(RpClump *clump);

	// static functions

	static void SetAtomicRendererCB(RpAtomic *atomic, void *renderFunc);
	/* struct tSearchData { char *name; RwFrame *result; };
	  returns 0 if we found frame, or last frame if we need to continue searching */
	static RwFrame *FindFrameFromNameCB(RwFrame *frame, void *searchData);
	static RwFrame *FindFrameFromNameWithoutIdCB(RwFrame *frame, void *searchData);
	static RwFrame *FindFrameFromIdCB(RwFrame *frame, void *searchData);
	static RwFrame *FillFrameArrayCB(RwFrame *frame, void *data);
	static RwFrame *GetFrameFromId(RpClump *clump, int id);
	static RwFrame *GetFrameFromName(RpClump *clump, char *name);
	static void FillFrameArray(RpClump *clump, RwFrame **frames);
    void SetFrameIds(RwObjectNameIdAssocation* data);
};

VALIDATE_SIZE(CClumpModelInfo, 0x24);