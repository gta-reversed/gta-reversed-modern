#pragma once

#include "Base.h"

#include "rwplcore.h" // RwMatrix

#include "Vector.h"
#include "NodeAddress.h"
#include "tEffectFurniture.h"
#include "InteriorInfo_t.h"
#include "List_c.h"
#include "ListItem_c.h"

class CEntity;
class CObject;
class FurnitureEntity_c; // TODO
class Furniture_c;

class Interior_c : public ListItem_c {
public:
    int32             m_interiorId;
    int32             m_pGroup;
    int32             m_areaCode;
    tEffectFurniture* m_furnitureEffect;
    RwMatrix          m_matrix;
    int32             field_58;
    List_c            m_list;
    char              field_68[900];
    int16             field_3EC;
    int16             field_3EE;
    CNodeAddress      m_nodeAddress;
    int16             field_3F4;
    int16             field_3F6;
    int32             field_3F8;
    int32             field_3FC;
    CVector           m_position;
    int8              field_40C;
    int8              m_interiorInfosCount;
    int32             field_412;
    int32             field_416;
    int32             field_41A;
    int32             field_41E;
    int32             field_422;
    int32             field_426;
    int32             field_42A;
    int32             field_42E;
    int32             field_432;
    char              gap436[346];
    InteriorInfo_t    m_interiorInfos[16];
    int8              m_furnitureGroupId;
    int8              m_furnitureId;
    int8              field_792;
    int8              field_793;

public:
    static void InjectHooks();

    Interior_c();
    ~Interior_c() = default; // 0x591360

    int32 Init(CVector* a2);
    void Exit();

    CObject* Bedroom_AddTableItem(int32 a2, int32 a3, int32 a4, int32 a5, int32 a6, int32 a7);
    void FurnishBedroom();
    CObject* Kitchen_FurnishEdges();
    void FurnishKitchen();
    CObject* Lounge_AddTV(int32 a2, int32 a3, int32 a4, int32 a5);
    CObject* Lounge_AddHifi(int32 a2, int32 a3, int32 a4, int32 a5);
    void Lounge_AddChairInfo(int32 a2, int32 a3, CEntity* entityIgnoredCollision);
    void Lounge_AddSofaInfo(int32 sitType, int32 offsetX, CEntity* entityIgnoredCollision);
    void FurnishLounge();
    bool Office_PlaceEdgeFillers(int32 arg0, int32 a2, int32 a3, int32 a6, int32);
    int32 Office_PlaceDesk(int32 a3, int32 arg4, int32 offsetY, int32 a5, uint8 a6, int32 b);
    int32 Office_PlaceEdgeDesks(int32 a2, int32 a3, int32 a4, int32 a5, int32 a6);
    void Office_FurnishEdges();
    int32 Office_PlaceDeskQuad(int32 a2, int32 a3, int32 a4, int32 a5);
    int32 Office_FurnishCenter();
    void FurnishOffice();
    int8 Shop_Place3PieceUnit(int32 a2, int32 a3, int32 a4, int32 a5, int32 a6);
    int32 Shop_PlaceEdgeUnits(int32 a2, int32 a3, int32 a4, int32 a5);
    int32 Shop_PlaceCounter(uint8 a2);
    void Shop_PlaceFixedUnits();
    void Shop_FurnishCeiling();
    void Shop_AddShelfInfo(int32 a2, int32 a3, int32 a5);
    void Shop_FurnishEdges();
    int8 GetBoundingBox(FurnitureEntity_c* entity, CVector* a3);
    void ResetTiles();
    CObject* PlaceObject(uint8 isStealable, Furniture_c* furniture, float offsetX, float offsetY, float offsetZ, float rotationZ);
    ListItem_c* GetFurnitureEntity(CEntity*);
    bool IsPtInside(CVector* a2, float a3, float a4, float a5);
    void CalcMatrix(CVector* translation);
    void Furnish();
    void Unfurnish();
    int8 CheckTilesEmpty(int32 a1, int32 a2, int32 a3, int32 a4, uint8 a5);
    void SetTilesStatus(int32 a, int32 b, int32 a3, int32 a4, int32 a5, int8 a6);
    void SetCornerTiles(int32 a4, int32 a3, int32 a5, uint8 a6);
    int32 GetTileStatus(int32 x, int32 y);
    int32 GetNumEmptyTiles(int32 a2, int32 a3, int32 a4, int32 a5);
    int32 GetRandomTile(int32 a2, int32* a3, int32* a4);
    void Shop_FurnishAisles();
    CVector* GetTileCentre(float offsetX, float offsetY, CVector* pointsIn);
    void AddGotoPt(int32 a, int32 b, float a3, float a4);
    bool AddInteriorInfo(int32 actionType, float offsetX, float offsetY, int32 direction, CEntity* entityIgnoredCollision);
    void AddPickups();
    void FindBoundingBox(int32, int32, int32*, int32*, int32*, int32*, int32*);
    void CalcExitPts();
    bool IsVisible();
    void PlaceFurniture(Furniture_c* a1, int32 a2, int32 a3, float a4, int32 a5, int32 a6, int32* a7, int32* a8, uint8 a9);
    void PlaceFurnitureOnWall(int32 furnitureGroupId, int32 furnitureSubgroupId, int32 furnitureId, float a5, int32 a6, int32 a7, int32 a8, int32 a9, int32* a10, int32* a11,
                              int32* a12, int32* a13, int32* a14, int32* a15);
    void PlaceFurnitureInCorner(int32 furnitureGroupId, int32 furnitureSubgroupId, int32 id, float a4, int32 a5, int32 a6, int32 a2, int32* a9, int32* a10, int32* a11, int32* a12,
                                int32* a13);
    bool FindEmptyTiles(int32 a3, int32 a4, int32* arg8, int32* a5);
    void FurnishShop(int32 a2);
};
VALIDATE_SIZE(Interior_c, 0x794);
