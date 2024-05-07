#include "OutlinePolygonsLayer.hpp"

OutlinePolygonsLayer::OutlinePolygonsLayer( std::vector< sf::Color > colors )
    : m_colors( colors )
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
    auto color = current_color++ % m_colors.size( );
    for ( int i = 0; i < points.size( ); i++ )
    {
        auto a = points[ i ];
        auto b = points[ ( i + 1 ) % points.size( ) ];
        polygon.push_back( { a, b, m_colors[ color ], 2 } );
    }

    lock_guard lock( m_mutex );
    m_polygons.push_back( polygon );
}
