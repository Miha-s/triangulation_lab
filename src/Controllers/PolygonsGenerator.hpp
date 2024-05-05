#ifndef POLYGONSGENERATOR_HPP
#define POLYGONSGENERATOR_HPP

#include <Layers/PolygonsLayer.hpp>
#include <SFML/System/Vector2.hpp>
#include <Utils/Circle.hpp>
#include <Utils/RandomNumberGenerator.hpp>
#include <memory>
#include <vector>

class PolygonsGenerator
{
    int m_number_of_polygons = 0;
    int m_number_of_edges = 0;
    RandomNumberGenerator m_random_x;
    RandomNumberGenerator m_random_y;
    RandomNumberGenerator m_random_radius;
    RandomNumberGenerator m_random_angle;
    float m_min_radius = 30;
    float m_min_point_distance = 20;

public:
    std::vector< std::vector< sf::Vector2f > > generate( sf::Rect< float > area,
                                                         int number_of_polygons,
                                                         int number_of_edges );

private:
    std::vector< Circle > generate_polygons_circles( );
    std::vector< std::vector< sf::Vector2f > > generate_polygons_from_circles(
            std::vector< Circle > circles );
    void init_random_generators( sf::Rect< float > area );
    sf::Vector2f random_point( );

};

#endif  // POLYGONSGENERATOR_HPP
