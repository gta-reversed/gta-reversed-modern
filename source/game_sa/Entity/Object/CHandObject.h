/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CObject.h"

class CHandObject : public CObject {
public:
    class CPed* m_pPed;
    uint32      m_nBoneIndex;
    RwTexture*  m_pTexture;
    bool        m_bUpdatedMatricesArray;
    char        _pad[3];

public:
    static void InjectHooks();

    CHandObject(int32 handModelIndex, CPed* pPed, bool bLeftHand);
    ~CHandObject() = default;

    void ProcessControl() override;
    void PreRender() override;
    void Render() override;

private:
    void ProcessControl_Reversed();
    void PreRender_Reversed();
    void Render_Reversed();
};

VALIDATE_SIZE(CHandObject, 0x18C);
