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

#include "Utility/DefineUtility.h"
#include "Managers/Timer/Timer.h"
