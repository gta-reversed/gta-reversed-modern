#include "StdInc.h"

SurfaceInfos_c* g_surfaceInfos = reinterpret_cast<SurfaceInfos_c*>(0xB79538);
char* SurfaceInfos_c::cDefaultName = reinterpret_cast<char*>(0x85C658); // "DEFAULT/0"

void SurfaceInfos_c::InjectHooks()
{
    RH_ScopedClass(SurfaceInfos_c);
    RH_ScopedCategoryRoot();

    RH_ScopedInstall(GetSurfaceIdFromName, 0x55D220);
    RH_ScopedInstall(Init, 0x55F420);

    RH_ScopedInstall(GetAdhesionGroup, 0x55E5C0);
    RH_ScopedInstall(GetTyreGrip, 0x55E5E0);
    RH_ScopedInstall(GetWetMultiplier, 0x55E600);
    RH_ScopedInstall(GetSkidmarkType, 0x55E630);
    RH_ScopedInstall(GetFrictionEffect, 0x55E650);
    RH_ScopedInstall(GetBulletFx, 0x55E670);
    RH_ScopedInstall(IsSoftLanding, 0x55E690);
    RH_ScopedInstall(IsSeeThrough, 0x55E6B0);
    RH_ScopedInstall(IsShootThrough, 0x55E6D0);
    RH_ScopedInstall(IsSand, 0x55E6F0);
    RH_ScopedInstall(IsWater, 0x55E710);
    RH_ScopedInstall(IsShallowWater, 0x55E730);
    RH_ScopedInstall(IsBeach, 0x55E750);
    RH_ScopedInstall(IsSteepSlope, 0x55E770);
    RH_ScopedInstall(IsGlass, 0x55E790);
    RH_ScopedInstall(IsStairs, 0x55E7B0);
    RH_ScopedInstall(IsSkateable, 0x55E7D0);
    RH_ScopedInstall(IsPavement, 0x55E7F0);
    RH_ScopedInstall(GetRoughness, 0x55E810);
    RH_ScopedInstall(GetFlammability, 0x55E830);
    RH_ScopedInstall(CreatesSparks, 0x55E850);
    RH_ScopedInstall(CantSprintOn, 0x55E870);
    RH_ScopedInstall(LeavesFootsteps, 0x55E890);
    RH_ScopedInstall(ProducesFootDust, 0x55E8B0);
    RH_ScopedInstall(MakesCarDirty, 0x55E8D0);
    RH_ScopedInstall(MakesCarClean, 0x55E8F0);
    RH_ScopedInstall(CreatesWheelGrass, 0x55E910);
    RH_ScopedInstall(CreatesWheelGravel, 0x55E930);
    RH_ScopedInstall(CreatesWheelMud, 0x55E950);
    RH_ScopedInstall(CreatesWheelDust, 0x55E970);
    RH_ScopedInstall(CreatesWheelSand, 0x55E990);
    RH_ScopedInstall(CreatesWheelSpray, 0x55E9B0);
    RH_ScopedInstall(CreatesPlants, 0x55E9D0);
    RH_ScopedInstall(CreatesObjects, 0x55E9F0);
    RH_ScopedInstall(CanClimb, 0x55EA10);
    RH_ScopedInstall(IsAudioConcrete, 0x55EA30);
    RH_ScopedInstall(IsAudioGrass, 0x55EA50);
    RH_ScopedInstall(IsAudioSand, 0x55EA70);
    RH_ScopedInstall(IsAudioGravel, 0x55EA90);
    RH_ScopedInstall(IsAudioWood, 0x55EAB0);
    RH_ScopedInstall(IsAudioWater, 0x55EAD0);
    RH_ScopedInstall(IsAudioMetal, 0x55EAF0);
    RH_ScopedInstall(IsAudioLongGrass, 0x55EB10);
    RH_ScopedInstall(IsAudioTile, 0x55EB30);
    RH_ScopedInstall(GetAdhesiveLimit, 0x55EB50);
}

void SurfaceInfos_c::LoadAdhesiveLimits()
{
    return plugin::CallMethod<0x55D0E0, SurfaceInfos_c*>(this);
}

uint32 SurfaceInfos_c::GetSurfaceIdFromName(char* cName)
{
    if (!strcmp(cName, SurfaceInfos_c::cDefaultName))
        return SURFACE_DEFAULT;
    if (!strcmp(cName, "TARMAC"))
        return SURFACE_TARMAC;
    if (!strcmp(cName, "TARMAC_FUCKED"))
        return SURFACE_TARMAC_FUCKED;
    if (!strcmp(cName, "TARMAC_REALLYFUCKED"))
        return SURFACE_TARMAC_REALLYFUCKED;
    if (!strcmp(cName, "PAVEMENT"))
        return SURFACE_PAVEMENT;
    if (!strcmp(cName, "PAVEMENT_FUCKED"))
        return SURFACE_PAVEMENT_FUCKED;
    if (!strcmp(cName, "GRAVEL"))
        return SURFACE_GRAVEL;
    if (!strcmp(cName, "FUCKED_CONCRETE"))
        return SURFACE_FUCKED_CONCRETE;
    if (!strcmp(cName, "PAINTED_GROUND"))
        return SURFACE_PAINTED_GROUND;
    if (!strcmp(cName, "GRASS_SHORT_LUSH"))
        return SURFACE_GRASS_SHORT_LUSH;
    if (!strcmp(cName, "GRASS_MEDIUM_LUSH"))
        return SURFACE_GRASS_MEDIUM_LUSH;
    if (!strcmp(cName, "GRASS_LONG_LUSH"))
        return SURFACE_GRASS_LONG_LUSH;
    if (!strcmp(cName, "GRASS_SHORT_DRY"))
        return SURFACE_GRASS_SHORT_DRY;
    if (!strcmp(cName, "GRASS_MEDIUM_DRY"))
        return SURFACE_GRASS_MEDIUM_DRY;
    if (!strcmp(cName, "GRASS_LONG_DRY"))
        return SURFACE_GRASS_LONG_DRY;
    if (!strcmp(cName, "GOLFGRASS_ROUGH"))
        return SURFACE_GOLFGRASS_ROUGH;
    if (!strcmp(cName, "GOLFGRASS_SMOOTH"))
        return SURFACE_GOLFGRASS_SMOOTH;
    if (!strcmp(cName, "STEEP_SLIDYGRASS"))
        return SURFACE_STEEP_SLIDYGRASS;
    if (!strcmp(cName, "STEEP_CLIFF"))
        return SURFACE_STEEP_CLIFF;
    if (!strcmp(cName, "FLOWERBED"))
        return SURFACE_FLOWERBED;
    if (!strcmp(cName, "MEADOW"))
        return SURFACE_MEADOW;
    if (!strcmp(cName, "WASTEGROUND"))
        return SURFACE_WASTEGROUND;
    if (!strcmp(cName, "WOODLANDGROUND"))
        return SURFACE_WOODLANDGROUND;
    if (!strcmp(cName, "VEGETATION"))
        return SURFACE_VEGETATION;
    if (!strcmp(cName, "MUD_WET"))
        return SURFACE_MUD_WET;
    if (!strcmp(cName, "MUD_DRY"))
        return SURFACE_MUD_DRY;
    if (!strcmp(cName, "DIRT"))
        return SURFACE_DIRT;
    if (!strcmp(cName, "DIRTTRACK"))
        return SURFACE_DIRTTRACK;
    if (!strcmp(cName, "SAND_DEEP"))
        return SURFACE_SAND_DEEP;
    if (!strcmp(cName, "SAND_MEDIUM"))
        return SURFACE_SAND_MEDIUM;
    if (!strcmp(cName, "SAND_COMPACT"))
        return SURFACE_SAND_COMPACT;
    if (!strcmp(cName, "SAND_ARID"))
        return SURFACE_SAND_ARID;
    if (!strcmp(cName, "SAND_MORE"))
        return SURFACE_SAND_MORE;
    if (!strcmp(cName, "SAND_BEACH"))
        return SURFACE_SAND_BEACH;
    if (!strcmp(cName, "CONCRETE_BEACH"))
        return SURFACE_CONCRETE_BEACH;
    if (!strcmp(cName, "ROCK_DRY"))
        return SURFACE_ROCK_DRY;
    if (!strcmp(cName, "ROCK_WET"))
        return SURFACE_ROCK_WET;
    if (!strcmp(cName, "ROCK_CLIFF"))
        return SURFACE_ROCK_CLIFF;
    if (!strcmp(cName, "WATER_RIVERBED"))
        return SURFACE_WATER_RIVERBED;
    if (!strcmp(cName, "WATER_SHALLOW"))
        return SURFACE_WATER_SHALLOW;
    if (!strcmp(cName, "CORNFIELD"))
        return SURFACE_CORNFIELD;
    if (!strcmp(cName, "HEDGE"))
        return SURFACE_HEDGE;
    if (!strcmp(cName, "WOOD_CRATES"))
        return SURFACE_WOOD_CRATES;
    if (!strcmp(cName, "WOOD_SOLID"))
        return SURFACE_WOOD_SOLID;
    if (!strcmp(cName, "WOOD_THIN"))
        return SURFACE_WOOD_THIN;
    if (!strcmp(cName, "GLASS"))
        return SURFACE_GLASS;
    if (!strcmp(cName, "GLASS_WINDOWS_LARGE"))
        return SURFACE_GLASS_WINDOWS_LARGE;
    if (!strcmp(cName, "GLASS_WINDOWS_SMALL"))
        return SURFACE_GLASS_WINDOWS_SMALL;
    if (!strcmp(cName, "EMPTY1"))
        return SURFACE_EMPTY1;
    if (!strcmp(cName, "EMPTY2"))
        return SURFACE_EMPTY2;
    if (!strcmp(cName, "GARAGE_DOOR"))
        return SURFACE_GARAGE_DOOR;
    if (!strcmp(cName, "THICK_METAL_PLATE"))
        return SURFACE_THICK_METAL_PLATE;
    if (!strcmp(cName, "SCAFFOLD_POLE"))
        return SURFACE_SCAFFOLD_POLE;
    if (!strcmp(cName, "LAMP_POST"))
        return SURFACE_LAMP_POST;
    if (!strcmp(cName, "METAL_GATE"))
        return SURFACE_METAL_GATE;
    if (!strcmp(cName, "METAL_CHAIN_FENCE"))
        return SURFACE_METAL_CHAIN_FENCE;
    if (!strcmp(cName, "GIRDER"))
        return SURFACE_GIRDER;
    if (!strcmp(cName, "FIRE_HYDRANT"))
        return SURFACE_FIRE_HYDRANT;
    if (!strcmp(cName, "CONTAINER"))
        return SURFACE_CONTAINER;
    if (!strcmp(cName, "NEWS_VENDOR"))
        return SURFACE_NEWS_VENDOR;
    if (!strcmp(cName, "WHEELBASE"))
        return SURFACE_WHEELBASE;
    if (!strcmp(cName, "CARDBOARDBOX"))
        return SURFACE_CARDBOARDBOX;
    if (!strcmp(cName, "PED"))
        return SURFACE_PED;
    if (!strcmp(cName, "CAR"))
        return SURFACE_CAR;
    if (!strcmp(cName, "CAR_PANEL"))
        return SURFACE_CAR_PANEL;
    if (!strcmp(cName, "CAR_MOVINGCOMPONENT"))
        return SURFACE_CAR_MOVINGCOMPONENT;
    if (!strcmp(cName, "TRANSPARENT_CLOTH"))
        return SURFACE_TRANSPARENT_CLOTH;
    if (!strcmp(cName, "RUBBER"))
        return SURFACE_RUBBER;
    if (!strcmp(cName, "PLASTIC"))
        return SURFACE_PLASTIC;
    if (!strcmp(cName, "TRANSPARENT_STONE"))
        return SURFACE_TRANSPARENT_STONE;
    if (!strcmp(cName, "WOOD_BENCH"))
        return SURFACE_WOOD_BENCH;
    if (!strcmp(cName, "CARPET"))
        return SURFACE_CARPET;
    if (!strcmp(cName, "FLOORBOARD"))
        return SURFACE_FLOORBOARD;
    if (!strcmp(cName, "STAIRSWOOD"))
        return SURFACE_STAIRSWOOD;
    if (!strcmp(cName, "P_SAND"))
        return SURFACE_P_SAND;
    if (!strcmp(cName, "P_SAND_DENSE"))
        return SURFACE_P_SAND_DENSE;
    if (!strcmp(cName, "P_SAND_ARID"))
        return SURFACE_P_SAND_ARID;
    if (!strcmp(cName, "P_SAND_COMPACT"))
        return SURFACE_P_SAND_COMPACT;
    if (!strcmp(cName, "P_SAND_ROCKY"))
        return SURFACE_P_SAND_ROCKY;
    if (!strcmp(cName, "P_SANDBEACH"))
        return SURFACE_P_SANDBEACH;
    if (!strcmp(cName, "P_GRASS_SHORT"))
        return SURFACE_P_GRASS_SHORT;
    if (!strcmp(cName, "P_GRASS_MEADOW"))
        return SURFACE_P_GRASS_MEADOW;
    if (!strcmp(cName, "P_GRASS_DRY"))
        return SURFACE_P_GRASS_DRY;
    if (!strcmp(cName, "P_WOODLAND"))
        return SURFACE_P_WOODLAND;
    if (!strcmp(cName, "P_WOODDENSE"))
        return SURFACE_P_WOODDENSE;
    if (!strcmp(cName, "P_ROADSIDE"))
        return SURFACE_P_ROADSIDE;
    if (!strcmp(cName, "P_ROADSIDEDES"))
        return SURFACE_P_ROADSIDEDES;
    if (!strcmp(cName, "P_FLOWERBED"))
        return SURFACE_P_FLOWERBED;
    if (!strcmp(cName, "P_WASTEGROUND"))
        return SURFACE_P_WASTEGROUND;
    if (!strcmp(cName, "P_CONCRETE"))
        return SURFACE_P_CONCRETE;
    if (!strcmp(cName, "P_OFFICEDESK"))
        return SURFACE_P_OFFICEDESK;
    if (!strcmp(cName, "P_711SHELF1"))
        return SURFACE_P_711SHELF1;
    if (!strcmp(cName, "P_711SHELF2"))
        return SURFACE_P_711SHELF2;
    if (!strcmp(cName, "P_711SHELF3"))
        return SURFACE_P_711SHELF3;
    if (!strcmp(cName, "P_RESTUARANTTABLE"))
        return SURFACE_P_RESTUARANTTABLE;
    if (!strcmp(cName, "P_BARTABLE"))
        return SURFACE_P_BARTABLE;
    if (!strcmp(cName, "P_UNDERWATERLUSH"))
        return SURFACE_P_UNDERWATERLUSH;
    if (!strcmp(cName, "P_UNDERWATERBARREN"))
        return SURFACE_P_UNDERWATERBARREN;
    if (!strcmp(cName, "P_UNDERWATERCORAL"))
        return SURFACE_P_UNDERWATERCORAL;
    if (!strcmp(cName, "P_UNDERWATERDEEP"))
        return SURFACE_P_UNDERWATERDEEP;
    if (!strcmp(cName, "P_RIVERBED"))
        return SURFACE_P_RIVERBED;
    if (!strcmp(cName, "P_RUBBLE"))
        return SURFACE_P_RUBBLE;
    if (!strcmp(cName, "P_BEDROOMFLOOR"))
        return SURFACE_P_BEDROOMFLOOR;
    if (!strcmp(cName, "P_KIRCHENFLOOR"))
        return SURFACE_P_KIRCHENFLOOR;
    if (!strcmp(cName, "P_LIVINGRMFLOOR"))
        return SURFACE_P_LIVINGRMFLOOR;
    if (!strcmp(cName, "P_CORRIDORFLOOR"))
        return SURFACE_P_CORRIDORFLOOR;
    if (!strcmp(cName, "P_711FLOOR"))
        return SURFACE_P_711FLOOR;
    if (!strcmp(cName, "P_FASTFOODFLOOR"))
        return SURFACE_P_FASTFOODFLOOR;
    if (!strcmp(cName, "P_SKANKYFLOOR"))
        return SURFACE_P_SKANKYFLOOR;
    if (!strcmp(cName, "P_MOUNTAIN"))
        return SURFACE_P_MOUNTAIN;
    if (!strcmp(cName, "P_MARSH"))
        return SURFACE_P_MARSH;
    if (!strcmp(cName, "P_BUSHY"))
        return SURFACE_P_BUSHY;
    if (!strcmp(cName, "P_BUSHYMIX"))
        return SURFACE_P_BUSHYMIX;
    if (!strcmp(cName, "P_BUSHYDRY"))
        return SURFACE_P_BUSHYDRY;
    if (!strcmp(cName, "P_BUSHYMID"))
        return SURFACE_P_BUSHYMID;
    if (!strcmp(cName, "P_GRASSWEEFLOWERS"))
        return SURFACE_P_GRASSWEEFLOWERS;
    if (!strcmp(cName, "P_GRASSDRYTALL"))
        return SURFACE_P_GRASSDRYTALL;
    if (!strcmp(cName, "P_GRASSLUSHTALL"))
        return SURFACE_P_GRASSLUSHTALL;
    if (!strcmp(cName, "P_GRASSGRNMIX"))
        return SURFACE_P_GRASSGRNMIX;
    if (!strcmp(cName, "P_GRASSBRNMIX"))
        return SURFACE_P_GRASSBRNMIX;
    if (!strcmp(cName, "P_GRASSLOW"))
        return SURFACE_P_GRASSLOW;
    if (!strcmp(cName, "P_GRASSROCKY"))
        return SURFACE_P_GRASSROCKY;
    if (!strcmp(cName, "P_GRASSSMALLTREES"))
        return SURFACE_P_GRASSSMALLTREES;
    if (!strcmp(cName, "P_DIRTROCKY"))
        return SURFACE_P_DIRTROCKY;
    if (!strcmp(cName, "P_DIRTWEEDS"))
        return SURFACE_P_DIRTWEEDS;
    if (!strcmp(cName, "P_GRASSWEEDS"))
        return SURFACE_P_GRASSWEEDS;
    if (!strcmp(cName, "P_RIVEREDGE"))
        return SURFACE_P_RIVEREDGE;
    if (!strcmp(cName, "P_POOLSIDE"))
        return SURFACE_P_POOLSIDE;
    if (!strcmp(cName, "P_FORESTSTUMPS"))
        return SURFACE_P_FORESTSTUMPS;
    if (!strcmp(cName, "P_FORESTSTICKS"))
        return SURFACE_P_FORESTSTICKS;
    if (!strcmp(cName, "P_FORRESTLEAVES"))
        return SURFACE_P_FORRESTLEAVES;
    if (!strcmp(cName, "P_DESERTROCKS"))
        return SURFACE_P_DESERTROCKS;
    if (!strcmp(cName, "P_FORRESTDRY"))
        return SURFACE_P_FORRESTDRY;
    if (!strcmp(cName, "P_SPARSEFLOWERS"))
        return SURFACE_P_SPARSEFLOWERS;
    if (!strcmp(cName, "P_BUILDINGSITE"))
        return SURFACE_P_BUILDINGSITE;
    if (!strcmp(cName, "P_DOCKLANDS"))
        return SURFACE_P_DOCKLANDS;
    if (!strcmp(cName, "P_INDUSTRIAL"))
        return SURFACE_P_INDUSTRIAL;
    if (!strcmp(cName, "P_INDUSTJETTY"))
        return SURFACE_P_INDUSTJETTY;
    if (!strcmp(cName, "P_CONCRETELITTER"))
        return SURFACE_P_CONCRETELITTER;
    if (!strcmp(cName, "P_ALLEYRUBISH"))
        return SURFACE_P_ALLEYRUBISH;
    if (!strcmp(cName, "P_JUNKYARDPILES"))
        return SURFACE_P_JUNKYARDPILES;
    if (!strcmp(cName, "P_JUNKYARDGRND"))
        return SURFACE_P_JUNKYARDGRND;
    if (!strcmp(cName, "P_DUMP"))
        return SURFACE_P_DUMP;
    if (!strcmp(cName, "P_CACTUSDENSE"))
        return SURFACE_P_CACTUSDENSE;
    if (!strcmp(cName, "P_AIRPORTGRND"))
        return SURFACE_P_AIRPORTGRND;
    if (!strcmp(cName, "P_CORNFIELD"))
        return SURFACE_P_CORNFIELD;
    if (!strcmp(cName, "P_GRASSLIGHT"))
        return SURFACE_P_GRASSLIGHT;
    if (!strcmp(cName, "P_GRASSLIGHTER"))
        return SURFACE_P_GRASSLIGHTER;
    if (!strcmp(cName, "P_GRASSLIGHTER2"))
        return SURFACE_P_GRASSLIGHTER2;
    if (!strcmp(cName, "P_GRASSMID1"))
        return SURFACE_P_GRASSMID1;
    if (!strcmp(cName, "P_GRASSMID2"))
        return SURFACE_P_GRASSMID2;
    if (!strcmp(cName, "P_GRASSDARK"))
        return SURFACE_P_GRASSDARK;
    if (!strcmp(cName, "P_GRASSDARK2"))
        return SURFACE_P_GRASSDARK2;
    if (!strcmp(cName, "P_GRASSDIRTMIX"))
        return SURFACE_P_GRASSDIRTMIX;
    if (!strcmp(cName, "P_RIVERBEDSTONE"))
        return SURFACE_P_RIVERBEDSTONE;
    if (!strcmp(cName, "P_RIVERBEDSHALLOW"))
        return SURFACE_P_RIVERBEDSHALLOW;
    if (!strcmp(cName, "P_RIVERBEDWEEDS"))
        return SURFACE_P_RIVERBEDWEEDS;
    if (!strcmp(cName, "P_SEAWEED"))
        return SURFACE_P_SEAWEED;
    if (!strcmp(cName, "DOOR"))
        return SURFACE_DOOR;
    if (!strcmp(cName, "PLASTICBARRIER"))
        return SURFACE_PLASTICBARRIER;
    if (!strcmp(cName, "PARKGRASS"))
        return SURFACE_PARKGRASS;
    if (!strcmp(cName, "STAIRSSTONE"))
        return SURFACE_STAIRSSTONE;
    if (!strcmp(cName, "STAIRSMETAL"))
        return SURFACE_STAIRSMETAL;
    if (!strcmp(cName, "STAIRSCARPET"))
        return SURFACE_STAIRSCARPET;
    if (!strcmp(cName, "FLOORMETAL"))
        return SURFACE_FLOORMETAL;
    if (!strcmp(cName, "FLOORCONCRETE"))
        return SURFACE_FLOORCONCRETE;
    if (!strcmp(cName, "BIN_BAG"))
        return SURFACE_BIN_BAG;
    if (!strcmp(cName, "THIN_METAL_SHEET"))
        return SURFACE_THIN_METAL_SHEET;
    if (!strcmp(cName, "METAL_BARREL"))
        return SURFACE_METAL_BARREL;
    if (!strcmp(cName, "PLASTIC_CONE"))
        return SURFACE_PLASTIC_CONE;
    if (!strcmp(cName, "PLASTIC_DUMPSTER"))
        return SURFACE_PLASTIC_DUMPSTER;
    if (!strcmp(cName, "METAL_DUMPSTER"))
        return SURFACE_METAL_DUMPSTER;
    if (!strcmp(cName, "WOOD_PICKET_FENCE"))
        return SURFACE_WOOD_PICKET_FENCE;
    if (!strcmp(cName, "WOOD_SLATTED_FENCE"))
        return SURFACE_WOOD_SLATTED_FENCE;
    if (!strcmp(cName, "WOOD_RANCH_FENCE"))
        return SURFACE_WOOD_RANCH_FENCE;
    if (!strcmp(cName, "UNBREAKABLE_GLASS"))
        return SURFACE_UNBREAKABLE_GLASS;
    if (!strcmp(cName, "HAY_BALE"))
        return SURFACE_HAY_BALE;
    if (!strcmp(cName, "GORE"))
        return SURFACE_GORE;
    if (!strcmp(cName, "RAILTRACK"))
        return SURFACE_RAILTRACK;

    return SURFACE_DEFAULT;
}

void SurfaceInfos_c::LoadSurfaceInfos()
{
    return plugin::CallMethod<0x55EB90, SurfaceInfos_c*>(this);
}

void SurfaceInfos_c::LoadSurfaceAudioInfos()
{
    return plugin::CallMethod<0x55F2B0, SurfaceInfos_c*>(this);
}

void SurfaceInfos_c::Init()
{
    LoadAdhesiveLimits();
    LoadSurfaceInfos();
    LoadSurfaceAudioInfos();
}

eAdhesionGroup SurfaceInfos_c::GetAdhesionGroup(uint32 surfaceId)
{
    return static_cast<eAdhesionGroup>(m_surfaces[surfaceId].ucAdhesionGroup);
}

float SurfaceInfos_c::GetTyreGrip(uint32 surfaceId)
{
    return static_cast<float>(m_surfaces[surfaceId].tyreGrip) * 0.1F;
}

float SurfaceInfos_c::GetWetMultiplier(uint32 surfaceId)
{
    return static_cast<float>(m_surfaces[surfaceId].wetGrip) * 0.01F * CWeather::WetRoads + 1.0F;
}

uint32 SurfaceInfos_c::GetSkidmarkType(uint32 surfaceId)
{
    return m_surfaces[surfaceId].ucSkidmarkType;
}

eFrictionEffect SurfaceInfos_c::GetFrictionEffect(uint32 surfaceId)
{
    return static_cast<eFrictionEffect>(m_surfaces[surfaceId].ucFrictionEffect);
}

uint32 SurfaceInfos_c::GetBulletFx(uint32 surfaceId)
{
    return m_surfaces[surfaceId].ucBulletFX;
}

bool SurfaceInfos_c::IsSoftLanding(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsSoftLand;
}

bool SurfaceInfos_c::IsSeeThrough(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsSeeThrough;
}

bool SurfaceInfos_c::IsShootThrough(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsShootThrough;
}

bool SurfaceInfos_c::IsSand(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsSand;
}

bool SurfaceInfos_c::IsWater(uint32 surfaceID)
{
    return m_surfaces[surfaceID].bIsWater;
}

bool SurfaceInfos_c::IsShallowWater(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsShallowWater;
}

bool SurfaceInfos_c::IsBeach(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsBeach;
}

bool SurfaceInfos_c::IsSteepSlope(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsSteepSlope;
}

bool SurfaceInfos_c::IsGlass(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsGlass;
}

bool SurfaceInfos_c::IsStairs(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsStairs;
}

bool SurfaceInfos_c::IsSkateable(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsSkateable;
}

bool SurfaceInfos_c::IsPavement(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsPavement;
}

uint32 SurfaceInfos_c::GetRoughness(uint32 surfaceId)
{
    return m_surfaces[surfaceId].ucRoughness;
}

uint32 SurfaceInfos_c::GetFlammability(uint32 surfaceId)
{
    return m_surfaces[surfaceId].ucFlammability;
}

bool SurfaceInfos_c::CreatesSparks(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesSparks;
}

bool SurfaceInfos_c::CantSprintOn(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCantSprintOn;
}

bool SurfaceInfos_c::LeavesFootsteps(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bLeavesFootsteps;
}

bool SurfaceInfos_c::ProducesFootDust(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bProducesFootDust;
}

bool SurfaceInfos_c::MakesCarDirty(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bMakesCarDirty;
}

bool SurfaceInfos_c::MakesCarClean(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bMakesCarClean;
}

bool SurfaceInfos_c::CreatesWheelGrass(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesWheelGrass;
}

bool SurfaceInfos_c::CreatesWheelGravel(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesWheelGravel;
}

bool SurfaceInfos_c::CreatesWheelMud(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesWheelMud;
}

bool SurfaceInfos_c::CreatesWheelDust(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesWheelDust;
}

bool SurfaceInfos_c::CreatesWheelSand(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesWheelSand;
}

bool SurfaceInfos_c::CreatesWheelSpray(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesWheelSpray;
}

bool SurfaceInfos_c::CreatesPlants(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesPlants;
}

bool SurfaceInfos_c::CreatesObjects(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCreatesObjects;
}

bool SurfaceInfos_c::CanClimb(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bCanClimb;
}

bool SurfaceInfos_c::IsAudioConcrete(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioConcrete;
}

bool SurfaceInfos_c::IsAudioGrass(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioGrass;
}

bool SurfaceInfos_c::IsAudioSand(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioSand;
}

bool SurfaceInfos_c::IsAudioGravel(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioGravel;
}

bool SurfaceInfos_c::IsAudioWood(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioWood;
}

bool SurfaceInfos_c::IsAudioWater(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioWater;
}

bool SurfaceInfos_c::IsAudioMetal(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioMetal;
}

bool SurfaceInfos_c::IsAudioLongGrass(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioLongGrass;
}

bool SurfaceInfos_c::IsAudioTile(uint32 surfaceId)
{
    return m_surfaces[surfaceId].bIsAudioTile;
}

float SurfaceInfos_c::GetAdhesiveLimit(CColPoint* pColPoint)
{
    auto& surfaceA = m_surfaces[pColPoint->m_nSurfaceTypeA];
    auto& surfaceB = m_surfaces[pColPoint->m_nSurfaceTypeB];
    return m_adhesiveLimits[surfaceB.ucAdhesionGroup][surfaceA.ucAdhesionGroup];
}
