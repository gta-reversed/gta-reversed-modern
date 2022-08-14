#pragma once

#include "Base.h"

#include "Vector.h"
#include <rwplcore.h>

struct BreakGroup_t_f50 {
    CVector     positions[3];
    RwTexCoords texCoords[3];
    CRGBA       colors[3];
};

struct BreakGroup_t {
    RwMatrixTag       m_Matrix;
    float             m_LengthMaybe;
    float             m_WidthMaybe;
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
