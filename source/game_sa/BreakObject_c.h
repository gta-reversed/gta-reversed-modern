#pragma once

#include "Base.h"

#include "Vector.h"
#include <rwplcore.h>

struct BreakGroupRenderInfo_t {
    RwV3d       positions[3];
    RwTexCoords texCoords[3];
    CRGBA       colors[3];
};

struct BreakGroup_t {
    RwMatrix                m_Matrix;
    RwV3d                   m_Velocity;
    bool                    m_bStoppedMoving;
    int16                   m_NumTriangles;
    BreakGroupRenderInfo_t* m_RenderInfo;
    RwTexture*              m_Texture;
    int8                    m_Type;
    float                   m_BoundingSize;
    float                   m_RotationSpeed;
    CVector                 m_RotationAxis;
    int32                   m_FramesToLive;
};
VALIDATE_SIZE(BreakGroup_t, 0x74);

class BreakObject_c {
public:
    bool          m_JustFaces;
    bool          m_bActive;
    bool          m_AddSparks;
    bool          m_bDrawLast;
    int32         m_NumBreakGroups;
    BreakGroup_t* m_BreakGroups;
    int32         m_FramesActive;
    float         m_GroundZ;
    CVector       m_VecNormal;

public:
    static void InjectHooks();

    BreakObject_c();
    ~BreakObject_c() = default;

    bool Init(CObject* object, RwV3d* vecVelocity, float fVelocityRand, int32 bJustFaces);
    void Exit();

    void CalcGroupCenter(BreakGroup_t* group);
    void SetGroupData(RwMatrix* matrix, RwV3d* vecVelocity, float fVelocityRand);
    void SetBreakInfo(BreakInfo_t* info, int32 bJustFaces);

    void DoCollisionResponse(BreakGroup_t* group, float timeStep, RwV3d* vecNormal, float groundZ);
    void DoCollision(BreakGroup_t* group, float timeStep);
    void Update(float timeStep);
    void Render(bool isDrawLast) const;
};

VALIDATE_SIZE(BreakObject_c, 0x20);
