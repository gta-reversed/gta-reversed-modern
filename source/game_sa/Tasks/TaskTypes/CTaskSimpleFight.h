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
#include "CEntity.h"


class  CTaskSimpleFight : public CTaskSimple {
protected:
    CTaskSimpleFight(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:

   bool m_bIsFinished;
   bool m_bIsInControl;

   bool m_bAnimsReferenced;
private:
    char _pad;
public:
   unsigned int m_nRequiredAnimGroup;

   unsigned short m_nIdlePeriod;
   unsigned short m_nIdleCounter;
   char m_nContinueStrike;
   char m_nChainCounter;
private:
    char _pad2[2];
public:

   CEntity *m_pTargetEntity;
   CAnimBlendAssociation *m_pAnim;
   CAnimBlendAssociation *m_pIdleAnim;

   char m_nComboSet;
   char m_nCurrentMove;
   unsigned char m_nNextCommand;
   unsigned char m_nLastCommand;
    
   CTaskSimpleFight* Constructor(CEntity *pTargetEntity, int nCommand, unsigned int nIdlePeriod = 10000);
   bool ControlFight(CEntity* pEntity, unsigned char command);
};

VALIDATE_SIZE(CTaskSimpleFight, 0x28);
