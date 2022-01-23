#pragma once

class CVector;
class CRGBA;
class RwTexture;

class PPTriPlant {
public:
    CBoundingBox start;
    CBoundingBox end;
    int16        type;
    int16        field_32;
    float        field_34;
    float        field_38;
    RwTexture*   texture;
    CRGBA        color;
    uint16       colorIntensity;
    int8         surface; // eSurfaceType?
    int8         field_47;
    uint32       randomSeed;
    float        field_4C;
    float        field_50;
    float        m_fWindBendingModifier;
    float        field_58;
};

VALIDATE_SIZE(PPTriPlant, 0x5C);

constexpr unsigned MAX_PLANTS = 32;

class CPPTriPlantBuffer {
public:
    int32      m_nNumActive;
    PPTriPlant m_aPlants[MAX_PLANTS];
    int32      m_nType;
    RpAtomic*  m_aAtomics[4];

public:
    static void InjectHooks();

    CPPTriPlantBuffer();
    ~CPPTriPlantBuffer() = default;

    void Flush();
    PPTriPlant* GetPPTriPlantPtr(int32 nIncrease);
    void ChangeCurrentPlantModelsSet(int32 type);
    void IncreaseBufferIndex(int32 type, int32 nIncrease);

    void* GetPlantModelsTab(uint32 type);
    void SetPlantModelsTab(uint32 type, RpAtomic** atomics);

    static RpMaterial* SetGrassMaterialCB(RpMaterial* material, void* data);

    // original name unknown
    int32 GetType() const { return m_nType; }; // 0x5DAAF0
    void SetType(int32 type) { m_nType = type; }; // 0x5DAAE0

    // NOTSA
    void CopyToActive(PPTriPlant* plant) {
        memcpy(&m_aPlants[m_nNumActive], plant, sizeof(PPTriPlant));
    }
};

extern RwTexture*& RenderGrassTexture;
