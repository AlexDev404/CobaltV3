#pragma once

const int VEH = 0; // VectoredExceptionHandler
const int MH = 1; // MinHook
const int KIERO = 2; // DX9, DX10, Vulkan, DX11, DX12, OpenGl, etc.

inline bool InitVEH = false;
inline bool InitMH = false;
inline bool InitKiero = false;