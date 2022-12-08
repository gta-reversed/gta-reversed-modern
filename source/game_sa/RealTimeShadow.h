/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "RenderWare.h"
#include "ShadowCamera.h"
#include "Sphere.h"

class CPhysical;

class CRealTimeShadow { // AKA `CCutsceneShadow`
public:
    static void InjectHooks();

    CRealTimeShadow() = default;
    ~CRealTimeShadow() = default;

    struct RwFrame*   SetLightProperties(float angle, float _unused_param, bool setLight);
    struct RwTexture* GetShadowRwTexture();

    void              Destroy();
    CShadowCamera*    GetShadowCamera();
    void              DrawBorderAroundTexture(const RwRGBA& color);

    /// this creates all stuff for shadow processing (cameras, textures)
    bool Create(bool isBlurred, int32 blurPasses, bool drawMoreBlur);

    /// this one registers shadow for entity
    bool SetupForThisEntity(CPhysical* owner);

    /// this updates texture and gives it to us
    RwTexture* Update();

public: // Eventually make this private
    CPhysical*    m_pOwner{};
    bool          m_bCreated{};
    uint8         m_nIntensity{};
    CShadowCamera m_camera{};
    bool          m_bBlurred{};
    CShadowCamera m_blurCamera{};
    uint32        m_nBlurPasses{};
    bool          m_bDrawMoreBlur;
    uint32        m_nRwObjectType{(uint32)-1};
    RpLight*      m_pLight{};
    CSphere       m_boundingSphere{};
    CSphere       m_baseSphere{};

private:
    // 0x706410
    CRealTimeShadow* Constructor() {
        this->CRealTimeShadow::CRealTimeShadow();
        return this;
    }

    // 0x706440
    CRealTimeShadow* Destructor() {
        this->CRealTimeShadow::~CRealTimeShadow();
        return this;
    }
};

VALIDATE_SIZE(CRealTimeShadow, 0x4C);
