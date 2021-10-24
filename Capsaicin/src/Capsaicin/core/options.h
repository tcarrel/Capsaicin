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
        Application_Name
    };

    std::string get_field_string( Option_Field field );



    struct Capsaicin_Settings
    {
        enum class Option_Value_Type
        {
            Boolean          = BIT( 0 ),
            Unsigned_Integer = BIT( 1 ),
            Signed_Interger  = BIT( 2 ),
            Floating_Point   = BIT( 3 ),
            String           = BIT( 4 ),

            error            = 0
        };

        enum class Initialization_Status
        {
            FAILURE_NO_FALLBACK   = -4,
            ERROR_DEFAULTS_USED   = -3,
            MINOR_ERROR_IGNORING  = -2,
            MESSAGES_WERE_SET     = -1,
            INCOMPLETE            =  0,
            SUCCESS_WITH_MESSAGES =  1,
            SUCCESS               =  2
        };

        Capsaicin_Settings( int argc, char* argv[], std::filesystem::path ini_file_path = "" );

        Initialization_Status init_status() const;

        Option_Value_Type get_option_value_types( Option_Field option );

        bool        get_boolean_value( Option_Field field );
        uint64_t    get_unsigned_integer_value( Option_Field field );
        int64_t     get_integer_value( Option_Field field );
        long double get_float_value( Option_Field field );
        std::string get_string_value( Option_Field field );

    private:

        void set_defaults();
        void parse_ini_file_settings(std::filesystem::path path);
        void parse_command_line_args( int argc, char* argv[] );

        void set_status( Initialization_Status update_to );

        enum class Boolean_Options
        {
            Start_Fullscreen,

            Quantity,

            error
        };
        enum class Unsigned_Integer_Options
        {
            Screen_Width,
            Screen_Height,
            Log_Level,

            Quantity,

            error
        }; 
        enum class Signed_Integer_Options
        {
            Quantity,

            error
        };
        enum class Floating_Point_Options
        {
            Quantity,

            error
        };
        enum class String_Options
        {
            Application_Name,

            Quantity,

            error
        };

        static Initialization_Status s_init_status;

        static std::bitset<static_cast<size_t>( Boolean_Options::Quantity )>                    s_bool_settings;
        static std::array<uint64_t, static_cast<size_t>( Unsigned_Integer_Options::Quantity )>  s_uint_settings;
        static std::array<int64_t, static_cast<size_t>( Signed_Integer_Options::Quantity )>     s_int_settings;
        static std::array<long double, static_cast<size_t>( Floating_Point_Options::Quantity )> s_float_settings;
        static std::array<std::string, static_cast<size_t>( String_Options::Quantity )>         s_str_settings;
    };
}
