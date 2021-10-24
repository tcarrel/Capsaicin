#pragma once



#include<type_traits>



template<typename Integer_Type>
constexpr Integer_Type BIT( Integer_Type place )
{
    if constexpr( std::is_integral_v<Integer_Type> )
    {
        return 1 << place;
    }
    else
    {
        static_assert( false, "Integral Required" );
        return place;
    }
}
