/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "List_c.h"
#include "RenderWare.h"
#include "Vector.h"
#include "AEFireAudioEntity.h"

enum eFxSystemKillStatus : uint8 {
    FX_NOT_KILLED    = 0,
    FX_PLAY_AND_KILL = 1, // DESTROY_AFTER_FINISHING
    FX_KILLED        = 2,
    FX_3             = 3,
};

enum class eFxSystemPlayStatus : uint8 {
    FX_PLAYING = 0,
    FX_STOPPED = 1,
    T2         = 2,
};

class FxSystemBP_c;
class FxPrtMult_c;
class FxSphere_c;
class FxPrim_c;
class FxPrimBP_c;
class FxBox_c;
struct Particle_c;

class FxSystem_c : public ListItem_c {
public:
    FxSystemBP_c* m_SystemBP;
    RwMatrix*     m_pParentMatrix;
    RwMatrix      m_LocalMatrix;

    eFxSystemPlayStatus m_nPlayStatus;
    eFxSystemKillStatus m_nKillStatus;

    uint8  m_bConstTimeSet;
    float  m_fCurrentTime;
    float  m_fCameraDistance;
    uint16 m_nConstTime;

    uint16 m_nRateMult;
    uint16 m_nTimeMult;

    uint8 m_bOwnedParentMatrix : 1;
    uint8 m_bLocalParticles : 1;
    uint8 m_bZTestEnabled : 1;
    uint8 m_bUnknown4 : 1;
    uint8 m_bUnknown5 : 1;
    uint8 m_bMustCreateParticles : 1;

    float              m_fUnkRandom;
    CVector            m_vecVelAdd;
    FxSphere_c*        m_BoundingSphere;
    FxPrim_c**         m_Prims;
    CAEFireAudioEntity m_FireAudio;

public:
    static void InjectHooks();

    FxSystem_c();
    ~FxSystem_c();
    FxSystem_c* Constructor();
    FxSystem_c* Destructor();

    bool Init(FxSystemBP_c* systemBP, RwMatrix* local, RwMatrix* parent);
    void Exit();

    void Play();
    void PlayAndKill();
    void Kill();
    void Pause();
    void Stop();

    void AttachToBone(CEntity* entity, ePedBones boneId);

    void AddParticle(CVector* position, CVector* velocity, float arg2, FxPrtMult_c* prtMult, float arg4, float brightness, float arg6, bool bLocalParticles);
    void AddParticle(RwMatrix* transform, CVector* velocity, float a4, FxPrtMult_c* prtMult, float a6, float brightness, float a8, bool a9);

    void EnablePrim(int32 primIndex, bool enable);
    void SetMatrix(RwMatrix* matrix);
    void SetOffsetPos(const CVector& pos);
    void AddOffsetPos(CVector* pos);
    void SetConstTime(uint8 time, float amount);
    void SetRateMult(float mult);
    void SetTimeMult(float mult);
    void SetVelAdd(CVector* velocity);
    void CopyParentMatrix();
    void GetCompositeMatrix(RwMatrix* out);
    eFxSystemPlayStatus GetPlayStatus() const;

    uint32 ForAllParticles(void(*callback)(Particle_c *, int32, FxBox_c**), FxBox_c* data);
    static void UpdateBoundingBoxCB(Particle_c* particle, int32 arg1, FxBox_c** data);

    void GetBoundingBox(FxBox_c* out);
    bool GetBoundingSphereWld(FxSphere_c* out);
    bool GetBoundingSphereLcl(FxSphere_c* out);
    void SetBoundingSphere(FxSphere_c* sphere);
    void ResetBoundingSphere();

    void SetLocalParticles(bool enable);
    void SetZTestEnable(bool enable);
    void SetMustCreatePrts(bool enable);

    bool IsVisible();

    void DoFxAudio(CVector posn);
    bool Update(RwCamera* camera, float timeDelta);

public:
    std::span<FxPrim_c*> GetPrims();

    template<typename T>
    static void KillAndClear(T*& fx) requires std::is_base_of_v<FxSystem_c, T> {
        fx->Kill();
        fx = nullptr;
    }

    template<typename T>
    static void SafeKillAndClear(T*& fx) requires std::is_base_of_v<FxSystem_c, T> {
        if (fx) {
            KillAndClear(fx);
        }
    }
};
