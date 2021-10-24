#pragma once



#include<memory>



#if defined(CP_DEBUG)
#   if defined(CP_PLATFORM_WINDOWS)
#       define CP_DEBUG_BREAK() __debugbreak()
#   elif defined(CP_PLATFORM_LINUX)
#       include<signal.h>
#       define CP_DEBUG_BREAK() raise(SIGTRAP)
#   else
#       error "Platform does not yet support debug break!"
#   endif
#   define CP_ENABLE_ASSERTS
#endif



#if defined( CP_PLATFORM_WINDOWS )
#   if defined(CP_DEBUG)
#       define CP_ENABLE_ASSERTS
#   endif
#else
#   error Only Windows is currently supported.
#endif



#if defined(CP_DEBUG)
#   define CP_NOEX
constexpr bool CP_START_FULLSCREEN{ false };
#else
#   define CP_NOEX noexcept
constexpr bool CP_START_FULLSCREEN{ true };
#endif


#define CP_EXPAND_MACRO(x) x
#define CP_STRINGIFY_MACRO(x) #x



namespace Capsaicin
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr Scope<T> create_scope( Args&& ... args )
    {
        return std::make_unique<T>( std::forward<Args>( args )... );
    }



    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr Ref<T> create_ref( Args&& ... args )
    {
        return std::make_shared<T>( std::forward<Args>( args )... );
    }
}



#include "log.h"
#include "assert.h"
