#pragma once
#include "CommandParser/Parser.hpp"
/*!
 * Various int operations (bitwise and modulo)
 */

auto BitAnd(uint32 a, uint32 b) {
    return a & b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_AND, BitAnd);
auto BitwiseAndThingWithThing(uint32& a, uint32 b) {
    a &= b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_AND_THING_WITH_THING, BitwiseAndThingWithThing);

auto BitOr(uint32 a, uint32 b) {
    return a | b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_OR, BitOr);
auto BitwiseOrThingWithThing(uint32& a, uint32 b) {
    a |= b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_OR_THING_WITH_THING, BitwiseOrThingWithThing);

auto BitXor(uint32 a, uint32 b) {
    return a ^ b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_XOR, BitXor);
auto BitwiseXorThingWithThing(uint32& a, uint32 b) {
    a ^= b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_XOR_THING_WITH_THING, BitwiseXorThingWithThing);

auto BitNot(uint32 a) {
    return ~a; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_NOT, BitNot);

auto BitShl(uint32 a, uint32 b) {
    return a << b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_SHL, BitShl);
auto BitwiseShlThingByThing(uint32& a, uint32 b) {
    a <<= b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_SHL_THING_BY_THING, BitwiseShlThingByThing);

auto BitShr(uint32 a, uint32 b) {
    return a >> b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_SHR, BitShr);
auto BitwiseShrThingByThing(uint32& a, uint32 b) {
    a >>= b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_SHR_THING_BY_THING, BitwiseShrThingByThing);

auto BitMod(uint32 a, uint32 b) {
    return a % b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BIT_MOD, BitMod);
auto BitwiseModThingByThing(uint32& a, uint32 b) {
    a %= b; 
}
REGISTER_COMMAND_HANDLER(COMMAND_BITWISE_MOD_THING_BY_THING, BitwiseModThingByThing);
