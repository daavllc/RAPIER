/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as DAGGer PreCompiled Header
////////////////////////////////
#pragma once

#include "DAGGer/Core/PlatformDetection.h"

#ifdef Dr_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "DAGGer/Core/Base.h"

#include "DAGGer/Core/Log.h"

#include "DAGGer/Debug/Instrumentor.h"

#ifdef Dr_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
