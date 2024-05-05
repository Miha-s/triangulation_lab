#include "TriangulationController.hpp"

void
TriangulationController::set_polygons_layer( std::shared_ptr< PolygonsLayer > polygons_layer )
{
    m_polygons_layer = polygons_layer;
}

void
TriangulationController::triangulate( std::vector< std::vector< sf::Vector2f > > polygons )
{
    // do stuff
    for ( auto& polygon : polygons )
    {
        m_polygons_layer->add_polygon( polygon );
    }
}

void
TriangulationController::clear( )
{
    m_polygons_layer->clear( );
}
