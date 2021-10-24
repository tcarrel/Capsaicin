#pragma once



#include "Capsaicin/core/core.h"
#include "Capsaicin/core/log.h"

#include<filesystem>



#if defined(CP_ENABLE_ASSERTS)

#   define CP_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CP##type##ERROR(msg, __VA_ARGS__); CP_DEBUG_BREAK(); } }
#   define CP_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CP_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#   define CP_INTERNAL_ASSERT_NO_MSG(type, check) CP_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CP_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#   define CP_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#   define CP_INTERNAL_ASSERT_GET_MACRO(...) CP_EXPAND_MACRO( CP_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CP_INTERNAL_ASSERT_WITH_MSG, CP_INTERNAL_ASSERT_NO_MSG) )

#   define CP_ASSERT(...) CP_EXPAND_MACRO( CP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#   define CP_CORE_ASSERT(...) CP_EXPAND_MACRO( CP_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#   define CP_ASSERT(...)
#   define CP_CORE_ASSERT(...)
#endif
