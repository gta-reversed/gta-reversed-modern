#pragma once

#include "Vector.h"

class CEntity;
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

    static inline int16& m_scanCode = *(int16*)0xC03980;
    static inline CPlantLocTri* m_UnusedLocTriListHead = *(CPlantLocTri**)0xC03984;
    static inline CPlantLocTri* (&m_CloseLocTriListHead)[4] = *(CPlantLocTri*(*)[4])0xC03988;
    static inline CPlantColEntEntry* m_UnusedColEntListHead = *(CPlantColEntEntry**)0xC03998;
    static inline CPlantColEntEntry* m_CloseColEntListHead = *(CPlantColEntEntry**)0xC0399C;
    static inline CRGBA& m_AmbientColor = *(CRGBA*)0xC03A44;
    static inline CPlantLocTri (&m_LocTrisTab)[256] = *(CPlantLocTri(*)[256])0xC03A48;
    static inline CPlantColEntEntry (&m_ColEntCacheTab)[40] = *(CPlantColEntEntry(*)[40])0xC08E48;

public:
    static void InjectHooks();

    static bool Initialise();
    static void Shutdown();
    static bool ReloadConfig();

    static void MoveColEntToList(CPlantColEntEntry** a1, CPlantColEntEntry** a2, CPlantColEntEntry* a3);
    static void MoveLocTriToList(CPlantLocTri** a1, CPlantLocTri** a2, CPlantLocTri* a3);
    static void SetPlantFriendlyFlagInAtomicMI(CAtomicModelInfo*);

    static void Update(const CVector& cameraPosition);
    static void UpdateAmbientColor();
    static void PreUpdateOnceForNewCameraPos(const CVector&);
    static float CalculateWindBending();

    static void Render();

private:
    static void _ColEntityCache_Add(CEntity* entity, bool a2);
    static void _ColEntityCache_FindInCache(CEntity* entity);
    static void _ColEntityCache_Remove(CEntity* entity);
    static void _ColEntityCache_Update(const CVector& cameraPos, bool last);

    static void _ProcessEntryCollisionDataSections(CPlantColEntEntry* entry, const CVector& center, int32 a3);
    static void _ProcessEntryCollisionDataSections_AddLocTris(CPlantColEntEntry*, const CVector&, int32, int32, int32);
    static void _ProcessEntryCollisionDataSections_RemoveLocTris(CPlantColEntEntry*, const CVector&, int32, int32, int32);

    static void _UpdateLocTris(const CVector& center, int32);

    static bool DbgCountCachedEntities(uint32*);
    static bool DbgCountLocTrisAndPlants(uint32, uint32*, uint32*);
    static bool DbgRenderCachedEntities(uint32*);
    static bool DbgRenderLocTris();

    static void IncrementScanCode() { ++m_scanCode; } // 0x5DB2D0
};
