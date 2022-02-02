#pragma once

#include "Vector.h"

class CEntity;
class CVehicle;
class CObject;
class CPtrList;

class CGlass {
public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void AskForObjectToBeRenderedInGlass(CEntity* pEntity);
    static void BreakGlassPhysically(CVector a1, float a2);
    static void CalcAlphaWithNormal(CVector* a1);
    static void CarWindscreenShatters(CVehicle* a1);
    static void FindFreePane();
    static void FindWindowSectorList(CPtrList& a1, float* a2, CEntity** a3, float a4, float a5, float a6);
    static void GeneratePanesForWindow(uint32 a1, CVector a2, CVector a3, CVector a4, CVector a5, CVector a6, float a7, bool a8, bool a9, int32 a10, bool a11);
    static void HasGlassBeenShatteredAtCoors(CVector a1);
    static void Render();
    static void RenderHiLightPolys();
    static void RenderReflectionPolys();
    static void RenderShatteredPolys();
    static void WasGlassHitByBullet(CEntity* a1, CVector a2);
    static void WindowRespondsToExplosion(CEntity* a1, const CVector& a2);
    static void WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, int32 bUnknown);
    static void WindowRespondsToSoftCollision(CObject* pEntity, float fDamageIntensity);
};
