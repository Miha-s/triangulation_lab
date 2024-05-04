#include "Renderer.hpp"

void
Renderer::render( sf::RenderWindow& window )
{
    window.setActive( true );

    while ( window.isOpen( ) )
    {
        window.clear( sf::Color::White );

        for ( auto& layer : m_layers )
        {
            layer->draw( window );
        }

        // end the current frame
        window.display( );
    }

    window.setActive( false );
}

void
Renderer::add_layer( RenderLayerPtr layer )
{
    m_layers.push_back( layer );
}
