#include "Renderer.hpp"

void
Renderer::render( sf::RenderWindow& window )
{
    window.clear( sf::Color{ 110, 108, 105 } );

    for ( auto& layer : m_layers )
    {
        layer->draw( window );
    }

    // end the current frame
    window.display( );
}

void
Renderer::add_layer( RenderLayerPtr layer )
{
    m_layers.push_back( layer );
}
