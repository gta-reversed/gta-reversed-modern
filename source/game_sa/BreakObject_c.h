#pragma once

#include "Base.h"

#include "Vector.h"
#include <rwplcore.h>

struct BreakInfo_t {
    uint32               m_nPosRule;
    uint16               m_nNumVertices;
    char                 _pad06[2];
    CVector*             m_pVertexPos;
    RwTexCoords*         m_pTexCoors;
    RwRGBA*              m_pVertexColors;
    int16                m_usNumTriangles;
    char                 _pad16[2];
    RpTriangle*          m_pTriangles;
    uint16*              m_pMaterialAssignments;
    uint16               m_usNumMaterials;
    char                 _pad22[2];
    RwTexture**          m_pTextures;
    char*                m_pTextureNames;
    char*                m_pMaskNames;
    RwSurfaceProperties* m_pMaterialProperties;
};

struct BreakGroup_test {
    CVector a;
    CVector b;
    CVector c;
};

struct BreakGroup_t_f50 {
    CVector     positions[3];
    RwTexCoords texCoords[3];
    CRGBA       colors[3];
};

struct BreakGroup_t {
    char              pad00[12];
    int32             unk;
    int16             f10;
    char              pad12[14];
    int16             f20;
    char              pad22[14];
    CVector           fxPosn;
    CVector           vec3C;
    float             m_Height;
    int8              f4C;
    char              pad4c;
    int16             m_CountOfF50;
    BreakGroup_t_f50* f50;
    RwTexture*        m_Texture;
    int8              m_Type;
    char              pad58[3];
    float             f5C;
    float             f60;
    CVector           vec64;
    int32             m_Random;
};

class BreakObject_c {
public:
    bool          m_JustFaces;
    bool          m_bActive;
    bool          m_AddSparks;
    int8          m_nRenderPhase;
    int32         m_NumBreakGroups;
    BreakGroup_t* m_BreakGroup;
    CVector       fC;
    float         f18;
    float         f1C;

public:
    static void InjectHooks();

    BreakObject_c();
    ~BreakObject_c() = default;

    bool Init(CObject* object, CVector* posn, float fVelocityRand, int32 bJustFaces);
    void Exit();

    static void CalcGroupCenter(BreakGroup_t* group);

    void SetGroupData(RwMatrix* matrix, CVector* posn, float a5);
    void SetBreakInfo(BreakInfo_t* info, int32 bJustFaces);

    void DoCollisionResponse(BreakGroup_t* group, float a2, CVector* posn, float a4);
    void DoCollision(BreakGroup_t* group, float a2);
    void Update(float timeStep);
    void Render(bool a1);
};

VALIDATE_SIZE(BreakObject_c, 0x20);
