#pragma once

#include "DAGGer/Core/Base.h"
#include "DAGGer/Core/Log.h"
#include <filesystem>

#ifdef Dr_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define Dr_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { Dr##type##ERROR(msg, __VA_ARGS__); Dr_DEBUGBREAK(); } }
#define Dr_INTERNAL_ASSERT_WITH_MSG(type, check, ...) Dr_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define Dr_INTERNAL_ASSERT_NO_MSG(type, check) Dr_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", Dr_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define Dr_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define Dr_INTERNAL_ASSERT_GET_MACRO(...) Dr_EXPAND_MACRO( Dr_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, Dr_INTERNAL_ASSERT_WITH_MSG, Dr_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define Dr_ASSERT(...) Dr_EXPAND_MACRO( Dr_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define Dr_CORE_ASSERT(...) Dr_EXPAND_MACRO( Dr_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define Dr_ASSERT(...)
#define Dr_CORE_ASSERT(...)
#endif
