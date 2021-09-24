#pragma once

#include "Vector.h"

class CPlantColEntEntry;
class CPlantLocTri;

class CPlantMgr {
public:
    static RwTexture* (&PC_PlantTextureTab0)[4];
    static RwTexture* (&PC_PlantTextureTab1)[4];
    static RwTexture* (&PC_PlantTextureTab2)[4];
    static RwTexture* (&PC_PlantTextureTab3)[4];

    static RpAtomic* (&PC_PlantModelsTab0)[4];
    static RpAtomic* (&PC_PlantModelsTab1)[4];
    static RpAtomic* (&PC_PlantModelsTab2)[4];
    static RpAtomic* (&PC_PlantModelsTab3)[4];

public:
    static void InjectHooks();

    CPlantMgr();
    ~CPlantMgr();

    static bool Initialise();
    static void Shutdown();

    static void CalculateWindBending();
    static void MoveColEntToList(CPlantColEntEntry**, CPlantColEntEntry**, CPlantColEntEntry*);
    static void MoveLocTriToList(CPlantLocTri**, CPlantLocTri**, CPlantLocTri*);
    static void PreUpdateOnceForNewCameraPos(const CVector&);
    static bool ReloadConfig();
    static void Render();
    static void SetPlantFriendlyFlagInAtomicMI(CAtomicModelInfo*);
    static void Update(const CVector& cameraPosition);
    static void UpdateAmbientColor();

private:
    // From Android

    static void _ColEntityCache_Add(CEntity*, uint8);
    static void _ColEntityCache_FindInCache(CEntity*);
    static void _ColEntityCache_Remove(CEntity*);
    static void _ColEntityCache_Update(const CVector&, uint8);

    static void _ProcessEntryCollisionDataSections(CPlantColEntEntry*, const CVector&, int32);
    static void _ProcessEntryCollisionDataSections_AddLocTris(CPlantColEntEntry*, const CVector&, int32, int32, int32);
    static void _ProcessEntryCollisionDataSections_RemoveLocTris(CPlantColEntEntry*, const CVector&, int32, int32, int32);

    static void _UpdateLocTris(const CVector&, int32);

    static void DbgCountCachedEntities(uint32*);
    static void DbgCountLocTrisAndPlants(uint32, uint32*, uint32*);
    static void DbgRenderCachedEntities(uint32*);
    static void DbgRenderLocTris();
};
