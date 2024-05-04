#include "ShapeAdditionLayer.hpp"
static constexpr float POINT_RAIDUS = 3.f;

void
ShapeAdditionLayer::draw( sf::RenderTarget& render_target )
{
    lock_guard guard{ m_mutex };

    for ( auto& point : m_points )
    {
        render_target.draw( point );
    }
}

void
ShapeAdditionLayer::clear( )
{
    lock_guard guard{ m_mutex };
    m_points.clear( );
}

void
ShapeAdditionLayer::add_point( sf::Vector2f p )
{
    sf::CircleShape point( POINT_RAIDUS );
    point.setFillColor( sf::Color::Black );
    point.setPosition( p );

    {
        lock_guard guard{ m_mutex };
        m_points.push_back( point );
    }
}
