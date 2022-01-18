/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "List_c.h"
#include "RenderWare.h"
#include "Vector.h"
#include "AEFireAudioEntity.h"
#include "FxPrtMult_c.h"
#include "FxSphere_c.h"
#include "FxBox_c.h"

enum eFxSystemKillStatus {
    FX_NOT_KILLED = 0,
    FX_PLAY_AND_KILL = 1,
    FX_KILLED = 2
};

enum class eFxSystemPlayStatus {
    FX_PLAYING = 0,
    FX_STOPPED = 1
};

class FxSystemBP_c;
class Particle_c;

class FxSystem_c : public ListItem_c {
public:
    // ListItem_c m_link;
    void *m_pBlueprint;
    RwMatrix *m_pParentMatrix;
    RwMatrix m_localMatrix;
    uint8 m_nPlayStatus; // see eFxSystemPlayStatus
    uint8 m_nKillStatus; // see eFxSystemKillStatus
    uint8 m_bConstTimeSet;
    char field_53;
    int32 field_54;
    float m_fCameraDistance;
    uint16 m_nConstTime;
    uint16 m_nRateMult;
    uint16 m_nTimeMult;
    struct {
        uint8 bOwnedParentMatrix: 1;
        uint8 bLocalParticles : 1;
        uint8 bZTestEnabled : 1;
        uint8 bUnknown4 : 1;
        uint8 bUnknown5 : 1;
        uint8 bMustCreatePtrs : 1;
    } m_nFlags;
    char field_63;
    float fUnkRandom;
    CVector m_vecVelAdd;
    void *m_pBounding;
    void **m_pPrimsPtrList;
    char m_fireAudio[0x88]; // CAEFireAudioEntity

    CAEFireAudioEntity *GetFireAudio() { return reinterpret_cast<CAEFireAudioEntity *>(m_fireAudio); }

    FxSystem_c();
    ~FxSystem_c();
    void Play();
    void Pause();
    void Stop();
    void PlayAndKill();
    void Kill();
    void AttachToBone(CEntity* entity, int32 boneId);
    void AddParticle(RwV3d* position, RwV3d* velocity, float arg2, FxPrtMult_c* prtMult, float arg4, float brightness, float arg6, uint8 arg7);
    void AddParticle(RwMatrixTag* transform, RwV3d* position, float arg2, FxPrtMult_c* prtMult, float arg4, float arg5, float arg6, uint8 arg7);
    void EnablePrim(int32 primIndex, uint8 enable);
    void SetMatrix(RwMatrixTag* matrix);
    void SetOffsetPos(const CVector& pos);
    void AddOffsetPos(RwV3d* pos);
    void SetConstTime(uint8 arg0, float amount);
    void SetRateMult(float mult);
    void SetTimeMult(float mult);
    void SetVelAdd(RwV3d* velAdd);
    bool Init(FxSystemBP_c* arg0, RwMatrixTag* local, RwMatrixTag* parent);
    void Exit();
    void CopyParentMatrix();
    void GetCompositeMatrix(RwMatrixTag* out);
    eFxSystemPlayStatus GetPlayStatus();
    void SetLocalParticles(uint8 enable);
    uint32 ForAllParticles(void(*callback)(Particle_c *, int32, void **), void* data);
    static void UpdateBoundingBoxCB(Particle_c* particle, int32 arg1, void** data);
    void GetBoundingBox(FxBox_c* out);
    bool GetBoundingSphereWld(FxSphere_c* out);
    bool GetBoundingSphereLcl(FxSphere_c* out);
    void SetBoundingSphere(FxSphere_c* bound);
    void ResetBoundingSphere();
    void SetZTestEnable(uint8 enable);
    void SetMustCreatePrts(uint8 enable);
    void DoFxAudio(CVector posn);
    bool IsVisible();
    bool Update(RwCamera* camera, float timeDelta);
};
