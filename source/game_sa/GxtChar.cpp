#include "StdInc.h"

#include "GxtChar.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

// 0x718600
void AsciiToGxtChar(const char* src, GxtChar* dst) {
    assert(src && dst);
    for (int32 i = 0; src[i]; ++i) {
        dst[i] = src[i];
        dst[i + 1] = 0;
    }
}

// 0x69F7E0
const char* GxtCharToAscii(GxtChar* src, uint8 start) {
    static char buf[256] = { 0 };

    GxtChar* str = src;
    if (start) {
        str = &src[start];
    }

    int32 i = 0;
    while (i < (ARRAY_SIZE(buf) - 1) && (str && str[i])) {
        GxtChar symbol = str[i];

        if (symbol >= 0x80 && symbol <= 0x83)
            symbol += 0x40;
        else if (symbol >= 0x84 && symbol <= 0x8D)
            symbol += 0x42;
        else if (symbol >= 0x8E && symbol <= 0x91)
            symbol += 0x44;
        else if (symbol >= 0x92 && symbol <= 0x95)
            symbol += 0x47;
        else if (symbol >= 0x96 && symbol <= 0x9A)
            symbol += 0x49;
        else if (symbol >= 0x9B && symbol <= 0xA4)
            symbol += 0x4B;
        else if (symbol >= 0xA5 && symbol <= 0xA8)
            symbol += 0x4D;
        else if (symbol >= 0xA9 && symbol <= 0xCC)
            symbol += 0x50;
        else if (symbol == 0xCD)
            symbol = 0xD1;
        else if (symbol == 0xCE)
            symbol = 0xF1;
        else if (symbol == 0xCF)
            symbol = 0xBF;
        else if (symbol >= 0xD0)
            symbol = 0x23; // '#'

        buf[i] = symbol;

        ++i;
    }
    buf[i] = '\0';

    return buf;
}

GxtChar* GxtCharStrcat(GxtChar* dst, GxtChar* src) {
    GxtChar* target = dst;
    if (*dst) {
        while (target[0])
            ++target;
    }
    if (*src) {
        while (*src)
            *target++ = *src++;
    }
    *target = '\0';
    return dst;
}

uint32 GxtCharStrlen(const GxtChar* str) {
    uint32 len = 0;
    while (str[len]) {
        ++len;
    }
    return len;
}

void MakeLowerCase(char* str) {
    char* start = str;
    while (*start) {
        if (*start >= 'A' && *start <= 'Z') {
            *start += 'a' - 'A';
        }
        ++start;
    }
}

// 0x69F910
void TextCopy(GxtChar* dst, const GxtChar* src) {
    while (*src) {
        *dst = *src;
        ++src;
        ++dst;
    }
    *dst = '\0';
}

// 0x718660
GxtChar* GxtCharStrcpy(GxtChar* dst, const GxtChar* src) {
    TextCopy(dst, src);
    return dst;
}
