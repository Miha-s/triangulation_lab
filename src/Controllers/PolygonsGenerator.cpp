#include "PolygonsGenerator.hpp"
#include <iostream>

std::vector< std::vector< sf::Vector2f > >
PolygonsGenerator::generate( sf::Rect< float > area, int number_of_polygons, int number_of_edges )
{
    m_number_of_polygons = number_of_polygons;
    m_number_of_edges = number_of_edges;

    init_random_generators( area );

    auto circles = generate_polygons_circles( );

    return generate_polygons_from_circles( circles );
}

std::vector< Circle >
PolygonsGenerator::generate_polygons_circles( )
{
    std::vector< Circle > circles;
    for ( int i = 0; i < m_number_of_polygons; )
    {
        auto point = random_point( );
        auto radius = m_random_radius.get_number( );
        Circle new_circle{ point, radius };

        bool bad_circle = false;
        for ( const auto& circle : circles )
        {
            if ( circle.overlaps( new_circle ) )
            {
                auto center_distance = distance( circle.center, new_circle.center );
                auto new_circle_radius = center_distance - circle.radius;
                if ( new_circle_radius < m_min_radius )
                {
                    bad_circle = true;
                    break;
                }
                else
                {
                    new_circle.radius = new_circle_radius;
                }
            }
        }

        if ( !bad_circle )
        {
            i++;
            circles.push_back( new_circle );
        }
    }

    return circles;
}

std::vector< std::vector< sf::Vector2f > >
PolygonsGenerator::generate_polygons_from_circles( std::vector< Circle > circles )
{
    std::vector< std::vector< sf::Vector2f > > polygons;

    for ( int i = 0; i < m_number_of_polygons; i++ )
    {
        auto circle = circles[ i ];
        std::vector< float > angles;

        for ( int j = 0, num_tries = 0; j < m_number_of_edges; )
        {
            auto angle = m_random_angle.get_number( );
            auto point = circle.point_on_circle( angle );

            auto it = std::find_if( angles.begin( ),
                                    angles.end( ),
                                    [ &point, &circle, this ]( const float& angle ) {
                                        return distance( circle.point_on_circle( angle ), point )
                                               < m_min_point_distance;
                                    } );

            if ( it == angles.end( ) || num_tries >= 5 )
            {
                j++;
                num_tries = 0;
                angles.push_back( angle );
            }
            else
            {
                num_tries++;
            }
        }

        std::sort( angles.begin( ), angles.end( ) );
        std::vector< sf::Vector2f > polygon;
        std::for_each( angles.begin( ),
                       angles.end( ),
                       [ &polygon, &circle ]( const float& angle )
                       { polygon.push_back( circle.point_on_circle( angle ) ); } );

        polygons.push_back( polygon );
    }


    return polygons;
}

void
PolygonsGenerator::init_random_generators( sf::Rect< float > area )
{
    m_random_x.set_range( area.left, area.left + area.width );
    m_random_y.set_range( area.top, area.top + area.height );
    m_random_radius.set_range( m_min_radius, m_min_radius * 2 );
    m_random_angle.set_range( 0, 2 * M_PI );
}

sf::Vector2f
PolygonsGenerator::random_point( )
{
    return sf::Vector2f{ m_random_x.get_number( ), m_random_y.get_number( ) };
}
