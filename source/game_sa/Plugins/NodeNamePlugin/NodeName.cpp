#include "StdInc.h"

#include "NodeName.h"

#define NAME_LENGTH 23

RwInt32 gPluginOffset;

/**
 * NodeName plugin structure
 *
 * @size 24
 */
typedef struct tNodeNamePlugin {
    RwChar name[NAME_LENGTH + 1];
} NodeNamePluginInstance;

void NodeNamePlugin::InjectHooks() {
    Install("NodeNamePlugin", "NodeNamePluginAttach", 0x72FAB0, &NodeNamePluginAttach);
    Install("NodeNamePlugin", "GetFrameNodeName", 0x72FB30, &GetFrameNodeName);
    Install("NodeNamePlugin", "SetFrameNodeName", 0x72FB00, &SetFrameNodeName);
}

// internal
// 0x72F9C0
static void* NodeNameConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    if (gPluginOffset > 0)
        RWPLUGINOFFSET(NodeNamePluginInstance, object, gPluginOffset)->name[0] = '\0';

    return object;
}

// internal
// 0x72F9E0
static void* NodeNameDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    return object;
}

// internal
// 0x72F9F0
static void* NodeNameCopy(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    strncpy(RWPLUGINOFFSET(NodeNamePluginInstance, dstObject, gPluginOffset)->name, RWPLUGINOFFSET(NodeNamePluginInstance, srcObject, gPluginOffset)->name, NAME_LENGTH);
    return dstObject;
}

// internal
// 0x72FA50
static RwStream* NodeNameStreamRead(RwStream* stream, RwInt32 binaryLength, void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    RwStreamRead(stream, RWPLUGINOFFSET(NodeNamePluginInstance, object, gPluginOffset), binaryLength);
    RWPLUGINOFFSET(NodeNamePluginInstance, object, gPluginOffset)->name[binaryLength] = 0;
    return stream;
}

// internal
// 0x72FA20
static RwStream* NodeNameStreamWrite(RwStream* stream, RwInt32 binaryLength, const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    RwStreamWrite(stream, RWPLUGINOFFSET(NodeNamePluginInstance, object, gPluginOffset), binaryLength);
    return stream;
}

// internal
// 0x72FA80
static RwInt32 NodeNameStreamGetSize(const void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    if (RWPLUGINOFFSET(NodeNamePluginInstance, object, gPluginOffset))
        return strlen(RWPLUGINOFFSET(NodeNamePluginInstance, object, gPluginOffset)->name);

    return 0;
}

RwBool NodeNamePluginAttach() {
    // register plugin
    gPluginOffset = RwFrameRegisterPlugin(sizeof(NodeNamePluginInstance), rwID_NODENAMEPLUGIN, NodeNameConstructor, NodeNameDestructor, NodeNameCopy);

    // register stream operations
    RwFrameRegisterPluginStream(rwID_NODENAMEPLUGIN, NodeNameStreamRead, NodeNameStreamWrite, NodeNameStreamGetSize);

    return gPluginOffset != -1;
}

const RwChar* GetFrameNodeName(RwFrame* frame) {
    if (gPluginOffset > 0)
        return RWPLUGINOFFSET(NodeNamePluginInstance, frame, gPluginOffset)->name;

    return nullptr;
}

void SetFrameNodeName(RwFrame* frame, const RwChar* name) {
    if (gPluginOffset > 0) {
        strncpy(RWPLUGINOFFSET(NodeNamePluginInstance, frame, gPluginOffset)->name, name, NAME_LENGTH);
        RWPLUGINOFFSET(NodeNamePluginInstance, frame, gPluginOffset)->name[NAME_LENGTH] = '\0';
    }
}
