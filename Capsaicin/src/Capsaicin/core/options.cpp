#include "cp-pch.h"

#include "core.h"
#include "options.h"

#include "Capsaicin/utilities/text_utilities.h"

#include<unordered_map>
//  #include<format>   // C++ 20!!



namespace Capsaicin
{
    Capsaicin_Settings::Initialization_Status Capsaicin_Settings::s_init_status
    {
        Capsaicin_Settings::Initialization_Status::INCOMPLETE
    };



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



    Capsaicin_Settings::Capsaicin_Settings( int argc, char* argv[], std::filesystem::path ini_file_path )
    {
        set_defaults();
        parse_ini_file_settings( ini_file_path );
        parse_command_line_args( argc, argv );

        switch( s_init_status )
        {
        case Initialization_Status::MESSAGES_WERE_SET:
            s_init_status = Initialization_Status::SUCCESS_WITH_MESSAGES;
            return;
        case Initialization_Status::INCOMPLETE:
            s_init_status = Initialization_Status::SUCCESS;
            return;
        default:
            return;
        }
    }

    
    
    Capsaicin_Settings::Initialization_Status Capsaicin_Settings::init_status() const
    {
        return s_init_status;
    }



    void Capsaicin_Settings::set_defaults()
    {
        s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] = CP_START_FULLSCREEN;
        
        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] = 1024;
        s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] = 768;

        s_str_settings[ static_cast<size_t>( String_Options::Application_Name ) ] = "Capsaicin Rendered Application";
    }



    void Capsaicin_Settings::parse_ini_file_settings( std::filesystem::path path )
    {
        // TODO.
    }



    void Capsaicin_Settings::parse_command_line_args( int argc, char* argv[] )
    {
        s_str_settings[ static_cast<size_t>( String_Options::Application_Name ) ] = argv[ 0 ];

        for( int i{ 1 }; i < argc; ++i )
        {

        }
    }

    
    
    void Capsaicin_Settings::set_status( Initialization_Status update_to )
    {
        const auto current_status{ static_cast<int>( s_init_status ) };
        const auto new_status{ static_cast<int>( update_to ) };

        if( new_status < current_status )
        {
            s_init_status = update_to;
        }
    }



    Capsaicin_Settings::Option_Value_Type Capsaicin_Settings::get_option_value_types( Option_Field option )
    {
        switch( option )
        {
        case Option_Field::Start_Fullscreen:
            return Option_Value_Type::Boolean;
        case Option_Field::Screen_Width:  [[fallthrough]];
        case Option_Field::Screen_Height: [[fallthrough]];
        case Option_Field::Log_Level:
            return Option_Value_Type::Unsigned_Integer;
        case Option_Field::Application_Name:
            return Option_Value_Type::String;

        default:
            // static assert?
            return Option_Value_Type::error;
        }
    }



    bool Capsaicin_Settings::get_boolean_value( Option_Field field )
    {
        switch( field )
        {
        case Option_Field::Start_Fullscreen:
            return s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ];

        default:
            CP_CORE_WARN( "Could not convert " + get_field_string( field ) + " to bool.  Returning <false>." );
            return false;
        }
    }



    uint64_t Capsaicin_Settings::get_unsigned_integer_value( Option_Field field )
    {
        switch( field )
        {
        case Option_Field::Start_Fullscreen:
            return static_cast<uint64_t>( s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] );
        case Option_Field::Screen_Width:
            return s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ];
        case Option_Field::Screen_Height:
            return s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ];
        case Option_Field::Log_Level:
            return s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ];
        default:
            CP_CORE_WARN( "Could not convert "
                          + get_field_string( field )
                          + " to unsigned int.  Returning <18446744073709551615>." );
            return 0xFFFF'FFFF'FFFF'FFFF;
        }
    }



    int64_t Capsaicin_Settings::get_integer_value( Option_Field field )
    {
        switch( field )
        {
        case Option_Field::Start_Fullscreen:
            return static_cast<int64_t>( s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] );
        case Option_Field::Screen_Width:
            return static_cast<int64_t>( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] );
        case Option_Field::Screen_Height:
            return static_cast<int64_t>( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] );
        case Option_Field::Log_Level:
            return static_cast<int64_t>( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ] );
        default:
            CP_CORE_WARN( "Could not convert " + get_field_string( field ) + " to signed int.  Returning <-9,223,372,036,854,775,808>" );
            return -static_cast<int64_t>( 9'223'372'036'854'775'808 );
        }
    }



    long double Capsaicin_Settings::get_float_value( Option_Field field )
    {
        long double return_value{ 0 };
        switch( field )
        {
        case Option_Field::Start_Fullscreen:
            return_value = static_cast<long double>( s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] );
            CP_CORE_WARN( "Casting boolean value <{}> was cast to floating point value <{}>.",
                          s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ],
                          return_value );
            return return_value;
        case Option_Field::Screen_Width:
            return_value = static_cast<long double>( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] );
            CP_CORE_WARN( "Casting unsigned int value <{}> to floating point <{}>.",
                          s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ],
                          return_value );
            return return_value;
        case Option_Field::Screen_Height:
            return_value = static_cast<long double>( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] );
            CP_CORE_WARN( "Casting unsigned int value <{}> to floating point <{}>.",
                          s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ],
                          return_value );
            return return_value;
        case Option_Field::Log_Level:
            return_value = static_cast<long double>( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ] );
            CP_CORE_WARN( "Casting unsigned int value <{}> to floating point <{}>.",
                          s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ],
                          return_value );
            return return_value;
        default:
            CP_CORE_ERROR( "Could not convert {} to floating point.  Returning <0.0>", get_field_string( field ) );
            return 0.0;
        }
    }



    std::string Capsaicin_Settings::get_string_value( Option_Field field )
    {
        switch( field )
        {
        case Option_Field::Start_Fullscreen:
            CP_CORE_WARN( "Returning bool ({}) as a string.", get_field_string( field ) );
            return s_bool_settings[ static_cast<size_t>( Boolean_Options::Start_Fullscreen ) ] ? "true" : "false";
        case Option_Field::Screen_Width:
            CP_CORE_WARN( "Returning bool ({}) as a string.", get_field_string( field ) );
            return Util::to_string( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] );
            //return std::format( "{}", s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Width ) ] );
        case Option_Field::Screen_Height:
            CP_CORE_WARN( "Returning bool ({}) as a string.", get_field_string( field ) );
            return Util::to_string( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] );
            //return std::format( "{}", s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Screen_Height ) ] );
        case Option_Field::Log_Level:
            CP_CORE_WARN( "Returning bool ({}) as a string.", get_field_string( field ) );
            return Util::to_string( s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ] );
            //return std::format( "{}", s_uint_settings[ static_cast<size_t>( Unsigned_Integer_Options::Log_Level ) ] );
        case Option_Field::Application_Name:
            return s_str_settings[ static_cast<size_t>( String_Options::Application_Name ) ];
        }
        return "";
    }
    


    std::string get_field_string( Option_Field field )
    {
        switch( field )
        {
        case Option_Field::Start_Fullscreen:  return "start_fullscreen";
        case Option_Field::Screen_Width:      return "screen_width";
        case Option_Field::Screen_Height:     return "screen_height";
        case Option_Field::Log_Level:         return "log_level";
        case Option_Field::Application_Name:  return "app_name";

        default: return "UNKNOWN // ERROR";
        }
    }
}
