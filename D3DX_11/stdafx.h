#pragma once
#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>

#include <vector>
#include <map>

//	Renderer
#include "System/Renderer/DXRenderer.h"

//	Utility
#include "Utility/DefineUtility.h"

//	Managers
#include "Managers/Timer/Timer.h"
#include "Managers/Input/InputManager.h"

//	Global interfaces
#include "MainEntry/Interface/IScene.h"

#pragma comment(lib, "D3D11_ImGUI.lib")
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
