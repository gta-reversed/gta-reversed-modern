#pragma once

#define VERIFY_IMPL(expr, ...) expr
#define VERIFY VERIFY_IMPL

#define DEV_LOG(format, ...)

#define PUSH_RENDERGROUP(str) 0
#define POP_RENDERGROUP() 0

void CreateDebugFont();
void DestroyDebugFont();
void ObrsPrintfString(const char* str, int16 x, int16 y);
void FlushObrsPrintfs();
