#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES

#include "CStreamingDebugModule.h"
#include "Streaming.h"

#include "imgui.h"

namespace CStreamingDebugModule {
void ProcessImGui() {
    using namespace ImGui;

    if (Button("ReInit")) {
        CStreaming::ReInit();
    }

    Text("Memory: %u Ki", CStreaming::ms_memoryUsed / 1024);
    Text("Buffer size: %u Sectors (%u Ki)", CStreaming::ms_streamingBufferSize, CStreaming::ms_streamingBufferSize * STREAMING_SECTOR_SIZE / 1024);

    {
        constexpr auto GetListSize = [](auto begin, auto end) {
            uint32 n{};
            for (auto it = begin->GetNext(); it != end; it = it->GetNext())
                n++;
            return n;
        };
        Text("Req. list size: %u", GetListSize(CStreaming::ms_pStartRequestedList, CStreaming::ms_pEndRequestedList));
        Text("Loaded list size: %u", GetListSize(CStreaming::ms_startLoadedList, CStreaming::ms_pEndLoadedList));
    }

    {
        constexpr auto GetChannelStatusStr = [](auto ch) {
            switch (CStreaming::ms_channel[ch].LoadStatus) {
            case eChannelState::IDLE:
                return "IDLE";
            case eChannelState::ERR:
                return "ERR";
            case eChannelState::STARTED:
                return "STARTED";
            case eChannelState::READING:
                return "READING";
            default:
                return "Unknown";
            }
        };

        Text("Ch #0 status: %s", GetChannelStatusStr(0));
        Text("Ch #1 status: %s", GetChannelStatusStr(1));
    }

    Text("Loading big model: %i", (int32)CStreaming::ms_bLoadingBigModel);
}

void ProcessRender() {

}
};
#endif
