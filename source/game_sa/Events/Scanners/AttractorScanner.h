/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskTimer.h"
#include "2dEffect.h"

class CEntity;

class CAttractorScanner {
public:
    static void InjectHooks();

    //static int8 GetClosestAttractorOfType(CVector const& point, float radius, int32 , int32 , charconst* String1, bool , C2dEffectconst* , C2dEffect*& , CEntity*& );

    void      Clear();
    void      AddEffect(C2dEffectPedAttractor* fx, CEntity* e, const CPed& ped);
    CPtrNode* ScanForAttractorsInPtrList(CPtrList&, const CPed&);
    void      ScanForAttractorsInRange(const CPed& a2);

    auto GetPreviousEffect() const { return m_PreviousEffect; }
    void SetPreviousEffect(C2dEffectPedAttractor* fx) { m_PreviousEffect = fx; }

private:
    bool                   m_bActivated{};
    CTaskTimer             m_Timer{};
    C2dEffectPedAttractor* m_PreviousEffect{};
    CEntity*               m_PreviousEntity{};
    CEntity*               m_Entities[PED_ATTRACTOR_NUM]{};
    C2dEffectPedAttractor* m_Effects[PED_ATTRACTOR_NUM]{};
    float                  m_MinDistSq[PED_ATTRACTOR_NUM]{};
};
VALIDATE_SIZE(CAttractorScanner, 0x90);
