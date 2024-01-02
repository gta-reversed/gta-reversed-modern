#pragma once

struct AnimDescriptor {
    int32 animId{};
    int32 flags{};
};

struct AnimAssocDefinition {
    constexpr static size_t ANIM_NAME_BUF_SZ = 24;
    
    char   groupName[16]{};
    char   blockName[16]{};
    int32  modelIndex{};
    int32  animsCount{};

    const char**    animNames{}; //< Pointers to heap allocated char arrays (size 24 each) - The array of pointers itself is heap allocated as well - Size == animsCount
    AnimDescriptor* animDesc{};
};
VALIDATE_SIZE(AnimAssocDefinition, 0x30);
