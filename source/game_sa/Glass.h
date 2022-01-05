#pragma once

#include "Vector2D.h"
#include "Vector.h"
#include "FallingGlassPane.h"

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
    static void WasGlassHitByBullet(CEntity* entity, CVector hitPos);
    static void WindowRespondsToCollision(CEntity* pEntity, float fDamageIntensity, CVector vecMoveSpeed, CVector vecPoint, bool max1PaneSection);
    static void GeneratePanesForWindow(uint32 type, CVector pos, CVector fwd, CVector right, CVector velocity, CVector center, float velocityCenterDragCoeff,
                                       bool bShatter, bool numSectionsMax1, int32 numSections, bool unk);
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
