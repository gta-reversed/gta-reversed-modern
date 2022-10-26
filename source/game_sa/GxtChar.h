/**
 * nick7 @ 2014/12/16 18:10
 */

#pragma once


typedef char GxtChar;            // 8-bit GXT character
typedef GxtChar* PGxtStr;        // 8-bit null terminated GXT string
typedef GxtChar const* PCGxtStr; // 8-bit null terminated constant GXT string

/**
 * Convert ANSI string to GXT-supported null-terminated string
 *
 * @param   src     pointer to null-terminated source string
 * @param   dst    pointer to destination buffer
 */
void AsciiToGxtChar(const char* src, GxtChar* dst);

/**
 * Convert GXT bull terminated string to ANSI string
 * NOTE: encoding bugs can appear!
 * NOTE: function is not thread safe,
 *
 * @param   src       pointer to null-terminated source string
 * @param   start     start position
 * @return  pointer to static var containing null-terminated ASCII string
 */
const char* GxtCharToAscii(const GxtChar* src, uint8 start);

/**
 * Concatenate null terminated GXT strings
 *
 * @param   dst    pointer to destination buffer containing null-terminated string
 * @param   src    pointer to null-terminated string you wanna add to destination
 */
GxtChar* GxtCharStrcat(GxtChar* dst, const GxtChar* src);

/**
 * Get GXT null terminated string length
 *
 * @param    str  pointer to null-terminated string
 * @return   string length
 */
uint32 GxtCharStrlen(const GxtChar* str);

/**
 * Lowercase null terminated string
 * NOTE: this function does NOT use locale.
 *
 * @param   str  pointer to null-terminated string you wanna lowercase
 */
void MakeLowerCase(char* str);

/**
 * Copy GXT null terminated string (like strcpy)
 *
 * @param   dst    pointer to destination buffer
 * @param   src    pointer to null-terminated string you wanna copy
 */
void TextCopy(GxtChar* dst, const GxtChar* src);

/**
 * Copy GXT null terminated strings
 *
 * @param   dst    pointer to destination buffer containing null-terminated string
 * @param   src    pointer to null-terminated string you wanna copy to destination
 * @return  pointer to destination buffer
 */
GxtChar* GxtCharStrcpy(GxtChar* dst, const GxtChar* src);
