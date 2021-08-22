#include "StdInc.h"

#include "rtdict.h"

RtDictSchema* RtDictSchemaInit(RtDictSchema* schema) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*))0x7CED40)(schema);
}

RwBool RtDictSchemaDestruct(RtDictSchema* schema) {
    return ((RwBool(__cdecl *)(RtDictSchema*))0x7CED70)(schema);
}

RtDict* RtDictSchemaStreamReadDict(RtDictSchema* schema, RwStream* stream) {
    return ((RtDict*(__cdecl *)(RtDictSchema*, RwStream*))0x7CF240)(schema, stream);
}

RtDict* RtDictSchemaCreateDict(RtDictSchema* schema) {
    return ((RtDict*(__cdecl *)(RtDictSchema*))0x7CED90)(schema);
}

RtDictSchema* RtDictSchemaAddDict(RtDictSchema* schema, RtDict* dict) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEE50)(schema, dict);
}

RtDictSchema* RtDictSchemaRemoveDict(RtDictSchema* schema, RtDict* dict) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEE80)(schema, dict);
}

RwBool RtDictSchemaForAllDictionaries(RtDictSchema* schema, RtDictCallBack* callback, RtDictEntryType data) {
    return ((RwBool(__cdecl *)(RtDictSchema*, RtDictCallBack*, RtDictEntryType))0x7CF5B0)(schema, callback, data);
}

RtDict* RtDictSchemaGetCurrentDict(RtDictSchema* schema) {
    return ((RtDict*(__cdecl *)(RtDictSchema*))0x7CEEE0)(schema);
}

RtDictSchema* RtDictSchemaSetCurrentDict(RtDictSchema* schema, RtDict* dict) {
    return ((RtDictSchema*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEEF0)(schema, dict);
}

RwBool RtDictDestroy(RtDict* dictionary) {
    return ((RwBool(__cdecl *)(RtDict*))0x7CF130)(dictionary);
}

RtDictEntryType RtDictAddEntry(RtDict* dictionary, RtDictEntryType entry) {
    return ((RtDictEntryType(__cdecl *)(RtDict*, RtDictEntryType))0x7CEFB0)(dictionary, entry);
}

RtDictEntryType RtDictFindNamedEntry(RtDict* dictionary, const RwChar* name) {
    return ((RtDictEntryType(__cdecl *)(RtDict*, const RwChar*))0x7CEFE0)(dictionary, name);
}

const RtDict* RtDictForAllEntries(const RtDict* dictionary, RtDictEntryCallBack* callBack, RtDictEntryType data) {
    return ((const RtDict*(__cdecl *)(const RtDict*, RtDictEntryCallBack*, RtDictEntryType))0x7CF060)(dictionary, callBack, data);
}

RtDict* RtDictRemoveEntry(RtDict* dictionary, RtDictEntryType entry) {
    return ((RtDict*(__cdecl *)(RtDict*, RtDictEntryType))0x7CF0C0)(dictionary, entry);
}

const RtDict* RtDictStreamWrite(const RtDict* dictionary, RwStream* stream) {
    return ((const RtDict*(__cdecl *)(const RtDict*, RwStream*))0x7CF490)(dictionary, stream);
}

RwUInt32 RtDictStreamGetSize(const RtDict* dictionary) {
    return ((RwUInt32(__cdecl *)(const RtDict*))0x7CF1F0)(dictionary);
}

RtDict* _rtDictSchemaInitDict(RtDictSchema* schema, RtDict* dictionary) {
    return ((RtDict*(__cdecl *)(RtDictSchema*, RtDict*))0x7CEF00)(schema, dictionary);
}

RwBool _rtDictDestruct(RtDict* dictionary) {
    return ((RwBool(__cdecl *)(RtDict*))0x7CEF60)(dictionary);
}
