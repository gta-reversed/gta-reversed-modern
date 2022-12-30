#pragma once

namespace VideoPlayer {

void InjectHooks();

void Shutdown();
void WaitState(int32 state);
void OnGraphNotify();
void UpdateWindow();
void Release();
void Play(int32 nCmdShow, const char* path);

} // namespace VideoPlayer
