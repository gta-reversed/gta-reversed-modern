/**
 * nick7 @ 2015/12/19 23:48
 */

#pragma once

#include "Base.h"

extern bool ReadLine(FILESTREAM file, char* pszBuffer, int32 iBufferSize);

namespace traits {

template <typename type>
struct fx_field_scanf_format;

template <>
struct fx_field_scanf_format<int32> {
    static inline const char* value() {
        return "%s %d";
    }
};

template <>
struct fx_field_scanf_format<float> {
    static inline const char* value() {
        return "%s %f";
    }
};

template <int32 size>
struct fx_field_scanf_format<char[size]> {
    static inline const char* value() {
        return "%s %s";
    }
};

} // namespace traits

template <typename Type>
inline void ReadFieldImpl(FILESTREAM file, Type& refValue, const char* fieldName = nullptr) {
    char line[256], field[128];
    ReadLine(file, line, sizeof(line));
    if (fieldName == nullptr) {
        // todo: ASSERT(!strncmp(line, fieldName, strlen(fieldName)), "Line: %s\nRequested field: %s", line, fieldName);
    }
    RET_IGNORED(sscanf(line, traits::fx_field_scanf_format<Type>::value(), field, &refValue));
}

template <typename Type>
Type ReadField(FILESTREAM file, const char* fieldName = nullptr);

template <typename Type>
Type ReadField(FILESTREAM file, const char* fieldName) {
    Type value;
    ReadFieldImpl(file, value, fieldName);
    return value;
}

template <>
inline void ReadField<void>(FILESTREAM file, const char* fieldName) {
    char line[256], field[128];
    ReadLine(file, line, sizeof(line));
    RET_IGNORED(sscanf(line, "%s", field));
}

template <>
inline int8 ReadField<int8>(FILESTREAM file, const char* fieldName) {
    return (int8)ReadField<int32>(file, fieldName);
}

template <>
inline uint8 ReadField<uint8>(FILESTREAM file, const char* fieldName) {
    return (uint8)ReadField<int32>(file, fieldName);
}

template <>
inline bool ReadField<bool>(FILESTREAM file, const char* fieldName) {
    return ReadField<int32>(file, fieldName) != 0;
}
