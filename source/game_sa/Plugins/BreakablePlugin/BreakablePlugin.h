#pragma once

/**
 * collision plugin unique rwID
 */
#define rwID_BREAKABLEPLUGIN MAKECHUNKID(rwVENDORID_DEVELOPER, 0xFD)

/*
 * Collision plugin static offset
 */
extern RwInt32& g_BreakablePlugin;

enum eBreakablePluginPositionRule : uint32 {
    OBJECT_ORIGIN = 0,
    COLLISION_ORIGIN = 1,
};

struct BreakInfoTriangle {
    RwUInt16 vertIndex[3];
};

// RW PLUGIN
struct BreakInfo_t {
    eBreakablePluginPositionRule m_uiPosRule;
    uint16                       m_usNumVertices;
    struct RwV3d*                m_pVertexPos;
    struct RwTexCoords*          m_pTexCoors;
    struct RwRGBA*               m_pVertexColors;
    uint16                       m_usNumTriangles;
    struct BreakInfoTriangle*    m_pTriangles;
    uint16*                      m_pTrianglesMaterialIndices;
    uint16                       m_usNumMaterials;
    struct RwTexture**           m_pTextures;
    char*                        m_pTextureNames;
    char*                        m_pMaskNames;
    struct RwSurfaceProperties*  m_pMaterialProperties;
};
VALIDATE_SIZE(BreakInfo_t, 0x34);

struct BreakablePlugin {
    union {
        uint32 m_SectionHeader;
        BreakInfo_t* m_pBreakableInfo;
    };

    static void InjectHooks();
};
VALIDATE_SIZE(BreakablePlugin, 0x4);

struct BreakablePluginData {
    BreakInfo_t m_Info;
    // Dynamically allocated size, depending on loaded model sizes]
    // RwV3d               m_aVertexPos[m_usNumVertices];
    // RwTexCoords         m_aTexCoors[m_usNumVertices];
    // RwRGBA              m_aVertexColors[m_usNumVertices];
    // BreakInfoTriangle   m_aTriangleVertIndices[m_usNumTriangles];
    // uint16              m_aTriangleMaterialIndices[m_usNumTriangles];
    // char                m_aTextureNames[m_usNumMaterials][32];
    // char                m_aMaskNames[m_usNumMaterials][32];
    // RwSurfaceProperties m_aMaterialProperties[m_usNumMaterial];
    // RwTexture*          m_aTexturePointers[m_usNumMaterial];

// NOTSA: Helper functions
    static uint32 GetRequiredAllocationSize(BreakInfo_t const& baseInfo) {
        auto size = sizeof(BreakInfo_t);
        size += sizeof(RwV3d) * baseInfo.m_usNumVertices;
        size += sizeof(RwTexCoords) * baseInfo.m_usNumVertices;
        size += sizeof(RwRGBA) * baseInfo.m_usNumVertices;
        size += sizeof(BreakInfoTriangle) * baseInfo.m_usNumTriangles;
        size += sizeof(uint16) * baseInfo.m_usNumTriangles;
        size += sizeof(char[32]) * baseInfo.m_usNumMaterials;
        size += sizeof(char[32]) * baseInfo.m_usNumMaterials;
        size += sizeof(RwSurfaceProperties) * baseInfo.m_usNumMaterials;
        size += sizeof(RwTexture*) * baseInfo.m_usNumMaterials;

        return size;
    };

// UGLY METHODS BELOW
    inline RwV3d* GetVertexPosPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        return reinterpret_cast<RwV3d*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline RwTexCoords* GetTexCoordsPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        return reinterpret_cast<RwTexCoords*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline RwRGBA* GetVertColorsPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        return reinterpret_cast<RwRGBA*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline BreakInfoTriangle* GetTrianglesPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwRGBA) * m_Info.m_usNumVertices;
        return reinterpret_cast<BreakInfoTriangle*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline uint16* GetMaterialIndicesPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwRGBA) * m_Info.m_usNumVertices;
        byteOffset += sizeof(BreakInfoTriangle) * m_Info.m_usNumTriangles;
        return reinterpret_cast<uint16*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline char* GetTextureNamesPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwRGBA) * m_Info.m_usNumVertices;
        byteOffset += sizeof(BreakInfoTriangle) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(uint16) * m_Info.m_usNumTriangles;
        return reinterpret_cast<char*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline char* GetMaskNamesPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwRGBA) * m_Info.m_usNumVertices;
        byteOffset += sizeof(BreakInfoTriangle) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(uint16) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(char[32]) * m_Info.m_usNumMaterials;
        return reinterpret_cast<char*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline RwSurfaceProperties* GetSurfacePropsPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwRGBA) * m_Info.m_usNumVertices;
        byteOffset += sizeof(BreakInfoTriangle) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(uint16) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(char[32]) * m_Info.m_usNumMaterials;
        byteOffset += sizeof(char[32]) * m_Info.m_usNumMaterials;
        return reinterpret_cast<RwSurfaceProperties*>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };

    inline RwTexture** GetTexturesPtr() {
        auto byteOffset = sizeof(BreakInfo_t);
        byteOffset += sizeof(RwV3d) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwTexCoords) * m_Info.m_usNumVertices;
        byteOffset += sizeof(RwRGBA) * m_Info.m_usNumVertices;
        byteOffset += sizeof(BreakInfoTriangle) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(uint16) * m_Info.m_usNumTriangles;
        byteOffset += sizeof(char[32]) * m_Info.m_usNumMaterials;
        byteOffset += sizeof(char[32]) * m_Info.m_usNumMaterials;
        byteOffset += sizeof(RwSurfaceProperties) * m_Info.m_usNumMaterials;
        return reinterpret_cast<RwTexture**>(&reinterpret_cast<uint8*>(this)[byteOffset]);
    };
};

#define BREAKABLEPLG(geometry, var) \
    (RWPLUGINOFFSET(BreakablePlugin, geometry, g_BreakablePlugin)->var)

#define BREAKABLECONSTPLG(geometry, var) \
    (RWPLUGINOFFSETCONST(BreakablePlugin, geometry, g_BreakablePlugin)->var)

void* BreakableConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
void* BreakableDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);

bool BreakablePluginAttach();
RwStream* BreakableStreamRead(RwStream* stream, int binaryLength, void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
RwStream* BreakableStreamWrite(RwStream* stream, RwInt32 binaryLength, const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
RwInt32 BreakableStreamGetSize(const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
