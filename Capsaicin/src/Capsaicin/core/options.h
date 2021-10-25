#pragma once

//#include "core.h"
#include "Capsaicin/core/math.h"

#include<array>
#include<bitset>
#include<filesystem>
#include<string>
#include<type_traits>



namespace Capsaicin
{
    enum class Option_Field
    {
        // Boolean
        Start_Fullscreen,

        // Unsigned Integer
        Screen_Width,
        Screen_Height,
        Log_Level,

        // Signed Integer


        // Floating point


        // String
        Executable_Name
    };

    std::string get_field_string( Option_Field field );



    struct Capsaicin_Settings
    {

        Capsaicin_Settings();
        Capsaicin_Settings( int argc, char* argv[], std::filesystem::path ini_file_path = "" );

        bool set_start_fullsceen( std::string start_fullscreen );
        bool set_screen_width( std::string pixels_wide );
        bool set_screen_height( std::string  pixels_high );
        bool set_log_level( std::string log_level );
        bool set_exe_name( std::string exe );

    private:

        void set_defaults();
        void parse_ini_file_settings(std::filesystem::path path);
        void parse_command_line_args( int argc, char* argv[] );

        bool parse_boolean( std::string boolean_string, bool& return_value );

        enum class Boolean_Options
        {
            Start_Fullscreen,

            Quantity
        };
        enum class Unsigned_Integer_Options
        {
            Screen_Width, Screen_Height, Log_Level,

            Quantity
        };
        enum class Signed_Integer_Options
        {
            Quantity
        };
        enum class Floating_Point_Options
        {
            Quantity
        };
        enum class String_Options
        {
            Executable_Name,

            Quantity
        };

        static std::bitset<static_cast<size_t>( Boolean_Options::Quantity )>                    s_bool_settings;
        static std::array<uint64_t, static_cast<size_t>( Unsigned_Integer_Options::Quantity )>  s_uint_settings;
        static std::array<int64_t, static_cast<size_t>( Signed_Integer_Options::Quantity )>     s_int_settings;
        static std::array<long double, static_cast<size_t>( Floating_Point_Options::Quantity )> s_float_settings;
        static std::array<std::string, static_cast<size_t>( String_Options::Quantity )>         s_str_settings;
    };
}
