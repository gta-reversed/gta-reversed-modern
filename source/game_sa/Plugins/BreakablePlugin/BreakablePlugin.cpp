#include "StdInc.h"

#include "BreakablePlugin.h"

void BreakablePlugin::InjectHooks() {
    RH_ScopedClass(BreakablePlugin);
    RH_ScopedCategory("Plugins");

    RH_ScopedGlobalInstall(BreakableConstructor, 0x59CD70);
    RH_ScopedGlobalInstall(BreakableDestructor, 0x59CD90);
    RH_ScopedGlobalInstall(BreakablePluginAttach, 0x59D100);
    RH_ScopedGlobalInstall(BreakableStreamRead, 0x59CEC0);
    RH_ScopedGlobalInstall(BreakableStreamWrite, 0x59CDE0);
    RH_ScopedGlobalInstall(BreakableStreamGetSize, 0x59D0F0);
}

// 0x59D100
bool BreakablePluginAttach() {
    g_BreakablePlugin = RpGeometryRegisterPlugin(sizeof(BreakablePlugin), rwID_BREAKABLEPLUGIN, BreakableConstructor, BreakableDestructor, nullptr);
    if (g_BreakablePlugin == -1) {
        DEV_LOG("Failed to register Breakable Plugin");
        return false;
    }

    auto registerResult = RpGeometryRegisterPluginStream(rwID_BREAKABLEPLUGIN, BreakableStreamRead, BreakableStreamWrite, BreakableStreamGetSize);
    if (registerResult < 0) {
        g_BreakablePlugin = -1;
        DEV_LOG("Failed to register Breakable Plugin Stream");
        return false;
    }

    return true;
}

// 0x59CD70
void* BreakableConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    if (g_BreakablePlugin <= 0)
        return object;

    auto* plugin = RWPLUGINOFFSET(BreakablePlugin, object, g_BreakablePlugin);
    plugin->m_pBreakableInfo = nullptr;
    return object;
}

// 0x59CD90
void* BreakableDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    if (g_BreakablePlugin <= 0)
        return object;

    auto* plugin = RWPLUGINOFFSET(BreakablePlugin, object, g_BreakablePlugin);
    if (!plugin->m_pBreakableInfo)
        return object;

    for (auto& texture : plugin->GetTextures()) {
        if (texture) {
            RwTextureDestroy(texture);
        }
    }
    delete plugin->m_pBreakableInfo;
    return object;
}

// 0x59CEC0
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
    auto& info = pluginStruct->m_Info;

    const auto Read = [&](void* to, void* what, size_t size) {
        to = what;
        RwStreamRead(stream, to, size);
    };
    Read(info.m_pVertexPos,                pluginStruct->GetVertexPosPtr(),       sizeof(RwV3d) * info.m_usNumVertices);
    Read(info.m_pTexCoors,                 pluginStruct->GetTexCoordsPtr(),       sizeof(RwTexCoords) * info.m_usNumVertices);
    Read(info.m_pVertexColors,             pluginStruct->GetVertColorsPtr(),      sizeof(RwRGBA) * info.m_usNumVertices);
    Read(info.m_pTriangles,                pluginStruct->GetTrianglesPtr(),       sizeof(BreakInfoTriangle) * info.m_usNumTriangles);
    Read(info.m_pTrianglesMaterialIndices, pluginStruct->GetMaterialIndicesPtr(), sizeof(uint16) * info.m_usNumTriangles);
    Read(info.m_pTextureNames,             pluginStruct->GetTextureNamesPtr(),    sizeof(char[32]) * info.m_usNumMaterials);
    Read(info.m_pMaskNames,                pluginStruct->GetMaskNamesPtr(),       sizeof(char[32]) * info.m_usNumMaterials);
    Read(info.m_pMaterialProperties,       pluginStruct->GetSurfacePropsPtr(),    sizeof(BreakInfoColor) * info.m_usNumMaterials);

    info.m_pTextures = pluginStruct->GetTexturesPtr();
    for (auto i = 0; i < info.m_usNumMaterials; ++i) {
        auto charOffset = i * 32; // todo: sizeof m_pTextureNames[0]?
        info.m_pTextures[i] = RwTextureRead(
            &info.m_pTextureNames[charOffset],
            info.m_pMaskNames[charOffset] ? &info.m_pMaskNames[charOffset] : nullptr
        );
    }

    return stream;
}

// 0x59CDE0
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
