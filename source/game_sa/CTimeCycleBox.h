/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CBox.h"


class CTimeCycleBox
{
public:
  CBox box;
  short farclip;
  unsigned char lodDistMult;
  int extraColor;
  float strength;
  float falloff;
};

VALIDATE_SIZE(CTimeCycleBox, 0x28);