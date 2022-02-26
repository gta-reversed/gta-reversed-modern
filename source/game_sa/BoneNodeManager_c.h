#pragma once

#include "Base.h"

#include "List_c.h"
#include "ListItem_c.h"
#include "BoneNode_c.h"
#include "tBoneInfo.h"

class BoneNodeManager_c {
public:
    static inline tBoneInfo (&ms_boneInfos)[32] = *(tBoneInfo(*)[32])0x8D26D0;

public:
    BoneNode_c          m_space[128] = {}; // 0
    TList_c<BoneNode_c> m_bonesList = {};  // 0x4C00

public:
    static void InjectHooks();

    ~BoneNodeManager_c();
    BoneNodeManager_c();

    bool Init();
    void Exit();
    void Reset();
    BoneNode_c* GetBoneNode();
    void ReturnBoneNode(BoneNode_c* bone);
    int32 GetNumBoneNodesLeft();

private:
    BoneNodeManager_c* Constructor();
    BoneNodeManager_c* Destructor();
};
VALIDATE_SIZE(BoneNodeManager_c, 0x4C0C);

static inline BoneNodeManager_c& g_boneNodeMan = *(BoneNodeManager_c*)0xC10820;
