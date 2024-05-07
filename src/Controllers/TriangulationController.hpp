#ifndef TRIANGULATIONCONTROLLER_HPP
#define TRIANGULATIONCONTROLLER_HPP

#include <Algorithms/HalfEdgeList.hpp>
#include <Layers/PolygonsLayer.hpp>
#include <memory>
#include <vector>

class TriangulationController
{
    std::shared_ptr< PolygonsLayer > m_polygons_layer;

    std::vector< HalfEdgeList > m_whole_polygons;
    std::vector< HalfEdgeList > m_monotone_polygons;
    std::vector< HalfEdgeList > m_monotone_trinagulated_polygons;
    std::vector< HalfEdgeList > m_triangulated_polygon;

    int m_index = 0;

    enum ActiveMode
    {
        Whole,
        Monotone,
        MonotoneTriangulated,
        Trinagulated
    };

    ActiveMode active_mode = Whole;
    std::vector< HalfEdgeList >& active_polygons( );

public:
    void set_polygons_layer( std::shared_ptr< PolygonsLayer > polygons_layer );
    void triangulate( std::vector< std::vector< sf::Vector2f > > polygons );
    void show_next( );
    void show_prev( );
    void switch_mode( );

    void show_polygons( );
    void clear( );
};

#endif  // TRIANGULATIONCONTROLLER_HPP
