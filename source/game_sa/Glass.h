#pragma once

#include "FallingGlassPane.h"
#include "Vector2D.h"
#include "Vector.h"

class CVehicle;
class CEntity;
class CPtrList;

class CGlass {
public:
    static CVector2D (&PanePolyPositions)[4][3];
    static int32& ReflectionPolyVertexBaseIdx;
    static int32& ReflectionPolyIndexBaseIdx;
    static int32& ShatteredVerticesBaseIdx;
    static int32& ShatteredIndicesBaseIdx;
    static uint32& NumHiLightPolyVertices;
    static int32& NumHiLightPolyIndices;
    static CVector2D (&PanePolyCenterPositions)[5];
    static int32 (&apEntitiesToBeRendered)[1];
    static int32& NumGlassEntities;
    static CFallingGlassPane (&aGlassPanes)[44];
    static int32& LastColCheckMS;

public:
    static void InjectHooks();

    static void Init();
    static bool HasGlassBeenShatteredAtCoors(CVector pos);
    static void CarWindscreenShatters(CVehicle* pVeh);
    static void WasGlassHitByBullet(CEntity* pObj, CVector hitPos);
    static void WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, bool a5);
    static void GeneratePanesForWindow(uint32 type, CVector bl_pos, CVector fwd_unnorm, CVector right_unnorm, CVector move_speed, CVector center, float velocityo_center_drag_coeff,
                                       bool bShatter, bool size_max_1, int32 num_sections, bool a11);
    static void Update();
    static void Render();
    static void FindWindowSectorList(CPtrList& objList, float& outDist, CEntity*& outEntity, CVector point);
    static void RenderReflectionPolys();
    static void RenderShatteredPolys();
    static void RenderHiLightPolys();
    static uint8 CalcAlphaWithNormal(CVector* normal);
    static void AskForObjectToBeRenderedInGlass(CEntity* a1);
    static CFallingGlassPane* FindFreePane();
    static void WindowRespondsToSoftCollision(CEntity* pEntity, float fDamageIntensity);
    static void BreakGlassPhysically(CVector pos, float radius);
};
