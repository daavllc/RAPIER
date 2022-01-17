#pragma once

#include "RAPIER/Core/PlatformDetection.h"

#ifdef RP_PLATFORM_WINDOWS
	#include <Windows.h>
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
#include <fstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Log.h"

#include "RAPIER/Debug/Profiler.h"
