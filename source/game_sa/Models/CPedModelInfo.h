/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CClumpModelInfo.h"
#include "CColModel.h"

struct tPedColNodeInfo {
private:
    int m_nPad;
public:
    int m_nBoneID; // see ePedBones
    int m_nFlags;
    CVector m_vecCenter;
    float m_fRadius;
};

class  CPedModelInfo : public CClumpModelInfo {
public:
    CPedModelInfo() : CClumpModelInfo(), m_pHitColModel(nullptr) {}
    ~CPedModelInfo() { if (m_pHitColModel) delete m_pHitColModel; }
public:
    int m_nAnimType;
    unsigned int m_nPedType;
    unsigned int m_nStatType;
    unsigned short m_nCarsCanDriveMask;
    unsigned short m_nPedFlags;
    CColModel *m_pHitColModel;
    unsigned char m_nRadio1;
    unsigned char m_nRadio2;
    unsigned char m_nRace;
private:
    char __pad;
public:
    short m_nPedAudioType;
    short m_nVoiceMin;
    short m_nVoiceMax;
    short m_nVoiceId;

public:
    static constexpr int NUM_PED_NAME_ID_ASSOC = 13;
    static RwObjectNameIdAssocation (&m_pPedIds)[NUM_PED_NAME_ID_ASSOC];
    static constexpr int NUM_PED_COL_NODE_INFOS = 12;
    static tPedColNodeInfo(&m_pColNodeInfos)[NUM_PED_COL_NODE_INFOS];

public:
    static void InjectHooks();

// virtual
    ModelInfoType GetModelType() override;
    void DeleteRwObject() override;
    void SetClump(RpClump* clump) override;

// virtual implementations
    ModelInfoType GetModelType_Reversed();
    void DeleteRwObject_Reversed();
    void SetClump_Reversed(RpClump* clump);

// class
    void AddXtraAtomics(RpClump* pClump); //empty
    void SetFaceTexture(RwTexture* pTexture); //empty
    void CreateHitColModelSkinned(RpClump* pClump);
    CColModel* AnimatePedColModelSkinned(RpClump* pClump);
    CColModel* AnimatePedColModelSkinnedWorld(RpClump* pClump);
    void IncrementVoice();
};

VALIDATE_SIZE(CPedModelInfo, 0x44);
