#pragma once



#include "Capsaicin/core/core.h"

#include<string>
#include<sstream>
#include<type_traits>



namespace Capsaicin
{
    namespace Util
    {
        void lowercase( std::string& text );
        std::string lowercase_copy( const std::string& text );

        template<typename Numeric_Type>
        std::string to_string( Numeric_Type number )
        {
            if constexpr( std::is_arithmetic_v<Numeric_Type> )
            {
                std::stringstream ss;
                ss << number;
                return ss.str();
            }

            CP_CORE_ASSERT( false, "Cannot convert argument to string.");
            return "";
        }
    }
}
