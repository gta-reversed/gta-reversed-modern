/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#pragma once

#include "RenderWare.h"
#include "MenuManager.h"

namespace JPegPlugin
{
void InjectHooks();
}

void JPegCompressScreen(RwCamera* camera, struct jpeg_destination_mgr& dst);

/**
 * Compress camera screen and save at the given file path
 *
 * @addr  0x5D0820
 */
extern void JPegCompressScreenToFile(RwCamera* camera, char const* path);

/**
 * Compress camera screen to the given buffer
 */
extern void JPegCompressScreenToBuffer(char** buffer, uint32* size);

void JPegDecompressToRaster(RwRaster* raster, struct jpeg_source_mgr& src);
void JPegDecompressToVramFromBuffer(RwRaster* raster, RwInt8** unk);
