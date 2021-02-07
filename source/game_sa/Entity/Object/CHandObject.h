/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CObject.h"

class  CHandObject : public CObject {
public:
    CHandObject(int handModelIndex, CPed* pPed, bool bLeftHand);
    ~CHandObject() = default;
public:
    class CPed  *m_pPed;
    unsigned int m_nBoneIndex;
    RwTexture   *m_pTexture;
    bool         m_bUpdatedMatricesArray;
    char _pad[3];

public:
    static void InjectHooks();

    void ProcessControl() override;
    void PreRender() override;
    void Render() override;

private:
    void ProcessControl_Reversed();
    void PreRender_Reversed();
    void Render_Reversed();
};

VALIDATE_SIZE(CHandObject, 0x18C);
