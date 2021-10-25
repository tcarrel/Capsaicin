#pragma once


#include "Capsaicin/core/core.h"

#if 0
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#endif

#include<filesystem>

#pragma warning(push, 0)
#include<spdlog/spdlog.h>
#include<spdlog/fmt/ostr.h>
#pragma warning(pop)




namespace Capsaicin
{
    struct Log
    {
        static void init( spdlog::level::level_enum show_at_least = spdlog::level::warn,
                          const std::filesystem::path& log_file = "Capsaicin.log" );

        static Ref<spdlog::logger>& get_core_logger();

        static bool is_initialized();

        static void set_log_level( spdlog::level::level_enum log_level );
        static void set_flush_level( spdlog::level::level_enum flush_on );

    private:

        static bool s_is_initialized;
        static Ref<spdlog::logger> s_core_logger;
    };
}



// Core logging macros
#define CP_TRACE(...)    ::Capsaicin::Log::get_core_logger()->trace(__VA_ARGS__)
#define CP_INFO(...)     ::Capsaicin::Log::get_core_logger()->info(__VA_ARGS__)
#define CP_WARN(...)     ::Capsaicin::Log::get_core_logger()->warn(__VA_ARGS__)
#define CP_ERROR(...)    ::Capsaicin::Log::get_core_logger()->error(__VA_ARGS__)
#define CP_CRITICAL(...) ::Capsaicin::Log::get_core_logger()->critical(__VA_ARGS__)
