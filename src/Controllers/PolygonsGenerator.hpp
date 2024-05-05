#ifndef POLYGONSGENERATOR_HPP
#define POLYGONSGENERATOR_HPP

#include <Layers/PolygonsLayer.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

class PolygonsGenerator
{
    int m_number_of_polygons = 0;

public:
    void set_number_of_polygons( int n );

    std::vector< std::vector< sf::Vector2f > > generate( );
};

#endif  // POLYGONSGENERATOR_HPP
