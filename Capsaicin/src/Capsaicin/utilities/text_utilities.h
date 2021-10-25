#pragma once



#include "Capsaicin/core/core.h"

#include<string>
#include<type_traits>



namespace Capsaicin
{
    namespace Util
    {
        void lowercase( std::string& text );
        std::string lowercase_copy( const std::string& text );

        std::string bool_to_string( bool true_or_false );
    }
}



#if 0 // Overloads for GLM types.
template<typename Output_Stream, glm::length_t Length, typename GLM_Type, glm::qualifier GLM_Qualifier>
Output_Stream& operator<<( Output_Stream& out, const glm::vec<Length, GLM_Type, GLM_Qualifier>& vector )
{
    return os << glm::to_string( vector );
}



template<typename Output_Stream, glm::length_t Columns, glm::length_t Rows, typename GLM_Type, glm::qualifier GLM_Qualifier>
Output_Stream& operator<<( Output_Stream& out, const glm::mat<Columns, Rows, GLM_Type, GLM_Qualifier>& matrix )
{
    return os << glm::to_string( matrix );
}



template<typename Output_Stream, typename GLM_Type, glm::qualifier GLM_Qualifier>
Output_Stream& operator<<( Output_Stream& out, const glm::qua<GLM_Type, GLM_Qualifier>& quaternion )
{
    return os << glm::to_string( quaternion );
}
#endif
