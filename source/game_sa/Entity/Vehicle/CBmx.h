/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CBike.h"
#include "CAnimBlendAssociation.h"

enum eBmxNodes {
    BMX_NODE_NONE = 0,
    BMX_CHASSIS = 1,
    BMX_FORKS_FRONT = 2,
    BMX_FORKS_REAR = 3,
    BMX_WHEEL_FRONT = 4,
    BMX_WHEEL_REAR = 5,
    BMX_HANDLEBARS = 6,
    BMX_CHAINSET = 7,
    BMX_PEDAL_R = 8,
    BMX_PEDAL_L = 9,
    BMX_NUM_NODES
};

class CBmx : public CBike {
protected:
    CBmx(plugin::dummy_func_t) : CBike(plugin::dummy) {}
public:
    float field_814;
    float field_818;
    float field_81C;
    float field_820;
    float field_824;
    float field_828;
    float m_fDistanceBetweenWheels;
    float m_fWheelsBalance;
    unsigned char field_834;
    char _pad[3];

    //funcs

    CBmx(int modelIndex, unsigned char createdBy);
 
    void GetFrameOffset(float& arg0, float& arg1);
    void ProcessBunnyHop();

    static void LaunchBunnyHopCB(CAnimBlendAssociation* blendAssoc, void* data); // data is a ptr to CBmx
};

VALIDATE_SIZE(CBmx, 0x838);