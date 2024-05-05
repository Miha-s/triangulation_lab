#include "ConvexPolygonsLayer.hpp"

void
ConvexPolygonsLayer::draw_polygons( sf::RenderTarget& render_targer )
{
    lock_guard lock( m_mutex );
    for ( auto& polygon : m_polygons )
    {
        render_targer.draw( polygon );
    }
}

void
ConvexPolygonsLayer::clear_polygons( )
{
    lock_guard lock( m_mutex );
    m_polygons.clear( );
}

void
ConvexPolygonsLayer::add_polygon( std::vector< sf::Vector2f > points )
{
    sf::ConvexShape convex;
    convex.setPointCount( points.size( ) );
    convex.setFillColor( sf::Color::Black );

    for ( int i = 0; i < points.size( ); i++ )
    {
        convex.setPoint( i, points[ i ] );
    }

    lock_guard lock( m_mutex );
    m_polygons.push_back( convex );
}
