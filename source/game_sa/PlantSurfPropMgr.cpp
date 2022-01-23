#include "StdInc.h"

#include "PlantSurfPropMgr.h"

int32* (&CPlantSurfPropMgr::m_SurfPropPtrTab)[MAX_SURFACE_PROPERTIES] = *(int32* (*)[MAX_SURFACE_PROPERTIES])0xC38070;
int32& CPlantSurfPropMgr::m_countSurfPropsAllocated = *(int32*)0xC39ED4;
int32*& CPlantSurfPropMgr::m_SurfPropTab = *(int32**)0xC38338;

enum class ePlantField {
    NAME,                   // Name
    PCD_ID,                 // PCDid
    SLOT_ID,                // SlotID
    MODEL_ID,               // ModelID
    UV_OFFSET,              // UVoff
    COLOR_R,                // R
    COLOR_G,                // G
    COLOR_B,                // B
    INTENSITY,              // I
    INTENSITY_VARIATION,    // VarI
    COLOR_ALPHA,            // A
    SCALE_XY,               // SclXY
    SCALE_Z,                // SclZ
    SCALE_VARIATION_XY,     // SclVarXY
    SCALE_VARIATION_Z,      // SclVarZ
    WIND_BENDING_SCALE,     // WBendScl
    WIND_BENDING_VARIATION, // WBendVar
    DENSITY,                // Density

    ALL_FIELDS_READED
};

struct Plant {
    uint16 model_id;
    uint16 uv_offset;
    CRGBA  color{ 255, 255, 255, 255 };
    uint8  intensity = 255;
    uint8  intensity_variation = 0;
    float  scale_xy = 1.0f;
    float  scale_z = 1.0f;
    float  scale_variation_xy = 0.0f;
    float  scale_variation_z;
    float  density;
    float  wind_blending_scale = 0.0f;
    float  wind_blending_variation;
};

VALIDATE_SIZE(Plant, 0x28);

void CPlantSurfPropMgr::InjectHooks() {

}

// 0x5DD6C0
bool CPlantSurfPropMgr::Initialise() {
    m_countSurfPropsAllocated = 0;
    std::ranges::fill(m_SurfPropPtrTab, nullptr);
//    for (auto& props : m_SurfPropTab) {
//
//    }

    return LoadPlantsDat("PLANTS.DAT") != false;
}

void CPlantSurfPropMgr::Shutdown() {
    // NOP
}

// 0x5DD370
int32* CPlantSurfPropMgr::AllocSurfProperties(uint16 surfaceId, bool clearAllocCount) {
    if (clearAllocCount) {
        m_countSurfPropsAllocated = 0;
        return nullptr;
    }
    if (m_countSurfPropsAllocated >= 57)
        return nullptr;

    m_SurfPropPtrTab[surfaceId] = reinterpret_cast<int32*>(&m_SurfPropTab + 124 * m_countSurfPropsAllocated++);

    return m_SurfPropPtrTab[surfaceId];
}

// 0x6F9DE0
int32* CPlantSurfPropMgr::GetSurfProperties(uint16 index) {
    if (index >= MAX_SURFACE_PROPERTIES)
        return nullptr;
    else
        return m_SurfPropPtrTab[index];
}

// 0x5DD3B0
bool CPlantSurfPropMgr::LoadPlantsDat(const char* filename) {
    char errorMsg[128];
    char* v9;
    uint16 pcdId;
    uint32 surfaceId;

    CFileMgr::SetDir("DATA");
    auto file = CFileMgr::OpenFile(filename, "r");
    CFileMgr::SetDir(gta_empty_string);
    int32 lineId = 0;
    for (char* line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file)) {
        ++lineId;
        if (!strcmp(line, ";the end"))
            break;

        if (*line == ';')
            continue;

        ePlantField field = ePlantField::NAME;
        int32* surfProperties = nullptr;

        char* surfaceName = strtok(line, " \t");

        Plant* plant = nullptr;
        do {
            switch (field) {
            case ePlantField::NAME:
                surfaceId = g_surfaceInfos->GetSurfaceIdFromName(surfaceName);
                if (surfaceId != SURFACE_DEFAULT) {
                    surfProperties = GetSurfProperties(surfaceId);
                    if (surfProperties || AllocSurfProperties(surfaceId, false)) {
                        field = ePlantField::NAME;
                        break;
                    }
                } else {
                    sprintf(errorMsg, "Unknown surface name '%s' in 'Plants.dat' (line %d)! See Andrzej to fix this.", surfaceName, lineId);
                }
                return false;
            case ePlantField::PCD_ID:
                pcdId = atoi(surfaceName);
                if (pcdId > 2) {
                    pcdId = 0;
                }
                plant = reinterpret_cast<Plant*>(&surfProperties[20 * pcdId + 2]);
                break;
            case ePlantField::SLOT_ID:
                surfProperties = reinterpret_cast<int32*>(atoi(surfaceName));
                break;
            case ePlantField::MODEL_ID:
                plant->model_id = atoi(surfaceName);
                break;
            case ePlantField::UV_OFFSET:
                plant->uv_offset = atoi(surfaceName);
                break;
            case ePlantField::COLOR_R:
                plant->color.r = atoi(surfaceName);
                break;
            case ePlantField::COLOR_G:
                plant->color.g = atoi(surfaceName);
                break;
            case ePlantField::COLOR_B:
                plant->color.b = atoi(surfaceName);
                break;
            case ePlantField::INTENSITY:
                plant->intensity = atoi(surfaceName);
                break;
            case ePlantField::INTENSITY_VARIATION:
                plant->intensity_variation = atoi(surfaceName);
                break;
            case ePlantField::COLOR_ALPHA:
                plant->color.a = atoi(surfaceName);
                break;
            case ePlantField::SCALE_XY:
                plant->scale_xy = atof(surfaceName);
                break;
            case ePlantField::SCALE_Z:
                plant->scale_z = atof(surfaceName);
                break;
            case ePlantField::SCALE_VARIATION_XY:
                plant->scale_variation_xy = atof(surfaceName);
                break;
            case ePlantField::SCALE_VARIATION_Z:
                plant->scale_variation_z = atof(surfaceName);
                break;
            case ePlantField::WIND_BENDING_SCALE:
                plant->wind_blending_scale = atof(surfaceName);
                break;
            case ePlantField::WIND_BENDING_VARIATION:
                plant->wind_blending_variation = atof(surfaceName);
                break;
            case ePlantField::DENSITY:
                plant->density = atof(surfaceName);
                break;
            default:
                break;
            }
            surfaceName = strtok(nullptr, " \t");
            field = static_cast<ePlantField>(static_cast<int32>(field) + 1);
        } while (surfaceName);

        if (field < ePlantField::ALL_FIELDS_READED)
            return false;
    }
    CFileMgr::CloseFile(file);
    return true;
}
