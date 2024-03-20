#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <DirectXMath.h>
#include <cmath>
#include <cstdlib>

#include <array>
#include <memory>
#include <string>
#include "Utils.h"

#define FRAMEBUFFER_WIDTH		640
#define FRAMEBUFFER_HEIGHT		480

#define RANDOM_COLOR			(0xFF000000 | ((rand() * 0xFFFFFF) / RAND_MAX))

#define DegreeToRadian(x)		float((x)*3.141592654f/180.0f)

#define EPSILON					1.0e-2f

inline bool IsZero(float fValue) { return((std::fabsf(fValue) <= EPSILON)); }
inline bool IsEqual(float fA, float fB) { return(::IsZero(fA - fB)); }