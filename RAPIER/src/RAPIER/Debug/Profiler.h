#pragma once

#include <optick.h>

#if RP_ENABLE_PROFILING
	#define RP_PROFILE_FRAME(...)           OPTICK_FRAME(__VA_ARGS__)
	#define RP_PROFILE_FUNC(...)            OPTICK_EVENT(__VA_ARGS__)
	#define RP_PROFILE_TAG(NAME, ...)       OPTICK_TAG(NAME, __VA_ARGS__)
	#define RP_PROFILE_SCOPE_DYNAMIC(NAME)  OPTICK_EVENT_DYNAMIC(NAME)
	#define RP_PROFILE_THREAD(...)          OPTICK_THREAD(__VA_ARGS__)
#else
	#define RP_PROFILE_FRAME(...)
	#define RP_PROFILE_FUNC()
	#define RP_PROFILE_TAG(NAME, ...) 
	#define RP_PROFILE_SCOPE_DYNAMIC(NAME)
	#define RP_PROFILE_THREAD(...)
#endif

#if RP_ENABLE_RENDERER_PROFILING
	#define RP_PROFILE_RENDERER_FUNC(...) RP_PROFILE_FUNC(__VA_ARGS__)
#else
	#define RP_PROFILE_RENDERER_FUNC(...)
#endif
