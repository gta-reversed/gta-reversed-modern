#pragma once

#include <map>
#include <string>

class CDebugMenuToolInput
{
public:
    using ToolMap = std::map<std::int32_t, std::string>;
private:
    std::string m_inputBuffer;
    std::int32_t m_lastInputBufferSize = 0;
    ToolMap* m_originalGristListMap = nullptr;
    ToolMap m_gristListMap;
    size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos = 0);
public:
    void Initialise(std::int32_t inputBufferCapacity, ToolMap* OriginalMap);
    void Process();
    std::string& GetInputBuffer() { return m_inputBuffer; }
    ToolMap& GetGridListMap() { return m_gristListMap; }
};
