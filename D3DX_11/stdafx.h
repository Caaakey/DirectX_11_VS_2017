#pragma once
#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#if _DEBUG
#pragma comment(lib, "VLD/lib/vld.lib")
#include <VLD/vld.h>
#endif

//	X4717 Warning : effects deprecated for d3dcompiler_47
#pragma warning(disable : 4717)

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>

#include <vector>
#include <map>

//	Utility
#include "Utility/DefineUtility.h"
#include "Utility/Importer/ModelUtility.h"

//	Application
#include "System/Application.h"

#pragma comment(lib, "D3D11_ImGUI.lib")
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>

//	Renderer
#include "System/Renderer/DXRenderer.h"

//	Managers
#include "Managers/Timer/Timer.h"
#include "Managers/Input/InputManager.h"
#include "Managers/Camera/CameraManager.h"

//	Global interfaces

//	Objects
#include "_Scenes/SceneObject.h"
#include "_Objects/ObjectModel.h"