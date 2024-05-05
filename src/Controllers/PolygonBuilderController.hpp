#ifndef POLYGONBUILDERCONTROLLER_HPP
#define POLYGONBUILDERCONTROLLER_HPP

#include <Layers/OutlinePolygonsLayer.hpp>
#include <Layers/ShapeAdditionLayer.hpp>

class PolygonBuilderController
{
public:
    using Result = std::vector< std::vector< sf::Vector2f > >;

private:
    ShapeAdditionLayerPtr m_polygon_addition_l;
    PolygonsLayerPtr m_user_polygons_l;
    int m_number_of_edges;

    Result m_user_polygons;
    std::vector< sf::Vector2f > m_current_points;

public:
    void set_polygon_layer( PolygonsLayerPtr user_polygons_l );
    void set_polygon_addition_layer( ShapeAdditionLayerPtr polygon_addition_l );
    void set_number_of_edges( int n );

    void clear( );
    void add_point( sf::Vector2f point );
    void add_polygon( std::vector< sf::Vector2f > polygon );
    Result get_result( );
};

#endif  // POLYGONBUILDERCONTROLLER_HPP
