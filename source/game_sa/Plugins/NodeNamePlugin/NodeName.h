/**
 * nick7 @ 2015/03/14 20:21
 */

#pragma once

#include <rwcore.h>

/**
 * define function calling
 */
#ifndef _NODENAMEPLUGINAPI
    #ifdef __cplusplus
        #define _NODENAMEPLUGINAPI extern "C"
    #else
        #define _NODENAMEPLUGINAPI extern
    #endif
#endif

namespace NodeNamePlugin {
void InjectHooks();
}

/**
 * NodeNamePlugin unique rwID
 */
#define rwID_NODENAMEPLUGIN MAKECHUNKID(rwVENDORID_DEVELOPER, 0xFE)

/*
* NodeName plugin static offset
*/
extern RwInt32& gNodeNamePluginOffset;

/**
 * Attach NodeName plugin
 *
 * @since   gta3
 * @return  true if plugin was successfully attached
 * @addr    0x72FAB0
 */
_NODENAMEPLUGINAPI RwBool NodeNamePluginAttach();

/**
 * Get node name for RwFrame
 * Maximum length is 23 chars.
 *
 * @since   gta3
 * @param   frame   pointer to RwFrame struct
 * @return  -
 * @addr    0x72FB30
 */
_NODENAMEPLUGINAPI RwChar const* GetFrameNodeName(RwFrame* frame);

/**
 * Set node name for RwFrame
 * Name will be truncated to 23 chars.
 *
 * @since   gta3
 * @param   frame   pointer to RwFrame struct
 * @param   name  null terminated string containing node name
 * @addr    0x72FB00
 */
_NODENAMEPLUGINAPI void SetFrameNodeName(RwFrame* frame, const RwChar* name);
