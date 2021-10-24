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

    //   Capsaicin should not do logging for client applications.  Keeping the functions for that here,
    // for now, in case I change my mind.


    struct Log
    {
        static void init( spdlog::level::level_enum show_at_least = spdlog::level::warn,
                          const std::filesystem::path& log_file = "Capsaicin.log" );

        static Ref<spdlog::logger>& get_core_logger();
        //static Ref<spdlog::logger>& get_client_logger();

        static bool is_initialized();

    private:

        static bool s_is_initialized;
        static Ref<spdlog::logger> s_core_logger;
        //static Ref<spdlog::logger> s_client_logger;
    };
}



#if 0
template<typename Output_Stream, glm::length_t Length, typename GLM_Type, glm::qualifier GLM_Qualifier>
inline Output_Stream& operator<<( Output_Stream& out, const glm::vec<Length, GLM_Type, GLM_Qualifier>& vector )
{
    return os << glm::to_string( vector );
}



template<typename Output_Stream, glm::length_t Columns, glm::length_t Rows, typename GLM_Type, glm::qualifier GLM_Qualifier>
inline Output_Stream& operator<<( Output_Stream& out, const glm::mat<Columns, Rows, GLM_Type, GLM_Qualifier>& matrix )
{
    return os << glm::to_string( matrix );
}



template<typename Output_Stream, typename GLM_Type, glm::qualifier GLM_Qualifier>
inline Output_Stream& operator<<( Output_Stream& out, const glm::qua<GLM_Type, GLM_Qualifier>& quaternion )
{
    return os << glm::to_string( quaternion );
}
#endif



// Core logging macros
#define CP_CORE_TRACE(...)    ::Capsaicin::Log::get_core_logger()->trace(__VA_ARGS__)
#define CP_CORE_INFO(...)     ::Capsaicin::Log::get_core_logger()->info(__VA_ARGS__)
#define CP_CORE_WARN(...)     ::Capsaicin::Log::get_core_logger()->warn(__VA_ARGS__)
#define CP_CORE_ERROR(...)    ::Capsaicin::Log::get_core_logger()->error(__VA_ARGS__)
#define CP_CORE_CRITICAL(...) ::Capsaicin::Log::get_core_logger()->critical(__VA_ARGS__)



//   Capsaicin should not do logging for client applications, however I'm keeping this here, for now,
// in case I change my mind.

// Client logging macros
//#define CP_TRACE(...)         ::Capsaicin::Log::get_client_logger()->trace(__VA_ARGS__)
//#define CP_INFO(...)          ::Capsaicin::Log::get_client_logger()->info(__VA_ARGS__)
//#define CP_WARN(...)          ::Capsaicin::Log::get_client_logger()->warn(__VA_ARGS__)
//#define CP_ERROR(...)         ::Capsaicin::Log::get_client_logger()->error(__VA_ARGS__)
//#define CP_CRITICAL(...)      ::Capsaicin::Log::get_client_logger()->critical(__VA_ARGS__)
