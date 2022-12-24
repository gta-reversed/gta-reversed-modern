#pragma once
#include "CommandParser/Parser.hpp"
/*!
 * Various int operations (bitwise and modulo)
 */

REGISTER_COMMAND_HANDLER(COMMAND_BIT_AND, [](uint32 a, uint32 b) { return a & b; });
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_AND_THING_WITH_THING, [](uint32& a, uint32 b) { a &= b; });

REGISTER_COMMAND_HANDLER(COMMAND_BIT_OR, [](uint32 a, uint32 b) { return a | b; });
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_OR_THING_WITH_THING, [](uint32& a, uint32 b) { a |= b; });

REGISTER_COMMAND_HANDLER(COMMAND_BIT_XOR, [](uint32 a, uint32 b) { return a ^ b; });
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_XOR_THING_WITH_THING, [](uint32& a, uint32 b) { a ^= b; });

REGISTER_COMMAND_HANDLER(COMMAND_BIT_NOT, [](uint32 a) { return ~a; });

REGISTER_COMMAND_HANDLER(COMMAND_BIT_SHL, [](uint32 a, uint32 b) { return a << b; });
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_SHL_THING_BY_THING, [](uint32& a, uint32 b) { a <<= b; });

REGISTER_COMMAND_HANDLER(COMMAND_BIT_SHR, [](uint32 a, uint32 b) { return a >> b; });
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_SHR_THING_BY_THING, [](uint32& a, uint32 b) { a >>= b; });

REGISTER_COMMAND_HANDLER(COMMAND_BIT_MOD, [](uint32 a, uint32 b) { return a % b; });
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_MOD_THING_BY_THING, [](uint32& a, uint32 b) { a %= b; });
