#include "StdInc.h"

#include "FxInfoManager.h"
#include "FxManager.h"

#include "EmissionInfo.h"
#include "MovementInfo.h"
#include "RenderInfo.h"

// #include "FxInfoEmRate.h"
// #include "FxInfoEmSize.h"
// #include "FxInfoEmSpeed.h"
// #include "FxInfoEmDir.h"
// #include "FxInfoEmAngle.h"
// #include "FxInfoEmLife.h"
// #include "FxInfoEmPos.h"
// #include "FxInfoEmWeather.h"
// #include "FxInfoEmRotation.h"
// #include "FxInfoNoise.h"
// #include "FxInfoForce.h"
// #include "FxInfoFriction.h"
// #include "FxInfoAttractPt.h"
// #include "FxInfoAttractLine.h"
// #include "FxInfoGroundCollide.h"
// #include "FxInfoWind.h"
// #include "FxInfoJitter.h"
// #include "FxInfoRotSpeed.h"
// #include "FxInfoFloat.h"
// #include "FxInfoUnderwater.h"
// #include "FxInfoColour.h"
// #include "FxInfoSize.h"
// #include "FxInfoSpriteRect.h"
// #include "FxInfoHeatHaze.h"
// #include "FxInfoTrail.h"
// #include "FxInfoFlat.h"
// #include "FxInfoDir.h"
// #include "FxInfoAnimTexture.h"
// #include "FxInfoColourRange.h"
// #include "FxInfoSelfLit.h"
// #include "FxInfoColourBright.h"
// #include "FxInfoSmoke.h"
// #include "FxInfoRotate.h"
// #include "FxInfoTexCoords.h"
// #include "FxInfoRotateOffset.h"


void FxInfoManager_c::InjectHooks() {
    RH_ScopedClass(FxInfoManager_c);
    RH_ScopedCategory("Fx");

    // RH_ScopedInstall(AddFxInfo, 0x4A7B00);
    // RH_ScopedInstall(Load, 0x5C0B70);
    // RH_ScopedInstall(ProcessEmissionInfo, 0x4A4960);
    // RH_ScopedInstall(ProcessMovementInfo, 0x4A4A10);
    // RH_ScopedInstall(ProcessRenderInfo, 0x4A4A80);
}

// 0x4A7B00
FxInfo_c* FxInfoManager_c::AddFxInfo(int32 info) {
    return plugin::CallMethodAndReturn<FxInfo_c*, 0x4A7B00, FxInfoManager_c*, int32>(this, info);
    /*
    switch (info) {
    case FX_INFO_EMRATE_DATA:        return new FxInfoEmRate_c();
    case FX_INFO_EMSIZE_DATA:        return new FxInfoEmSize_c();
    case FX_INFO_EMSPEED_DATA:       return new FxInfoEmSpeed_c();
    case FX_INFO_EMDIR_DATA:         return new FxInfoEmDir_c();
    case FX_INFO_EMANGLE_DATA:       return new FxInfoEmAngle_c();
    case FX_INFO_EMLIFE_DATA:        return new FxInfoEmLife_c();
    case FX_INFO_EMPOS_DATA:         return new FxInfoEmPos_c();
    case FX_INFO_EMWEATHER_DATA:     return new FxInfoEmWeather_c();
    case FX_INFO_EMROTATION_DATA:    return new FxInfoEmRotation_c();
    case FX_INFO_NOISE_DATA:         return new FxInfoNoise_c();
    case FX_INFO_FORCE_DATA:         return new FxInfoForce_c();
    case FX_INFO_FRICTION_DATA:      return new FxInfoFriction_c();
    case FX_INFO_ATTRACTPT_DATA:     return new FxInfoAttractPt_c();
    case FX_INFO_ATTRACTLINE_DATA:   return new FxInfoAttractLine_c();
    case FX_INFO_GROUNDCOLLIDE_DATA: return new FxInfoGroundCollide_c();
    case FX_INFO_WIND_DATA:          return new FxInfoWind_c();
    case FX_INFO_JITTER_DATA:        return new FxInfoJitter_c();
    case FX_INFO_ROTSPEED_DATA:      return new FxInfoRotSpeed_c();
    case FX_INFO_FLOAT_DATA:         return new FxInfoFloat_c();
    case FX_INFO_UNDERWATER_DATA:    return new FxInfoUnderwater_c();
    case FX_INFO_COLOUR_DATA:        return new FxInfoColour_c();
    case FX_INFO_SIZE_DATA:          return new FxInfoSize_c();
    case FX_INFO_SPRITERECT_DATA:    return new FxInfoSpriteRect_c();
    case FX_INFO_HEATHAZE_DATA:      return new FxInfoHeatHaze_c();
    case FX_INFO_TRAIL_DATA:         return new FxInfoTrail_c();
    case FX_INFO_FLAT_DATA:          return new FxInfoFlat_c();
    case FX_INFO_DIR_DATA:           return new FxInfoDir_c();
    case FX_INFO_ANIMTEX_DATA:       return new FxInfoAnimTexture_c();
    case FX_INFO_COLOURRANGE_DATA:   return new FxInfoColourRange_c();
    case FX_INFO_SELFLIT_DATA:       return new FxInfoSelfLit_c();
    case FX_INFO_COLOURBRIGHT_DATA:  return new FxInfoColourBright_c();
    case FX_INFO_SMOKE_DATA:         return new FxInfoSmoke_c();
    // NOTSA case FX_INFO_ROTATE_DATA:        return new FxInfoRotate_c();
    // NOTSA case FX_INFO_TEXCOORDS_DATA:     return new FxInfoTexCoords_c();
    // NOTSA case FX_INFO_ROTATEOFFSET_DATA:  return new FxInfoRotateOffset_c();
    default:                         return nullptr;
    };
    */
}

constexpr struct { int32 type; const char* name; } mapping[] = {
    { FX_INFO_EMRATE_DATA,           "FX_INFO_EMRATE_DATA:"        },
    { FX_INFO_EMSIZE_DATA,           "FX_INFO_EMSIZE_DATA:"        },
    { FX_INFO_EMSPEED_DATA,          "FX_INFO_EMSPEED_DATA:"       },
    { FX_INFO_EMDIR_DATA,            "FX_INFO_EMDIR_DATA:"         },
    { FX_INFO_EMANGLE_DATA,          "FX_INFO_EMANGLE_DATA:"       },
    { FX_INFO_EMLIFE_DATA,           "FX_INFO_EMLIFE_DATA:"        },
    { FX_INFO_EMPOS_DATA,            "FX_INFO_EMPOS_DATA:"         },
    { FX_INFO_EMWEATHER_DATA,        "FX_INFO_EMWEATHER_DATA:"     },
    { FX_INFO_EMROTATION_DATA,       "FX_INFO_EMROTATION_DATA:"    },
    { FX_INFO_NOISE_DATA,            "FX_INFO_NOISE_DATA:"         },
    { FX_INFO_FORCE_DATA,            "FX_INFO_FORCE_DATA:"         },
    { FX_INFO_FRICTION_DATA,         "FX_INFO_FRICTION_DATA:"      },
    { FX_INFO_ATTRACTPT_DATA,        "FX_INFO_ATTRACTPT_DATA:"     },
    { FX_INFO_ATTRACTLINE_DATA,      "FX_INFO_ATTRACTLINE_DATA:"   },
    { FX_INFO_GROUNDCOLLIDE_DATA,    "FX_INFO_GROUNDCOLLIDE_DATA:" },
    { FX_INFO_WIND_DATA,             "FX_INFO_WIND_DATA:"          },
    { FX_INFO_JITTER_DATA,           "FX_INFO_JITTER_DATA:"        },
    { FX_INFO_ROTSPEED_DATA,         "FX_INFO_ROTSPEED_DATA:"      },
    { FX_INFO_FLOAT_DATA,            "FX_INFO_FLOAT_DATA:"         },
    { FX_INFO_UNDERWATER_DATA,       "FX_INFO_UNDERWATER_DATA:"    },
    { FX_INFO_COLOUR_DATA,           "FX_INFO_COLOUR_DATA:"        },
    { FX_INFO_SIZE_DATA,             "FX_INFO_SIZE_DATA:"          },
    { FX_INFO_SPRITERECT_DATA,       "FX_INFO_SPRITERECT_DATA:"    },
    { FX_INFO_HEATHAZE_DATA,         "FX_INFO_HEATHAZE_DATA:"      },
    { FX_INFO_TRAIL_DATA,            "FX_INFO_TRAIL_DATA:"         },
    { FX_INFO_FLAT_DATA,             "FX_INFO_FLAT_DATA:"          },
    { FX_INFO_DIR_DATA,              "FX_INFO_DIR_DATA:"           },
    { FX_INFO_ANIMTEX_DATA,          "FX_INFO_ANIMTEX_DATA:"       },
    { FX_INFO_COLOURRANGE_DATA,      "FX_INFO_COLOURRANGE_DATA:"   },
    { FX_INFO_SELFLIT_DATA,          "FX_INFO_SELFLIT_DATA:"       },
    { FX_INFO_COLOURBRIGHT_DATA,     "FX_INFO_COLOURBRIGHT_DATA:"  },
    { FX_INFO_SMOKE_DATA,            "FX_INFO_SMOKE_DATA:"         },
    // NOTSA { FX_INFO_ROTATE_DATA,           "FX_INFO_ROTATE_DATA:"        },
    // NOTSA { FX_INFO_TEXCOORDS_DATA,        "FX_INFO_TEXCOORDS_DATA:"     },
    // NOTSA { FX_INFO_ROTATEOFFSET_DATA,     "FX_INFO_ROTATEOFFSET_DATA:"  },
};

// 0x5C0B70
void FxInfoManager_c::Load(FILESTREAM file, int32 version) {
    return plugin::CallMethod<0x5C0B70, FxInfoManager_c*, FILESTREAM, int32>(this, file, version);

    /*
    ReadField<void>(file);
    m_nNumInfos = ReadField<int32>(file, "NUM_INFOS:");
    m_nFirstMovementInfo = -1;
    m_nFirstRenderInfo   = -1;

    m_pInfos = g_fxMan.Allocate<FxInfo_c*>(m_nNumInfos);
    assert(m_pInfos);

    char line[256], field[128];
    for (auto& info : GetInfos()) {
        ReadLine(file, line, sizeof(line));
        sscanf(line, "%s", field);

        const auto GetType = [=]() -> int32 {
            for (auto& [type, name] : mapping) {
                if (strcmp(field, name) == 0) {
                    return type;
                }
            }
            printf("Unknown FX Info: %s", field); // NOTSA
            assert(true);
            return 0;
        };
        auto infoType = GetType();

        bool bTimeModePrt = true;
        if ((infoType & 0xF000) > 0x1000 && version >= 0.7f) {
            bTimeModePrt = ReadField<bool>(file, "TIMEMODEPRT:");
        }

        info = AddFxInfo(infoType);
        assert(info); // printf("Failed to load info: %s\n", field)
        info->Load(file, version);
        ReadField<void>(file);

        info->m_bTimeModeParticle = bTimeModePrt;
    }

    if (m_nFirstRenderInfo == -1)
        m_nFirstRenderInfo = m_nNumInfos;

    if (m_nFirstMovementInfo == -1)
        m_nFirstMovementInfo = m_nFirstRenderInfo;
    */
}

/* todo:
 *  info->m_nType
 *  replace raw iteration to *irange*
 *  ProcessRenderInfo: mult = prt->m_fCurrentLife / prt->m_fTotalLife;
 */

// 0x4A4960
void FxInfoManager_c::ProcessEmissionInfo(float currentTime, float mult, float totalTime, bool bConstTimeSet, EmissionInfo_t* emission) {
    return plugin::CallMethod<0x4A4960, FxInfoManager_c*, float, float, float, bool, EmissionInfo_t*>(this, currentTime, mult, totalTime, bConstTimeSet, emission);
    /*
    emission->Process(mult);

    for (auto i = 0; i < m_nFirstMovementInfo; i++) {
        auto& info = m_pInfos[i];
        if ((info->m_nType & 0x1000) != 0) {
            info->GetValue(currentTime, 0.0f, mult, totalTime, bConstTimeSet, emission);
        }
    }
     */
}

// a6 - always false
// 0x4A4A10
void FxInfoManager_c::ProcessMovementInfo(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, MovementInfo_t* movementInfo) {
    return plugin::CallMethod<0x4A4A10, FxInfoManager_c*, float, float, float, float, bool, MovementInfo_t*>(this, currentTime, mult, totalTime, length, bConstTimeSet, movementInfo);
    /*
    movementInfo->Process();

    for (auto i = m_nFirstMovementInfo; i < m_nFirstRenderInfo; i++) {
        auto& info = m_pInfos[i];
        if ((info->m_nType & 0x2000) != 0) {
            info->GetValue(currentTime, mult, totalTime, length, bConstTimeSet, movementInfo);
        }
    }
     */
}

// a6 - always false
// 0x4A4A80
void FxInfoManager_c::ProcessRenderInfo(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, RenderInfo_t* renderInfo) {
    return plugin::CallMethod<0x4A4A80, FxInfoManager_c*, float, float, float, float, bool, RenderInfo_t*>(this, currentTime, mult, totalTime, length, bConstTimeSet, renderInfo);
    /*
    renderInfo->Process();

    for (auto i = m_nFirstRenderInfo; i < m_nNumInfos; i++) {
        auto& info = m_pInfos[i];
        if ((info->m_nType & 0xC000) != 0) {
            info->GetValue(currentTime, mult, totalTime, length, bConstTimeSet, renderInfo);
        }
    }
     */
}
