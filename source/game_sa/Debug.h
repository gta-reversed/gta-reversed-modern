#pragma once

#include <vector>
#include <string>

class CDebug
{
public:
    struct tDebugText
    {
        std::string text;
        float x, y;
    };
    static std::vector<tDebugText> m_debugStrings;

    static void InjectHooks();
    static void DebugInitTextBuffer();
    static void DebugAddText(const char* str);
    static void DebugAddText(const char* str, float x, float y);
    static void DebugDisplayTextBuffer();
};

