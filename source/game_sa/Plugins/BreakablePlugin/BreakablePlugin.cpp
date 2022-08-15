#include "StdInc.h"

RwInt32& g_BreakablePlugin = *(RwInt32*)0xBB4238;

void BreakablePlugin::InjectHooks() {
    RH_ScopedClass(BreakablePlugin);
    RH_ScopedCategory("Plugins");

    RH_ScopedGlobalInstall(BreakablePluginAttach, 0x59D100);
    RH_ScopedGlobalInstall(BreakableStreamRead, 0x59CEC0);
    RH_ScopedGlobalInstall(BreakableStreamWrite, 0x59CDE0);
    RH_ScopedGlobalInstall(BreakableStreamGetSize, 0x59D0F0);

    RH_ScopedGlobalInstall(BreakableConstructor, 0x59CD70);
    RH_ScopedGlobalInstall(BreakableDestructor, 0x59CD90);
}

//0x59D100
bool BreakablePluginAttach() {
    g_BreakablePlugin = RpGeometryRegisterPlugin(sizeof(BreakablePlugin), rwID_BREAKABLEPLUGIN, BreakableConstructor, BreakableDestructor, nullptr);
    if (g_BreakablePlugin == -1)
        return false;

    auto registerResult = RpGeometryRegisterPluginStream(rwID_BREAKABLEPLUGIN, BreakableStreamRead, BreakableStreamWrite, BreakableStreamGetSize);
    if (registerResult < 0) {
        g_BreakablePlugin = -1;
        return false;
    }

    return true;
}

//0x59CEC0
RwStream* BreakableStreamRead(RwStream* stream, int binaryLength, void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    auto* plugin = RWPLUGINOFFSET(BreakablePlugin, object, g_BreakablePlugin);
    RwStreamRead(stream, &plugin->m_SectionHeader, 4u);
    if (!plugin->m_SectionHeader)
        return stream;

    BreakInfo_t infoBuffer;
    RwStreamRead(stream, &infoBuffer, sizeof(BreakInfo_t));

    auto allocSize = BreakablePluginData::GetRequiredAllocationSize(infoBuffer);
    auto* pluginStruct = reinterpret_cast<BreakablePluginData*>(operator new(allocSize));

    plugin->m_pBreakableInfo = &pluginStruct->m_Info;
    pluginStruct->m_Info = infoBuffer;

    pluginStruct->m_Info.m_pVertexPos = pluginStruct->GetVertexPosPtr();
    RwStreamRead(stream, pluginStruct->GetVertexPosPtr(), sizeof(RwV3d) * pluginStruct->m_Info.m_usNumVertices);

    pluginStruct->m_Info.m_pTexCoors = pluginStruct->GetTexCoordsPtr();
    RwStreamRead(stream, pluginStruct->GetTexCoordsPtr(), sizeof(RwTexCoords) * pluginStruct->m_Info.m_usNumVertices);

    pluginStruct->m_Info.m_pVertexColors = pluginStruct->GetVertColorsPtr();
    RwStreamRead(stream, pluginStruct->GetVertColorsPtr(), sizeof(RwRGBA) * pluginStruct->m_Info.m_usNumVertices);

    pluginStruct->m_Info.m_pTriangles = pluginStruct->GetTrianglesPtr();
    RwStreamRead(stream, pluginStruct->GetTrianglesPtr(), sizeof(BreakInfoTriangle) * pluginStruct->m_Info.m_usNumTriangles);

    pluginStruct->m_Info.m_pTrianglesMaterialIndices = pluginStruct->GetMaterialIndicesPtr();
    RwStreamRead(stream, pluginStruct->GetMaterialIndicesPtr(), sizeof(uint16) * pluginStruct->m_Info.m_usNumTriangles);

    pluginStruct->m_Info.m_pTextureNames = pluginStruct->GetTextureNamesPtr();
    RwStreamRead(stream, pluginStruct->GetTextureNamesPtr(), sizeof(char[32]) * pluginStruct->m_Info.m_usNumMaterials);

    pluginStruct->m_Info.m_pMaskNames = pluginStruct->GetMaskNamesPtr();
    RwStreamRead(stream, pluginStruct->GetMaskNamesPtr(), sizeof(char[32]) * pluginStruct->m_Info.m_usNumMaterials);

    pluginStruct->m_Info.m_pMaterialProperties = pluginStruct->GetSurfacePropsPtr();
    RwStreamRead(stream, pluginStruct->GetSurfacePropsPtr(), sizeof(BreakInfoColor) * pluginStruct->m_Info.m_usNumMaterials);

    pluginStruct->m_Info.m_pTextures = pluginStruct->GetTexturesPtr();
    for (auto i = 0; i < pluginStruct->m_Info.m_usNumMaterials; ++i) {
        auto charOffset = i * 32;
        RwTexture* texture = nullptr;

        if (pluginStruct->m_Info.m_pMaskNames[charOffset])
            texture = RwTextureRead(&pluginStruct->m_Info.m_pTextureNames[charOffset], &pluginStruct->m_Info.m_pMaskNames[charOffset]);
        else
            texture = RwTextureRead(&pluginStruct->m_Info.m_pTextureNames[charOffset], nullptr);

        pluginStruct->m_Info.m_pTextures[i] = texture;
    }

    return stream;
}

//0x59CDE0
RwStream* BreakableStreamWrite(RwStream* stream, RwInt32 binaryLength, const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    auto* plugin = RWPLUGINOFFSET(BreakablePlugin, object, g_BreakablePlugin);
    RwStreamWrite(stream, plugin, 4u);

    if (plugin->m_pBreakableInfo) {
        auto* info = plugin->m_pBreakableInfo;
        RwStreamWrite(stream, info, sizeof(BreakInfo_t));
        RwStreamWrite(stream, info->m_pVertexPos, sizeof(RwV3d) * info->m_usNumVertices);
        RwStreamWrite(stream, info->m_pTexCoors, sizeof(RwTexCoords) * info->m_usNumVertices);
        RwStreamWrite(stream, info->m_pVertexColors, sizeof(RwRGBA) * info->m_usNumVertices);
        RwStreamWrite(stream, info->m_pTriangles, sizeof(BreakInfoTriangle) * info->m_usNumTriangles);
        RwStreamWrite(stream, info->m_pTrianglesMaterialIndices, sizeof(uint16) * info->m_usNumTriangles);
        RwStreamWrite(stream, info->m_pTextureNames, sizeof(char[32]) * info->m_usNumMaterials);
        RwStreamWrite(stream, info->m_pMaskNames, sizeof(char[32]) * info->m_usNumMaterials);
        RwStreamWrite(stream, info->m_pMaterialProperties, sizeof(BreakInfoColor) * info->m_usNumMaterials);
    }

    return stream;
}

// 0x59D0F0
RwInt32 BreakableStreamGetSize(const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    return sizeof(BreakInfo_t);
}

//0x59CD70
void* BreakableConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    if (g_BreakablePlugin <= 0)
        return object;

    auto* plugin = RWPLUGINOFFSET(BreakablePlugin, object, g_BreakablePlugin);
    plugin->m_pBreakableInfo = nullptr;
    return object;
}

//0x59CD90
void* BreakableDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    if (g_BreakablePlugin <= 0)
        return object;

    auto* plugin = RWPLUGINOFFSET(BreakablePlugin, object, g_BreakablePlugin);
    if (plugin->m_pBreakableInfo) {
        for (auto i = 0; i < plugin->m_pBreakableInfo->m_usNumMaterials; ++i) {
            if (plugin->m_pBreakableInfo->m_pTextures[i])
                RwTextureDestroy(plugin->m_pBreakableInfo->m_pTextures[i]);
        }

        operator delete(plugin->m_pBreakableInfo);
    }

    return object;
}

