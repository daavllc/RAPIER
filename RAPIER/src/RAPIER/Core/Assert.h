#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Log.h"
#include <filesystem>

#ifdef RP_ENABLE_ASSERTS
	#define RP_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { Dr##type##ERROR(msg, __VA_ARGS__); RP_DEBUGBREAK(); } }
	#define RP_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RP_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define RP_INTERNAL_ASSERT_NO_MSG(type, check) RP_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RP_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define RP_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define RP_INTERNAL_ASSERT_GET_MACRO(...) RP_EXPAND_MACRO( RP_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RP_INTERNAL_ASSERT_WITH_MSG, RP_INTERNAL_ASSERT_NO_MSG) )

	// Accepts the condition, and an optional message
	#define RP_ASSERT(...) RP_EXPAND_MACRO( RP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define RP_CORE_ASSERT(...) RP_EXPAND_MACRO( RP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define RP_ASSERT(...)
	#define RP_CORE_ASSERT(...)
#endif

#ifdef RP_ENABLE_VERIFY
	#define RP_VERIFY_NO_MESSAGE(condition) { if(!(condition)) { RP_ERROR("Verify Failed"); __debugbreak(); } }
	#define RP_VERIFY_MESSAGE(condition, ...) { if(!(condition)) { RP_ERROR("Verify Failed: {0}", __VA_ARGS__); __debugbreak(); } }

	#define RP_VERIFY_RESOLVE(arg1, arg2, macro, ...) macro
	#define RP_GET_VERIFY_MACRO(...) RP_EXPAND_VARGS(RP_VERIFY_RESOLVE(__VA_ARGS__, RP_VERIFY_MESSAGE, RP_VERIFY_NO_MESSAGE))

	#define RP_VERIFY(...) RP_EXPAND_VARGS( RP_GET_VERIFY_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define RP_CORE_VERIFY(...) RP_EXPAND_VARGS( RP_GET_VERIFY_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define RP_VERIFY(...)
	#define RP_CORE_VERIFY(...)
#endif
