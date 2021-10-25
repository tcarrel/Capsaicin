#include "cp-pch.h"

#include "Capsaicin/core/core.h"
#include "Capsaicin/core/math.h"
#include "Capsaicin/core/options.h"

#include "Capsaicin/utilities/text_utilities.h"

#include<unordered_map>
//  #include<format>   // C++ 20!!



namespace Capsaicin
{
    std::bitset<static_cast<size_t>( Capsaicin_Settings::Boolean_Options::Quantity )> 
        Capsaicin_Settings::s_bool_settings;
    std::array<uint64_t, static_cast<size_t>( Capsaicin_Settings::Unsigned_Integer_Options::Quantity )>
        Capsaicin_Settings::s_uint_settings;
    std::array<int64_t, static_cast<size_t>( Capsaicin_Settings::Signed_Integer_Options::Quantity )>
        Capsaicin_Settings::s_int_settings;
    std::array<long double, static_cast<size_t>( Capsaicin_Settings::Floating_Point_Options::Quantity )>
        Capsaicin_Settings::s_float_settings;
    std::array<std::string, static_cast<size_t>( Capsaicin_Settings::String_Options::Quantity )>
        Capsaicin_Settings::s_str_settings;



    Capsaicin_Settings::Capsaicin_Settings()
    {
        set_defaults();
    }



    Capsaicin_Settings::Capsaicin_Settings( int argc, char* argv[], std::filesystem::path ini_file_path )
        :
        Capsaicin_Settings()
    {
        parse_ini_file_settings( ini_file_path );
        parse_command_line_args( argc, argv );
    }



    void Capsaicin_Settings::set_defaults()
    {
        s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] = CP_START_FULLSCREEN;
        
        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] = CP_DEFAULT_SCREEN_WIDTH;
        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] = CP_DEFAULT_SCREEN_HEIGHT;

        s_str_settings[ static_cast<size_t>( String_Options::Executable_Name ) ] = "Capsaicin Rendered Application";
    }



    void Capsaicin_Settings::parse_ini_file_settings( std::filesystem::path path )
    {
        if( std::filesystem::exists( path ) )
        {
            // TODO: parse file.
        }
        else
        {
            // TODO: write default .ini file.
        }
    }



    void Capsaicin_Settings::parse_command_line_args( int argc, char* argv[] )
    {
        CP_ASSERT( argc >= 1, "<argc> Must be at least 1." );

        s_str_settings[ static_cast<size_t>( String_Options::Executable_Name ) ] = argv[ 0 ];

        for( int i{ 1 }; i < argc; ++i )
        {

        }
    }

    
    
    bool Capsaicin_Settings::parse_boolean( std::string boolean_string, bool& return_value )
    {
        static const std::unordered_map<std::string, bool> options{
            { "true", true},
            { "false", false},
            { "0", false },
            { "1", true },
            { "on", true },
            { "off", false }
        };

        auto position{ options.find( boolean_string ) };

        if( position == options.end() )
        {
            return FAILURE;
        }

        return_value = position->second;
        return SUCCESS;
    }



    bool Capsaicin_Settings::set_start_fullsceen( std::string start_fullscreen )
    {
        bool set_to{ CP_START_FULLSCREEN };

        if( parse_boolean( start_fullscreen, set_to ) == SUCCESS )
        {
            s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] = set_to;
            return SUCCESS;
        }

        CP_ERROR( "Unknown value for start_fullscreen.  {" + start_fullscreen + "}.  Boolean Expected." );
        return FAILURE;
    }



    bool Capsaicin_Settings::set_screen_width( std::string pixels_wide )
    {
        // TODO: Add try catch.
        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] = std::stoull( pixels_wide );
        return SUCCESS;
    }



    bool Capsaicin_Settings::set_screen_height( std::string pixels_high )
    {
        // TODO: ^
        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] = std::stoull( pixels_high );
        return SUCCESS;
    }



    bool Capsaicin_Settings::set_log_level( std::string log_level )
    {
        static const std::unordered_map<std::string, spdlog::level::level_enum> levels{
            { "mute",       spdlog::level::level_enum::critical },
            { "off",        spdlog::level::level_enum::critical },
            { "0",          spdlog::level::level_enum::critical },
            { "quiet",      spdlog::level::level_enum::err },
            { "min",        spdlog::level::level_enum::err },
            { "minimum",    spdlog::level::level_enum::err },
            { "1",          spdlog::level::level_enum::err },
            { "warn",       spdlog::level::level_enum::warn },
            { "2",          spdlog::level::level_enum::warn },
            { "verbose",    spdlog::level::level_enum::trace },
            { "everything", spdlog::level::level_enum::trace },
            { "3",          spdlog::level::level_enum::trace } };

        auto pos{ levels.find( log_level ) };
        if( pos == levels.end() )
        {
            CP_ERROR( "Log level {" + log_level + "} could not be interpreted." );
            CP_INFO( "  Possible Levels are:" );
            CP_INFO( "      mute / off / 0            : Dissable almost all logging." );
            CP_INFO( "      quiet / min / minimum / 1 : Only show error messages." );
            CP_INFO( "      warn / 2                  : Show errors and warnings." );
            CP_INFO( "      verbose / everything / 3  : Log *everything*." );
            return FAILURE;
        }

        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ] = pos->second;
        return SUCCESS;
    }

    
    
    bool Capsaicin_Settings::set_exe_name( std::string exe )
    {
        s_str_settings[ static_cast<size_t>( String_Options::Executable_Name ) ] = exe;
        return SUCCESS;
    }
}
