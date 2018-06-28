/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "List_c.h"
#include "RenderWare.h"
#include "CVector.h"
#include "CAEFireAudioEntity.h"
#include "FxPrtMult_c.h"
#include "FxSphere_c.h"
#include "FxBox_c.h"

enum eFxSystemKillStatus {
    FX_NOT_KILLED = 0,
    FX_PLAY_AND_KILL = 1,
    FX_KILLED = 2
};

enum eFxSystemPlayStatus {
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
    unsigned char m_nPlayStatus; // see eFxSystemPlayStatus
    unsigned char m_nKillStatus; // see eFxSystemKillStatus
    unsigned char m_bConstTimeSet;
    char field_53;
    int field_54;
    float m_fCameraDistance;
    unsigned short m_nConstTime;
    unsigned short m_nRateMult;
    unsigned short m_nTimeMult;
    struct {
        unsigned char bOwnedParentMatrix: 1;
        unsigned char bLocalParticles : 1;
        unsigned char bZTestEnabled : 1;
        unsigned char bUnknown4 : 1;
        unsigned char bUnknown5 : 1;
        unsigned char bMustCreatePtrs : 1;
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
    void AttachToBone(CEntity* entity, int boneId);
    void AddParticle(RwV3d* position, RwV3d* velocity, float arg2, FxPrtMult_c* prtMult, float arg4, float brightness, float arg6, unsigned char arg7);
    void AddParticle(RwMatrixTag* transform, RwV3d* position, float arg2, FxPrtMult_c* prtMult, float arg4, float arg5, float arg6, unsigned char arg7);
    void EnablePrim(int primIndex, unsigned char enable);
    void SetMatrix(RwMatrixTag* matrix);
    void SetOffsetPos(RwV3d* pos);
    void AddOffsetPos(RwV3d* pos);
    void SetConstTime(unsigned char arg0, float amount);
    void SetRateMult(float mult);
    void SetTimeMult(float mult);
    void SetVelAdd(RwV3d* velAdd);
    bool Init(FxSystemBP_c* arg0, RwMatrixTag* local, RwMatrixTag* parent);
    void Exit();
    void CopyParentMatrix();
    void GetCompositeMatrix(RwMatrixTag* out);
    void GetPlayStatus();
    void SetLocalParticles(unsigned char enable);
    unsigned int ForAllParticles(void(*callback)(Particle_c *, int, void **), void* data);
    static void UpdateBoundingBoxCB(Particle_c* particle, int arg1, void** data);
    void GetBoundingBox(FxBox_c* out);
    bool GetBoundingSphereWld(FxSphere_c* out);
    bool GetBoundingSphereLcl(FxSphere_c* out);
    void SetBoundingSphere(FxSphere_c* bound);
    void ResetBoundingSphere();
    void SetZTestEnable(unsigned char enable);
    void SetMustCreatePrts(unsigned char enable);
    void DoFxAudio(CVector posn);
    bool IsVisible();
    bool Update(RwCamera* camera, float timeDelta);
};
