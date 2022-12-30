#pragma once

static inline bool    DefaultVideoMode = *(bool*)0x8D2E34;
static inline bool    MultipleVideoModes = *(bool*)0xC92118;
static inline bool    VideoModeNotSelected = *(bool*)0x8D6218;

/*
* Dynamic array of video modes with format "width x height x depth"
*/
static inline char**& gVideoModes = *(char***)0xC920D0;
static inline uint32& gCurrentGpu = *(uint32*)0x8D6248;
static inline uint32  gnMemTotalVideo = *(uint32*)(0xC8CF68 + 0x18); // todo: fix
static inline int32&  gCurrentVideoMode = *(int32*)0x8D6220;

void VideoModeInjectHooks();

extern char** GetVideoModeList();
extern bool FreeVideoModeList();
extern void SetVideoMode(int32 mode);
extern bool IsVideoModeExclusive();
