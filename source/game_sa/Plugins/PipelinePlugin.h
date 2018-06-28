/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "RenderWare.h"

// Plugin ID:  MAKECHUNKID(rwVENDORID_DEVELOPER, 0xF3)

/**
 * Attach pipeline plugin
 *
 * @since   gtasa
 * @return  true if plugin was successfully attached.
 */
RwBool PipelinePluginAttach(void);

/**
 * Get pipeline ID
 *
 * @since   gtasa
 * @param   pAtomic       pointer to RpAtomic struct
 * @return                pipeline ID
 */
RwUInt32 GetPipelineID(RpAtomic * pAtomic);

/**
 * Set pipeline ID
 *
 * @since   gtasa
 * @param   pAtomic       pointer to RpAtomic struct
 * @param   nPipelineID   pipeline ID
 */
void SetPipelineID(RpAtomic * pAtomic, RwUInt32 uPipelineID);
