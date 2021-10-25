#include "cp-pch.h"

#include "text_utilities.h"



#include<algorithm>



namespace Capsaicin
{
    namespace Util
    {
        void lowercase( std::string& text )
        {
            std::transform( text.begin(), text.end(), text.begin(), []( unsigned char C ) -> unsigned char
                            {
                                return std::tolower( C );
                            } );
        }



        std::string lowercase_copy( const std::string& text )
        {
            std::string copy( text );
            lowercase( copy );
            return copy;
        }



        std::string bool_to_string( bool true_or_false )
        {
            if( true_or_false )
            {
                return "true";
            }
            else
            {
                return "false";
            }
        }

    }
}
