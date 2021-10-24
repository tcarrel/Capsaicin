#include "cp-pch.h"



#include "core.h"
#include "log.h"
#include<array>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/basic_file_sink.h>



namespace Capsaicin
{
    bool Log::s_is_initialized{ false };
    Ref<spdlog::logger> Log::s_core_logger;
//    Ref<spdlog::logger> Log::s_client_logger;



    void Log::init(spdlog::level::level_enum show_at_least, const std::filesystem::path& log_file )
    {
        if( !s_is_initialized )
        {
            std::array<spdlog::sink_ptr, 2> sinks{
                create_ref<spdlog::sinks::stdout_color_sink_mt>(),
                //create_ref<spdlog::sinks::basic_file_sink_mt>( log_file.c_str(), true ) };
                create_ref<spdlog::sinks::basic_file_sink_mt>( "Capsaicin.log", true ) };

            sinks[ 0 ]->set_pattern( "%^[%T] %n: %v%$" );
            sinks[ 1 ]->set_pattern( "[%T] [%l] %n: %v" );

            s_core_logger = create_ref<spdlog::logger>( "CAPSAICIN", begin( sinks ), end( sinks ) );
            spdlog::register_logger( s_core_logger );
            //s_core_logger->set_level( spdlog::level::trace );
            s_core_logger->flush_on( show_at_least );

            //   Capsaicin should not do logging for client applications.  Keeping this here, for now,
            // in case I change my mind.
            //s_client_logger = create_ref<spdlog::logger>( "APP      ", begin( sinks ), end( sinks ) );
            //spdlog::register_logger( s_client_logger );
            ////s_client_logger->set_level( spdlog::level::trace );
            //s_client_logger->flush_on( spdlog::level::trace );

            s_is_initialized = true;
        }
    }



    Ref<spdlog::logger>& Log::get_core_logger()
    {
        return s_core_logger;
    }



    bool Log::is_initialized()
    {
        return s_is_initialized;
    }



    //   Capsaicin should not do logging for client applications.  Keeping this here, for now,
    // in case I change my mind.
    //Ref<spdlog::logger>& Log::get_client_logger()
    //{
    //    return s_client_logger;
    //}
}
