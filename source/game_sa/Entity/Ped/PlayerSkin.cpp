#include "StdInc.h"

int32& CPlayerSkin::m_txdSlot = *(int32*) 0xC3F03C;
RpClump*& CPlayerSkin::m_Clump = *(RpClump**)(0xC3F040);
float& CPlayerSkin::m_Angle = *(float*) 0xC3F048;
uint32& CPlayerSkin::m_C3F04C = *(uint32*) 0xC3F04C; // todo: Rename CPlayerSkin:m_C3F04C

void CPlayerSkin::InjectHooks() {
    Install("CPlayerSkin", "Initialise", 0x6FF8A0, &CPlayerSkin::Initialise);
    Install("CPlayerSkin", "Shutdown", 0x6FF8D0, &CPlayerSkin::Shutdown);
    Install("CPlayerSkin", "RenderFrontendSkinEdit", 0x6FF900, &CPlayerSkin::RenderFrontendSkinEdit);
    Install("CPlayerSkin", "GetSkinTexture", 0x6FFA10, &CPlayerSkin::GetSkinTexture);
}

// 0x6FF8A0
void CPlayerSkin::Initialise() {
    CPlayerSkin::m_txdSlot = CTxdStore::AddTxdSlot(TXD_SKIN_SLOT);
    CTxdStore::Create(CPlayerSkin::m_txdSlot);
    CTxdStore::AddRef(CPlayerSkin::m_txdSlot);
}

// 0x6FF8D0
void CPlayerSkin::Shutdown() {
    CTxdStore::RemoveTxdSlot(CPlayerSkin::m_txdSlot);
}

// unused
// 0x6FF900
void CPlayerSkin::RenderFrontendSkinEdit() {
    RwV3d vector = {1.35f, 0.1f, 7.725f};
    RwV3d axis = {0.0f, 1.0f, 0.0f};

    auto* parentFrame = static_cast<RwFrame*>(Scene.m_pRwCamera->object.object.parent);
    RwRGBAReal color{255, 255, 255, 1.0f};
    if (CTimer::GetTimeInMSPauseMode() - CPlayerSkin::m_C3F04C > 7) {
        CPlayerSkin::m_Angle = CPlayerSkin::m_Angle + 2.0f;
        if (CPlayerSkin::m_Angle > 360.0) {
            CPlayerSkin::m_Angle -= 360.0f;
        }
        CPlayerSkin::m_C3F04C = CTimer::GetTimeInMSPauseMode();
    }
    auto* frame = static_cast<RwFrame*>(CPlayerSkin::m_Clump->object.parent);
    RwFrameTransform(frame, &parentFrame->modelling, rwCOMBINEREPLACE);
    RwFrameTranslate(frame, &vector, rwCOMBINEPRECONCAT);
    RwFrameRotate(frame, &axis, CPlayerSkin::m_Angle, rwCOMBINEPRECONCAT);
    RwFrameUpdateObjects(frame);
    SetAmbientColours(&color);
    RpClumpRender(CPlayerSkin::m_Clump);
}

// 0x6FFA10
RwTexture* CPlayerSkin::GetSkinTexture(const char* name) {
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CPlayerSkin::m_txdSlot);
    RwTexture* skinTexture = RwTextureRead(name, nullptr);
    CTxdStore::PopCurrentTxd();
    if (skinTexture) {
        return skinTexture;
    }

    const char* imagePath;
    if (!name[0] || !strcmp(name, "$$\"\"")) {
        imagePath = "models\\generic\\player.bmp";
    } else {
        imagePath = "skins\\%s.bmp";
    }
    sprintf(gString, imagePath, name);

    RwImage* image = RtBMPImageRead(gString);
    if (!image) {
        return skinTexture;
    }

    int32 width, height, depth, flags;
    RwImageFindRasterFormat(image, rwRASTERTYPETEXTURE, &width, &height, &depth, &flags);
    RwRaster* raster = RwRasterCreate(width, height, depth, flags);
    RwRasterSetFromImage(raster, image);
    RwTexture* texture = RwTextureCreate(raster);
    RwTextureSetName(texture, name);
    RwTextureSetFilterMode(texture, rwFILTERLINEAR);
    RwTexDictionaryAddTexture(CTxdStore::ms_pTxdPool->GetAtRef(CPlayerSkin::m_txdSlot)->m_pRwDictionary, texture);
    RwImageDestroy(image);
    return texture;
}
