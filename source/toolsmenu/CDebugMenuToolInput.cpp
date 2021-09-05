#include "StdInc.h"
#include <sstream>
#include "CDebugMenuToolInput.h"

void CDebugMenuToolInput::Initialise(int32 inputBufferCapacity, ToolMap* OriginalMap)
{
    m_inputBuffer.reserve(inputBufferCapacity);
    m_originalGristListMap = OriginalMap;
    m_gristListMap = *m_originalGristListMap;
}

size_t CDebugMenuToolInput::findCaseInsensitive(std::string data, std::string toSearch, size_t pos)
{
    // Convert complete given String to lower case
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    // Convert complete given Sub String to lower case
    std::transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    // Find sub string in given string
    return data.find(toSearch, pos);
}

void CDebugMenuToolInput::Process()
{
    if (m_inputBuffer.size() != m_lastInputBufferSize) {
        m_lastInputBufferSize = m_inputBuffer.size();
        if (m_lastInputBufferSize == 0) {
            m_gristListMap = *m_originalGristListMap;
        }
        else {
            m_gristListMap.clear();
            int32 id = 0;
            std::stringstream sstream(m_inputBuffer);
            sstream >> id;
            bool checkWithID = !sstream.fail();
            for (const auto& x : *m_originalGristListMap) {
                const std::string& name = x.second;
                if ((checkWithID && x.first == id) || findCaseInsensitive(name, m_inputBuffer) != std::string::npos) {
                    m_gristListMap[x.first] = x.second;
                }
            }
        }
    }
}
