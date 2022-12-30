#pragma once

struct AnimDescriptor {
    int32 animId{};
    int32 flags{};
};

struct AnimAssocDefinition {
    char   groupName[16]{};
    char   blockName[16]{};
    int32  modelIndex{};
    int32  animsCount{};

    const char**    animNames{};
    AnimDescriptor* animDesc{};
};
VALIDATE_SIZE(AnimAssocDefinition, 0x30);
