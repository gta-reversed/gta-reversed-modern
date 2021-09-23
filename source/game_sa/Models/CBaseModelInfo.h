/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "CColModel.h"
#include "CKeyGen.h"
#include "Plugins\TwoDEffectPlugin\C2dEffect.h"

#include "eModelID.h"

enum ModelInfoType : uint8 {
    MODEL_INFO_ATOMIC = 1,
    MODEL_INFO_TIME = 3,
    MODEL_INFO_WEAPON = 4,
    MODEL_INFO_CLUMP = 5,
    MODEL_INFO_VEHICLE = 6,
    MODEL_INFO_PED = 7,
    MODEL_INFO_LOD = 8
};

enum eModelInfoSpecialType : uint8 {
    TREE = 1,
    PALM = 2,
    GLASS_TYPE_1 = 4,
    GLASS_TYPE_2 = 5,
    TAG = 6,
    GARAGE_DOOR = 7,
    CRANE = 9,
    UNKNOWN = 10,
    BREAKABLE_STATUE = 11,
};

class CVehicleModelInfo;
class CTimeInfo;

// originally an abstract class
class CBaseModelInfo {
public:
    uint32 m_nKey;
    uint16 m_nRefCount;
    int16  m_nTxdIndex;
    uint8  m_nAlpha;
    uint8  m_n2dfxCount;
    int16  m_n2dEffectIndex;
    int16  m_nObjectInfoIndex;
    union {
        uint16 m_nFlags;
        struct {
            uint8 m_nFlagsUpperByte;
            uint8 m_nFlagsLowerByte;
        };
        struct {
            /* https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CModelInfoSA.h */
            uint8 bHasBeenPreRendered : 1; // we use this because we need to apply changes only once
            uint8 bDrawLast : 1;
            uint8 bAdditiveRender : 1;
            uint8 bDontWriteZBuffer : 1;
            uint8 bDontCastShadowsOn : 1;
            uint8 bDoWeOwnTheColModel : 1;
            uint8 bIsBackfaceCulled : 1;
            uint8 bIsLod : 1;

            union {
                struct { // Atomic flags
                    uint8 bIsRoad : 1;
                    uint8 : 1;
                    uint8 bDontCollideWithFlyer : 1;
                    uint8 nSpecialType : 4;
                    uint8 bWetRoadReflection : 1;
                };
                struct { // Vehicle flags
                    uint8 bUsesVehDummy : 1;
                    uint8 : 1;
                    uint8 nCarmodId : 5;
                    uint8 bUseCommonVehicleDictionary : 1;
                };
                struct { // Clump flags
                    uint8 bHasAnimBlend : 1;
                    uint8 bHasComplexHierarchy : 1;
                    uint8 bAnimSomething : 1;
                    uint8 bOwnsCollisionModel : 1;
                    uint8 : 3;
                    uint8 bTagDisabled : 1;
                };
            };
        };
    };
    CColModel* m_pColModel;     // 20
    float      m_fDrawDistance; // 24
    union {
        struct RwObject* m_pRwObject;
        struct RpClump*  m_pRwClump;
        struct RpAtomic* m_pRwAtomic;
    };

public:
    static void InjectHooks();

    CBaseModelInfo();

    // vtable
    virtual ~CBaseModelInfo() { assert(0); }
    virtual class CAtomicModelInfo* AsAtomicModelInfoPtr();
    virtual class CDamageAtomicModelInfo* AsDamageAtomicModelInfoPtr();
    virtual class CLodAtomicModelInfo* AsLodAtomicModelInfoPtr();
    virtual ModelInfoType GetModelType() = 0;
    virtual CTimeInfo* GetTimeInfo();
    virtual void Init();
    virtual void Shutdown();
    virtual void DeleteRwObject() = 0;
    virtual uint32 GetRwModelType() = 0;
    virtual struct RwObject* CreateInstance() = 0;
    virtual struct RwObject* CreateInstance(RwMatrix* matrix) = 0;
    virtual void SetAnimFile(char const* filename);
    virtual void ConvertAnimFileIndex();
    virtual signed int GetAnimFileIndex();

    // vtable methods implementations
    class CAtomicModelInfo* AsAtomicModelInfoPtr_Reversed();
    class CDamageAtomicModelInfo* AsDamageAtomicModelInfoPtr_Reversed();
    class CLodAtomicModelInfo* AsLodAtomicModelInfoPtr_Reversed();
    CTimeInfo* GetTimeInfo_Reversed();
    void Init_Reversed();
    void Shutdown_Reversed();
    void SetAnimFile_Reversed(char const* filename);
    void ConvertAnimFileIndex_Reversed();
    signed int GetAnimFileIndex_Reversed();

    void SetTexDictionary(char const* txdName);
    void ClearTexDictionary();
    void AddTexDictionaryRef();
    void RemoveTexDictionaryRef();
    void AddRef();
    void RemoveRef();
    // initPairedModel defines if we need to set col model for time model
    void SetColModel(CColModel* colModel, bool bIsLodModel);
    void Init2dEffects();
    void DeleteCollisionModel();
    // index is a number of effect (max number is (m_n2dfxCount - 1))
    C2dEffect* Get2dEffect(int32 index);
    void Add2dEffect(C2dEffect* effect);

    // Those further ones are completely inlined in final version, not present at all in android version;
    inline CVehicleModelInfo* AsVehicleModelInfoPtr() { return reinterpret_cast<CVehicleModelInfo*>(this); }
    inline CColModel* GetColModel() { return m_pColModel; }

    inline bool GetIsDrawLast() { return bDrawLast; }
    inline bool HasBeenPreRendered() { return bHasBeenPreRendered; }
    inline bool HasComplexHierarchy() { return bHasComplexHierarchy; }
    inline bool IsBackfaceCulled() { return bIsBackfaceCulled; }
    inline bool IsLod() { return bIsLod; }
    inline bool IsRoad() { return bIsRoad; }
    inline void SetHasBeenPreRendered(int32 bPreRendered) { bHasBeenPreRendered = bPreRendered; }
    inline void SetIsLod(bool bLod) { bIsLod = bLod; }
    inline void SetOwnsColModel(bool bOwns) { bDoWeOwnTheColModel = bOwns; }
    inline void IncreaseAlpha() {
        if (m_nAlpha >= 239)
            m_nAlpha = 255;
        else
            m_nAlpha += 16;
    };
    inline void SetModelName(const char* modelName) {
        m_nKey = CKeyGen::GetUppercaseKey(modelName);
    }

    inline bool IsSwayInWind1() { return nSpecialType == eModelInfoSpecialType::TREE; }        // 0x0800
    inline bool IsSwayInWind2() { return nSpecialType == eModelInfoSpecialType::PALM; }        // 0x1000
    inline bool SwaysInWind() { return IsSwayInWind1() || IsSwayInWind2(); }
    inline bool IsGlassType1() { return nSpecialType == eModelInfoSpecialType::GLASS_TYPE_1; } // 0x2000
    inline bool IsGlassType2() { return nSpecialType == eModelInfoSpecialType::GLASS_TYPE_2; } // 0x2800
    inline bool IsGlass() { return IsGlassType1() || IsGlassType2(); }
    inline bool IsTagModel() { return nSpecialType == eModelInfoSpecialType::TAG; }            // 0x3000
    inline bool IsGarageDoor() { return nSpecialType == eModelInfoSpecialType::GARAGE_DOOR; }  // 0x3800
    inline bool IsBreakableStatuePart() { return nSpecialType == eModelInfoSpecialType::BREAKABLE_STATUE; }
    inline bool IsCrane() { return nSpecialType == eModelInfoSpecialType::CRANE; } // 0x4800
};
VALIDATE_SIZE(CBaseModelInfo, 0x20);

void SetBaseModelInfoFlags(CBaseModelInfo* modelInfo, uint32 dwFlags);
