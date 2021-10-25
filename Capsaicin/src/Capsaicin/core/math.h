#pragma once



#include<cmath>
#include<type_traits>



constexpr auto EPSILON{ static_cast<long double>( 0.00000005 ) };



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



namespace Float
{
    template<typename Floating_Point_Type>
    bool eq( const Floating_Point_Type& lhs, const Floating_Point_Type& rhs )
    {
        if constexpr( std::is_floating_point_v<Floating_Point_Type> )
        {
            return abs( lhs - rhs ) <= EPSILON;
        }
        else
        {
            CP_WARN( "Floating point comparison functions are only needed for floating point values." );
            CP_WARN( "   Standard boolean operators are prefered for non-floating point types." );
            return lhs == rhs;
        }
    }



    template<typename Floating_Point_Type>
    bool neq( const Floating_Point_Type& lhs, const Floating_Point_Type& rhs )
    {
        if constexpr( std::is_floating_point_v<Floating_Point_Type> )
        {
            return !eq( lhs, rhs );
        }
    }



    template<typename Floating_Point_Type>
    bool eq_0( Floating_Point_Type fp_value )
    {
        if constexpr( std::is_floating_point_v<Floating_Point_Type> )
        {
            return eq( fp_value, static_cast<Floating_Point_Type>( 0.0f ) );
        }
    }



    template<typename Floating_Point_Type>
    bool neq_0( Floating_Point_Type fp_value )
    {
        if constexpr( std::is_floating_point_v<Floating_Point_Type> )
        {
            return neq( fp_value, static_cast<Floating_Point_Type>( 0.0f ) );
        }
    }
}
