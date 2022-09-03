#pragma once

#define VERIFY_IMPL(expr, ...) expr
#define VERIFY VERIFY_IMPL

#ifdef _DEBUG
namespace notsa {
static void DevPrintf(int lineno, const char* file, const char* fmt, ...) {
    (void)printf("[%s @ %i]: ", file, lineno);

    va_list vargs;
    va_start(vargs, fmt);
    (void)vprintf(fmt, vargs);
    va_end(vargs);

    printf("\n");
}
};
#define DEV_LOG(...) notsa::DevPrintf(__LINE__, __FILE__, ##__VA_ARGS__)
#else
#define DEV_LOG(...)
#endif

#define PUSH_RENDERGROUP(str) 0
#define POP_RENDERGROUP() 0

void CreateDebugFont();
void DestroyDebugFont();
void ObrsPrintfString(const char* str, int16 x, int16 y);
void FlushObrsPrintfs();
