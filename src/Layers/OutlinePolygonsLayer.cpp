#include "OutlinePolygonsLayer.hpp"

OutlinePolygonsLayer::OutlinePolygonsLayer(sf::Color color) : m_color(color)
{

}

void
OutlinePolygonsLayer::draw_polygons( sf::RenderTarget& render_targer )
{
    lock_guard lock( m_mutex );
    for ( auto& polygon : m_polygons )
    {
        for ( auto& line : polygon )
        {
            render_targer.draw( line );
        }
    }
}

void
OutlinePolygonsLayer::clear_polygons( )
{
    lock_guard lock( m_mutex );
    m_polygons.clear( );
}

void
OutlinePolygonsLayer::add_polygon( const std::vector< sf::Vector2f >& points )
{
    std::vector< sfLine > polygon;

    for ( int i = 0; i < points.size( ); i++ )
    {
        auto a = points[ i ];
        auto b = points[ ( i + 1 ) % points.size( ) ];
        polygon.push_back( { a, b, m_color, 2 } );
    }

    lock_guard lock( m_mutex );
    m_polygons.push_back( polygon );
}
