#pragma once

#include "Base.h"

#include "rwplcore.h" // RwMatrix

#include "Vector.h"
#include "NodeAddress.h"
#include "InteriorInfo_t.h"
#include "List_c.h"
#include "ListItem_c.h"
#include "./FurnitureEntity_c.h"

class CEntity;
class CObject;
class Furniture_c;
class InteriorGroup_c;
struct tEffectInterior;

struct GoToPt_t {
    int8    tileX, tileY;
    int8    link1, link2;
    CVector pos;
};
VALIDATE_SIZE(GoToPt_t, 0x10);

enum class eInteriorType {
    SHOP       = 0,
    OFFICE     = 1,
    LOUNGE     = 2,
    BEDROOM    = 3,
    KITCHEN    = 4,
    BATHROOM   = 5,
    OFFLICENSE = 6,
    HOTELROOM  = 7,
    MISC       = 8,
    TESTROOM   = 99, // NOTE: This isn't included in `NUM`

    //
    // Add new above this line
    //
    NUM = 9,
};
using eInteriorTypeS32 = notsa::WEnumS32<eInteriorType>;
using eInteriorTypeS8 = notsa::WEnumS8<eInteriorType>;

class Interior_c : public ListItem_c<Interior_c> {
    static constexpr size_t NUM_TILES_PER_AXIS = 30;
    static constexpr size_t NUM_TILES = sq(NUM_TILES_PER_AXIS);

    template<std::integral T>
    using Tiles = T[NUM_TILES_PER_AXIS][NUM_TILES_PER_AXIS]; //notsa::mdarray<uint8, NUM_TILES_PER_AXIS, NUM_TILES_PER_AXIS>;
public:
    static void InjectHooks();

    Interior_c() = default;
    ~Interior_c() = default; // 0x591360

    bool Init(const CVector& pos); // always true
    void Exit();
    void Furnish();
    void UnFurnish();

    /*!
     * @brief Get corners of a furniture's bounding box
     * @param fe The furniture to get the bb of
     * @param corners The 4 corners of the the bounding box (counter-clockwise, from top left): top left, bottom left, bottom right, top right
     * @return 
    */
    bool GetBoundingBox(FurnitureEntity_c* fe, CVector(&corners)[4]);
    void FindBoundingBox(
        int32 x,     int32 y,
        int32* minX, int32* maxX,
        int32* minY, int32* maxY,
        Tiles<int32>* tileInfo
    );
    void AddGotoPt(int32 a, int32 b, float a3, float a4);
    void CalcExitPts();
    bool AddInteriorInfo(int32 actionType, float offsetX, float offsetY, int32 direction, CEntity* entityIgnoredCollision);
    bool IsPtInside(const CVector& pt, CVector bias = {});
    void AddPickups();
    bool IsVisible();
    void CalcMatrix(const CVector& pos);
    auto GetDoorNodeAddress() const { return m_DoorAddr; }

    //
    // Bedroom
    //
    void FurnishBedroom();
    CObject* Bedroom_AddTableItem(int32 a2, int32 a3, int32 a4, int32 a5, int32 a6, int32 a7);

    //
    // Kitchen
    //
    void FurnishKitchen();
    CObject* Kitchen_FurnishEdges();

    //
    // Lounge
    //
    void FurnishLounge();
    CObject* Lounge_AddTV(int32 a2, int32 a3, int32 a4, int32 a5);
    CObject* Lounge_AddHifi(int32 a2, int32 a3, int32 a4, int32 a5);
    void Lounge_AddChairInfo(int32 a2, int32 a3, CEntity* entityIgnoredCollision);
    void Lounge_AddSofaInfo(int32 sitType, int32 offsetX, CEntity* entityIgnoredCollision);

    //
    // Office
    //
    void FurnishOffice();
    bool Office_PlaceEdgeFillers(int32 arg0, int32 a2, int32 a3, int32 a6, int32);
    int32 Office_PlaceDesk(int32 a3, int32 arg4, int32 offsetY, int32 a5, uint8 a6, int32 b);
    int32 Office_PlaceEdgeDesks(int32 a2, int32 a3, int32 a4, int32 a5, int32 a6);
    void Office_FurnishEdges();
    int32 Office_PlaceDeskQuad(int32 a2, int32 a3, int32 a4, int32 a5);
    int32 Office_FurnishCenter();

    //
    // Shop
    //
    void FurnishShop(eInteriorTypeS32 intType);
    void Shop_FurnishEdges();
    void Shop_FurnishAisles();
    int8 Shop_Place3PieceUnit(int32 a2, int32 a3, int32 a4, int32 a5, int32 a6);
    int32 Shop_PlaceEdgeUnits(int32 a2, int32 a3, int32 a4, int32 a5);
    int32 Shop_PlaceCounter(uint8 a2);
    void Shop_PlaceFixedUnits();
    void Shop_FurnishCeiling();
    void Shop_AddShelfInfo(int32 a2, int32 a3, int32 a5);

    //
    // Furnitures
    //
    void PlaceFurniture(Furniture_c* a1, int32 a2, int32 a3, float a4, int32 a5, int32 a6, int32* a7, int32* a8, uint8 a9);
    void PlaceFurnitureOnWall(int32 furnitureGroupId, int32 furnitureSubgroupId, int32 furnitureId, float a5, int32 a6, int32 a7, int32 a8, int32 a9, int32* a10, int32* a11,
                              int32* a12, int32* a13, int32* a14, int32* a15);
    void PlaceFurnitureInCorner(int32 furnitureGroupId, int32 furnitureSubgroupId, int32 id, float a4, int32 a5, int32 a6, int32 a2, int32* a9, int32* a10, int32* a11, int32* a12,
                                int32* a13);
    CObject* PlaceObject(uint8 isStealable, Furniture_c* furniture, float offsetX, float offsetY, float offsetZ, float rotationZ);
    FurnitureEntity_c* GetFurnitureEntity(CEntity*);

    //
    // Tiles
    //
    void ResetTiles();
    int8 CheckTilesEmpty(int32 a1, int32 a2, int32 a3, int32 a4, uint8 a5);
    void SetTilesStatus(int32 a, int32 b, int32 a3, int32 a4, int32 a5, int8 a6);
    void SetCornerTiles(int32 a4, int32 a3, int32 a5, uint8 a6);
    int32 GetTileStatus(int32 x, int32 y);
    int32 GetNumEmptyTiles(int32 a2, int32 a3, int32 a4, int32 a5);
    int32 GetRandomTile(int32 a2, int32* a3, int32* a4);
    CVector* GetTileCentre(float offsetX, float offsetY, CVector* pointsIn);
    bool FindEmptyTiles(int32 a3, int32 a4, int32* arg8, int32* a5);

public:
    int32                                                         m_ID{};                  // 0x8
    InteriorGroup_c*                                              m_Group{};               // 0xC
    int32                                                         m_AreaCode{};            // 0x10
    tEffectInterior*                                              m_Props{};               // 0x14
    RwMatrix                                                      m_Mat{};                 // 0x18
    float                                                         m_DistSq{};              // 0x58
    TList_c<FurnitureEntity_c>                                    m_FurnitureEntityList{}; // 0x5C
    Tiles<uint8>                                                  m_Tiles{};               // 0x68
    CNodeAddress                                                  m_ExitAddr{};            // 0x3EC
    CNodeAddress                                                  m_DoorAddr{};            // 0x3F0
    CVector                                                       m_ExitPos{};             // 0x3F4
    CVector                                                       m_DoorPos{};             // 0x400
    int8                                                          m_NumGoToPts{};          // 0x40C
    int8                                                          m_NumIntInfo{};          // 0x40D
    GoToPt_t                                                      m_GoToPts[16]{};         // 0x410
    GoToPt_t                                                      m_ExitPts[8]{};          // 0x510
    InteriorInfo_t                                                m_IntInfos[16]{};        // 0x590
    int8                                                          m_ShopSubType{};         // 0x790
    int8                                                          m_StyleA{};              // 0x791
    int8                                                          m_StyleB{};              // 0x792
};
VALIDATE_SIZE(Interior_c, 0x794);
