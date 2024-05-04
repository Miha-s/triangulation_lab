#include "ControllLayer.hpp"

void
ControllLayer::clear( )
{
    lock_guard guard( m_mutex );
    m_control_elements.clear( );
}

void
ControllLayer::draw( sf::RenderTarget& render_target )
{
    auto view = render_target.getView( );
    auto size = render_target.getSize( );

    sf::View view1( sf::FloatRect( 0.f, 0.f, size.x, size.y ) );
    render_target.setView( view1 );

    lock_guard guard( m_mutex );
    for ( auto& element : m_control_elements )
    {
        render_target.draw( *element );
    }

    render_target.setView( view );
}

void
ControllLayer::add_element( ControlElementPtr element )
{
    lock_guard guard( m_mutex );
    m_control_elements.push_back( element );
}

bool
ControllLayer::consume_event( sf::Event event, sf::Window& window )
{
    for ( auto& element : m_control_elements )
    {
        if ( element->consume_event( event, window ) )
        {
            return true;
        }
    }

    return false;
}
