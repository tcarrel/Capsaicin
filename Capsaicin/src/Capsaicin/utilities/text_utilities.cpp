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
    }
}
