#include "StdInc.h"

void C2dEffect::InjectHooks()
{
    ReversibleHooks::Install("C2dEffect", "Roadsign_GetNumLinesFromFlags", 0x6FA640, &C2dEffect::Roadsign_GetNumLinesFromFlags);
    ReversibleHooks::Install("C2dEffect", "Roadsign_GetNumLettersFromFlags", 0x6FA670, &C2dEffect::Roadsign_GetNumLettersFromFlags);
    ReversibleHooks::Install("C2dEffect", "Roadsign_GetPaletteIDFromFlags", 0x6FA6A0, &C2dEffect::Roadsign_GetPaletteIDFromFlags);
}

int C2dEffect::Roadsign_GetNumLinesFromFlags(CRoadsignAttrFlags flags)
{
    switch (flags.m_nNumOfLines) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    }

    return 4;
}

int C2dEffect::Roadsign_GetNumLettersFromFlags(CRoadsignAttrFlags flags)
{
    switch (flags.m_nSymbolsPerLine) {
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 8;
    }

    return 16;
}

int C2dEffect::Roadsign_GetPaletteIDFromFlags(CRoadsignAttrFlags flags)
{

    switch (flags.m_nTextColor) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    }

    return 0;
}
