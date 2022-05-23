/**
 * nick7 @ 2015/03/15 01:55
 */

#pragma once

#include <rwcore.h>
#include <rpworld.h>

/**
* define function calling
*/
#ifndef _PIPELINEPLUGINAPI
#  ifdef __cplusplus
#    define _PIPELINEPLUGINAPI extern "C"
#  else
#    define _PIPELINEPLUGINAPI extern
#  endif
#endif

namespace PipelinePlugin
{
void InjectHooks();
}

/**
 * pipeline plugin unique rwID
 */
#define rwID_PIPELINEPLUGIN  MAKECHUNKID(rwVENDORID_DEVELOPER, 0xF3)

/*
* Pipeline plugin static offset
*/
extern RwInt32& gPipelinePluginOffset;

/**
 * Attach pipeline plugin
 *
 * @since   gtasa
 * @return  true if plugin was successfully attached.
 */
_PIPELINEPLUGINAPI RwBool PipelinePluginAttach();

/**
 * Get pipeline ID
 *
 * @since   gtasa
 * @param   _pAtomic      pointer to RpAtomic struct
 * @return                pipeline ID
 */
_PIPELINEPLUGINAPI RwUInt32 GetPipelineID(RpAtomic * atomic);

/**
 * Set pipeline ID
 *
 * @since   gtasa
 * @param   _pAtomic      pointer to RpAtomic struct
 * @param   _nPipelineID  pipeline ID
 */
_PIPELINEPLUGINAPI void SetPipelineID(RpAtomic * atomic, RwUInt32 pipelineId);
