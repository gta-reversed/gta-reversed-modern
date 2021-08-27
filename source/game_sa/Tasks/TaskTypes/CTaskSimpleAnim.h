/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"

class  CTaskSimpleAnim : public CTaskSimple {
public:
    CTaskSimpleAnim(bool bHoldLastFrame);
    ~CTaskSimpleAnim();

public:
    CAnimBlendAssociation *m_pAnim;
    union
    {
        unsigned char m_nFlags;
        struct
        {
            unsigned char                        m_bIsFinished : 1;
            unsigned char                        m_bDontInterrupt : 1;
            unsigned char                        m_bHoldLastFrame : 1;

            // These flags are used in CTaskSimpleRunAnim only
            unsigned char                        m_bDontBlendOut : 1;

            // These flags are used in 	CTaskSimpleRunNamedAnim only
            unsigned char                        m_bRunInSequence : 1;
            unsigned char                        m_bOffsetAtEnd : 1;
            unsigned char                        m_bOffsetAvailable : 1;
        };
    };
private:
	char _pad[3];

public:
    static void InjectHooks();

    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
private:
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);

public:
    static void FinishRunAnimCB(CAnimBlendAssociation* pBlendAssoc, void* data); //data is CTaskSimpleAnim
};

VALIDATE_SIZE(CTaskSimpleAnim, 0x10);
