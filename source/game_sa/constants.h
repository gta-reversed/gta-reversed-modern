#pragma once
#include <cstdint>

// used in CStreaming
const std::uint32_t TOTAL_DFF_MODEL_IDS = 20000;
const std::uint32_t TOTAL_TXD_MODEL_IDS = 5000;
const std::uint32_t TOTAL_COL_MODEL_IDS = 255;
const std::uint32_t TOTAL_IPL_MODEL_IDS = 256;
const std::uint32_t TOTAL_DAT_MODEL_IDS = 64;
const std::uint32_t TOTAL_IFP_MODEL_IDS = 180;
const std::uint32_t TOTAL_RRR_MODEL_IDS = 475;
const std::uint32_t TOTAL_SCM_MODEL_IDS = 82;
const std::uint32_t TOTAL_INTERNAL_MODEL_IDS = 4; // internal use?

const std::uint32_t TOTAL_IMG_ARCHIVES = 8;
const std::uint32_t TOTAL_LOADED_PEDS = 8;
const std::uint32_t TOTAL_GANGS = 10;

const std::uint32_t TOTAL_SCRIPTED_TASKS = 128;
const std::uint32_t TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES = 48;
const std::int32_t TOTAL_DECISION_MAKERS = 20;
const std::int32_t TOTAL_PED_GROUPS = 8;

// used in CRenderer
const std::int32_t TOTAL_ENTITY_SCAN_LISTS = 5;
const float MAX_LOD_DISTANCE = 300.0f;
const float MAX_LOWLOD_DISTANCE = 150.0f;
const float MAX_FADING_DISTANCE = 20.0f;
const float MAX_STREAMING_DISTANCE = 50.0f;
const float MAX_INVISIBLE_ENTITY_DISTANCE = 30.0f;
const float MAX_INVISIBLE_VEHICLE_DISTANCE = 200.0f;
const float MAX_STREAMING_RADIUS = 10000.0f;
const float STREAMING_ANGLE_THRESHOLD = 20.62648f;
const float MAX_BIGBUILDING_STREAMING_RADIUS = 80000.0f;
const float BIGBUILDING_STREAMING_ANGLE_THRESHOLD = 40.107f;
const float LOWLOD_CAMERA_HEIGHT_THRESHOLD = 80.0f;
