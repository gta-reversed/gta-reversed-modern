#pragma once

#include "rwcore.h"

// Get first texture in TXD
// 0x734940
extern RwTexture* GetFirstTexture(RwTexDictionary* txd);

// 0x734930
extern RwTexture* GetFirstTextureCallback(RwTexture* texture, void* data);

// Read texture from RW stream
// 0x730E60
extern RwTexture* RwTextureGtaStreamRead(RwStream* stream);

// Read TXD from RW stream
// 0x730FC0
extern RwTexDictionary* RwTexDictionaryGtaStreamRead(RwStream* stream);

// Start reading TXD from RW stream
// 0x731070
extern RwTexDictionary* RwTexDictionaryGtaStreamRead1(RwStream* stream);

// Finish reading TXD from RW stream
// 0x731150
extern RwTexDictionary* RwTexDictionaryGtaStreamRead2(RwStream* stream, RwTexDictionary* txd);

// 0x72E570
extern bool RpClumpGtaStreamRead1(RwStream* stream);

// 0x72E620
RpClump* RpClumpGtaStreamRead2(RwStream* stream);
