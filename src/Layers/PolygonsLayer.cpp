#include "PolygonsLayer.hpp"

void
PolygonsLayer::add( std::vector< sf::Vector2f > points )
{
    add_polygon( points );
    if ( m_next_polygon_layer )
    {
        m_next_polygon_layer->add( points );
    }
}

void
PolygonsLayer::draw( sf::RenderTarget& render_target )
{
    draw_polygons( render_target );

    if ( m_next_polygon_layer )
        m_next_polygon_layer->draw( render_target );
}

void
PolygonsLayer::clear( )
{
    clear_polygons( );
    if ( m_next_polygon_layer )
        m_next_polygon_layer->clear( );
}

void
PolygonsLayer::set_next( PolygonsLayerPtr layer )
{
    m_next_polygon_layer = layer;
}
