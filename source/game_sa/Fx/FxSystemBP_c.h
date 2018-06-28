/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "ListItem_c.h"
#include "FxSphere_c.h"

class FxSystem_c;

/* FX System BluePrint */

class FxSystemBP_c : public ListItem_c {
public:
    unsigned int m_nNameKey;
    float m_fLength;
    float m_fLoopIntervalMin;
    float m_fLoopLength;
    short m_nCullDist;
    unsigned char m_nPlayMode;
    unsigned char m_nNumEmitters;
    void **m_emittersList;
    FxSphere_c *m_pBoundingSphere;

    FxSystemBP_c();
    ~FxSystemBP_c();
    static void* operator new(unsigned int size);
    void Unload();
    unsigned int Update(float arg0);
    void Render(RwCamera* camera, float arg1, unsigned char arg2);
    bool FreePrtFromSystem(FxSystem_c* system);
    FxSphere_c* GetBoundingSphere();
    void SetBoundingSphere(RwV3d* center, float radius);
    void Load(char* filename, int file, int version);
};

VALIDATE_SIZE(FxSystemBP_c, 0x24);