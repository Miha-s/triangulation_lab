#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Layers/RenderLayer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Renderer
{
    std::vector< RenderLayerPtr > m_layers;

public:
    void render( sf::RenderWindow& window );

    void add_layer( RenderLayerPtr layer );
};

#endif  // RENDERER_HPP
