/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as DAGGer PreCompiled Header
////////////////////////////////
#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "DAGGer/Core/Log.h"

#include "DAGGer/Debug/Instrumentor.h"

#include "DAGGer/Core/Base.h"

#ifdef Dr_PLATFORM_WINDOWS
	#include <Windows.h>
#endif