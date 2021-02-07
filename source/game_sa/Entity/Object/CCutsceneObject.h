/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CObject.h"

class  CCutsceneObject : public CObject {
public:
    CCutsceneObject();
public:
    union {
        RwFrame *m_pAttachTo;
        unsigned int m_nAttachBone; // this one if m_pAttachmentObject != 0
    };
    CObject *m_pAttachmentObject;
    CVector m_vWorldPosition;
    CVector m_vForce;

public:
    static constexpr int NUM_CUTSCENE_VEHS = 6;
    static char*(&ms_sCutsceneVehNames)[NUM_CUTSCENE_VEHS];

public:
    static void InjectHooks();

    void SetModelIndex(unsigned int index) override;
    void ProcessControl() override;
    void PreRender() override;
    bool SetupLighting() override;
    void RemoveLighting(bool bRemove) override;
private:
    void SetModelIndex_Reversed(unsigned int index);
    void ProcessControl_Reversed();
    void PreRender_Reversed();
    bool SetupLighting_Reversed();
    void RemoveLighting_Reversed(bool bRemove);

private: //Functions fully inlined in android idb, and unnamed in PC idb
    static void SetupCarPipeAtomicsForClump(unsigned int modelId, RpClump* pClump);
    static RpAtomic* SetupCarPipeAtomicCB(RpAtomic* pAtomic, void* data);

};

VALIDATE_SIZE(CCutsceneObject, 0x19C);
