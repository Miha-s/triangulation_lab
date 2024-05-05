#include "PolygonsGenerator.hpp"

void
PolygonsGenerator::set_number_of_polygons( int n )
{
    m_number_of_polygons = n;
}

std::vector< std::vector< sf::Vector2f > >
PolygonsGenerator::generate( )
{
    std::vector< std::vector< sf::Vector2f > > polygons;
    polygons.push_back( { sf::Vector2f{ 5, 5 }, sf::Vector2f{ 30, 70 }, sf::Vector2f{ 10, 40 } } );

    return polygons;
}
