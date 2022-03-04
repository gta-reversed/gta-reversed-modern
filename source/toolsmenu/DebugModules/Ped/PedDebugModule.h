#pragma once

namespace PedDebugModule {

void SpawnPed(int32 modelId, CVector position);
void SpawnRandomPed();

void Initialise();
void ProcessImGui();
void ProcessRender();

} // namespace PedDebugModule