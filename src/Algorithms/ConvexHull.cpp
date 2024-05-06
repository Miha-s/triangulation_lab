#include "ConvexHull.hpp"

#include <algorithm>

int
orientation( sf::Vector2f a, sf::Vector2f b, sf::Vector2f c )
{
    double v = a.x * ( b.y - c.y ) + b.x * ( c.y - a.y ) + c.x * ( a.y - b.y );
    if ( v < 0 )
        return -1;  // clockwise
    if ( v > 0 )
        return +1;  // counter-clockwise
    return 0;
}

bool
cw( sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, bool include_collinear )
{
    int o = orientation( a, b, c );
    return o < 0 || ( include_collinear && o == 0 );
}
bool
collinear( sf::Vector2f a, sf::Vector2f b, sf::Vector2f c )
{
    return orientation( a, b, c ) == 0;
}

std::vector< sf::Vector2f >
convex_hull( const std::vector< sf::Vector2f >& a_, bool include_collinear )
{
    auto a = a_;
    sf::Vector2f p0 =
            *min_element( a.begin( ),
                          a.end( ),
                          []( sf::Vector2f a, sf::Vector2f b )
                          { return std::make_pair( a.y, a.x ) < std::make_pair( b.y, b.x ); } );
    sort( a.begin( ),
          a.end( ),
          [ &p0 ]( const sf::Vector2f& a, const sf::Vector2f& b )
          {
              int o = orientation( p0, a, b );
              if ( o == 0 )
                  return ( p0.x - a.x ) * ( p0.x - a.x ) + ( p0.y - a.y ) * ( p0.y - a.y )
                         < ( p0.x - b.x ) * ( p0.x - b.x ) + ( p0.y - b.y ) * ( p0.y - b.y );
              return o < 0;
          } );
    if ( include_collinear )
    {
        int i = (int)a.size( ) - 1;
        while ( i >= 0 && collinear( p0, a[ i ], a.back( ) ) )
            i--;
        reverse( a.begin( ) + i + 1, a.end( ) );
    }

    std::vector< sf::Vector2f > st;
    for ( int i = 0; i < (int)a.size( ); i++ )
    {
        while ( st.size( ) > 1
                && !cw( st[ st.size( ) - 2 ], st.back( ), a[ i ], include_collinear ) )
            st.pop_back( );
        st.push_back( a[ i ] );
    }

    if ( include_collinear == false && st.size( ) == 2 && st[ 0 ] == st[ 1 ] )
        st.pop_back( );

    return st;
}
