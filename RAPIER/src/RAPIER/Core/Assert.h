#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Log.h"
#include <filesystem>

#ifdef RP_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define RP_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { Dr##type##ERROR(msg, __VA_ARGS__); RP_DEBUGBREAK(); } }
#define RP_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RP_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define RP_INTERNAL_ASSERT_NO_MSG(type, check) RP_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RP_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define RP_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define RP_INTERNAL_ASSERT_GET_MACRO(...) RP_EXPAND_MACRO( RP_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RP_INTERNAL_ASSERT_WITH_MSG, RP_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define RP_ASSERT(...) RP_EXPAND_MACRO( RP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define RP_CORE_ASSERT(...) RP_EXPAND_MACRO( RP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define RP_ASSERT(...)
#define RP_CORE_ASSERT(...)
#endif
