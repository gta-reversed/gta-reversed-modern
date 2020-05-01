#include "StdInc.h"

void D3DResourceSystem::TidyUpD3DIndexBuffers(unsigned int count)
{
	((void(__cdecl*)(short)) 0x730740) (count);
}

void D3DResourceSystem::TidyUpD3DTextures(unsigned int count)
{
	((void(__cdecl*)(short)) 0x7305E0) (count);
}