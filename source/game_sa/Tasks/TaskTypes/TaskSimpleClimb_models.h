#pragma once

#include <array>
#include "eSurfaceType.h"
#include "ColSphere.h"

constexpr CColSphere ClimbColModelSpheres[] = {
    { { { 0.0f, -0.06f, 1.2f }, 0.4f }, SURFACE_DEFAULT,              0 },
    { { { 0.0f, -0.06f, 1.7f }, 0.4f }, SURFACE_TARMAC,               1 },
    { { { 0.0f, -0.06f, 2.2f }, 0.4f }, SURFACE_TARMAC_FUCKED,        2 },
    { { { 0.0f, -0.06f, 2.5f }, 0.4f }, SURFACE_TARMAC_REALLYFUCKED,  3 },
    { { { 0.0f, +0.5f,  2.9f }, 0.4f }, SURFACE_PAVEMENT,             4 },
    { { { 0.0f, +0.5f,  2.4f }, 0.4f }, SURFACE_PAVEMENT_FUCKED,      5 },
    { { { 0.0f, +0.5f,  1.9f }, 0.4f }, SURFACE_GRAVEL,               6 },
    { { { 0.0f, +0.5f,  1.4f }, 0.4f }, SURFACE_FUCKED_CONCRETE,      7 },
    { { { 0.0f, +0.5f,  0.9f }, 0.4f }, SURFACE_PAINTED_GROUND,       8 },
    { { { 0.0f, +0.5f,  0.4f }, 0.4f }, SURFACE_GRASS_SHORT_LUSH,     9 },
    { { { 0.0f, +1.0f,  2.9f }, 0.4f }, SURFACE_GRASS_MEDIUM_LUSH,   10 },
    { { { 0.0f, +1.0f,  2.4f }, 0.4f }, SURFACE_GRASS_LONG_LUSH,     11 },
    { { { 0.0f, +1.0f,  1.9f }, 0.4f }, SURFACE_GRASS_SHORT_DRY,     12 },
    { { { 0.0f, +1.0f,  1.4f }, 0.4f }, SURFACE_GRASS_MEDIUM_DRY,    13 },
    { { { 0.0f, +1.0f,  0.9f }, 0.4f }, SURFACE_GRASS_LONG_DRY,      14 },
    { { { 0.0f, +1.0f,  0.4f }, 0.4f }, SURFACE_GOLFGRASS_ROUGH,     15 },
    { { { 0.0f, +1.5f,  2.9f }, 0.4f }, SURFACE_GOLFGRASS_SMOOTH,    16 },
    { { { 0.0f, +1.5f,  2.4f }, 0.4f }, SURFACE_STEEP_SLIDYGRASS,    17 },
    { { { 0.0f, +1.5f,  1.9f }, 0.4f }, SURFACE_STEEP_CLIFF,         18 },
    { { { 0.0f, +1.5f,  1.4f }, 0.4f }, SURFACE_FLOWERBED,           19 },
    { { { 0.0f, +1.5f,  0.9f }, 0.4f }, SURFACE_MEADOW,              20 },
    { { { 0.0f, +1.5f,  0.4f }, 0.4f }, SURFACE_WASTEGROUND,         21 },
};

constexpr CColSphere StandUpColModelSpheres[] = {
    { { { 0.0f, 0.6f, +1.75f }, 0.35f }, SURFACE_DEFAULT,             0 },
    { { { 0.0f, 0.6f, +1.30f }, 0.35f }, SURFACE_TARMAC,              1 },
    { { { 0.0f, 0.6f, +0.85f }, 0.35f }, SURFACE_TARMAC_FUCKED,       2 },
    { { { 0.0f, 0.3f, +0.65f }, 0.35f }, SURFACE_TARMAC_REALLYFUCKED, 3 },
    { { { 0.0f, 0.0f, +0.50f }, 0.35f }, SURFACE_PAVEMENT,            4 },
    { { { 0.0f, 0.0f, +0.10f }, 0.35f }, SURFACE_PAVEMENT_FUCKED,     5 },
    { { { 0.0f, 0.0f, -0.30f }, 0.35f }, SURFACE_GRAVEL,              6 }
};

constexpr CColSphere VaultColModelSpheres[] = {
    { { { 0.0f, 1.10f, -0.2f }, 0.3f }, SURFACE_DEFAULT,             0  },
    { { { 0.0f, 1.10f, +0.2f }, 0.3f }, SURFACE_TARMAC,              1  },
    { { { 0.0f, 1.10f, +0.6f }, 0.3f }, SURFACE_TARMAC_FUCKED,       2  },
    { { { 0.0f, 0.70f, +0.6f }, 0.3f }, SURFACE_TARMAC_REALLYFUCKED, 3  },
    { { { 0.0f, 0.35f, +0.6f }, 0.3f }, SURFACE_PAVEMENT,            4  },
    { { { 0.0f, 0.00f, +0.6f }, 0.3f }, SURFACE_PAVEMENT_FUCKED,     5  },
};

constexpr CColSphere FindEdgeColModelSpheres[] = {
    { { { 0.0f, -0.5f, +0.5f }, 0.3f }, SURFACE_DEFAULT,              0  },
    { { { 0.0f, -0.5f, +0.3f }, 0.3f }, SURFACE_TARMAC,               1  },
    { { { 0.0f, -0.5f, +0.1f }, 0.3f }, SURFACE_TARMAC_FUCKED,        2  },
    { { { 0.0f, -0.5f, -0.1f }, 0.3f }, SURFACE_TARMAC_REALLYFUCKED,  3  },
    { { { 0.0f, -0.3f, +0.5f }, 0.3f }, SURFACE_PAVEMENT,             4  },
    { { { 0.0f, -0.3f, +0.3f }, 0.3f }, SURFACE_PAVEMENT_FUCKED,      5  },
    { { { 0.0f, -0.3f, +0.1f }, 0.3f }, SURFACE_GRAVEL,               6  },
    { { { 0.0f, -0.3f, -0.1f }, 0.3f }, SURFACE_FUCKED_CONCRETE,      7  },
    { { { 0.0f, -0.1f, +0.5f }, 0.3f }, SURFACE_PAINTED_GROUND,       8  },
    { { { 0.0f, -0.1f, +0.3f }, 0.3f }, SURFACE_GRASS_SHORT_LUSH,     9  },
    { { { 0.0f, -0.1f, +0.1f }, 0.3f }, SURFACE_GRASS_MEDIUM_LUSH,   10  },
    { { { 0.0f, -0.1f, -0.1f }, 0.3f }, SURFACE_GRASS_LONG_LUSH,     11  },
    { { { 0.0f, +0.1f, +0.5f }, 0.3f }, SURFACE_GRASS_SHORT_DRY,     12  },
    { { { 0.0f, +0.1f, +0.3f }, 0.3f }, SURFACE_GRASS_MEDIUM_DRY,    13  },
    { { { 0.0f, +0.1f, +0.1f }, 0.3f }, SURFACE_GRASS_LONG_DRY,      14  },
    { { { 0.0f, +0.1f, -0.1f }, 0.3f }, SURFACE_GOLFGRASS_ROUGH,     15  },
};
