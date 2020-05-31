#include "StdInc.h"

float CCarFXRenderer::SetFxEnvMapLightMult(float multiplier)
{
    return plugin::CallAndReturn<float, 0x5D5BA0, float>(multiplier);
}
