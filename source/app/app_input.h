#pragma once

#include "skeleton.h"

void AppInputInjectHooks();
RsEventStatus HandleKeyDown(void* param);
RsEventStatus HandleKeyUp(void* param);
RsEventStatus KeyboardHandler(RsEvent event, void* param);
RsEventStatus HandlePadButtonDown(void* param);
RsEventStatus HandlePadButtonUp(void* param);
RsEventStatus PadHandler(RsEvent event, void* param);
bool AttachInputDevices();
