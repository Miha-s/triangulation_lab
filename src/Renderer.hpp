#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "RenderLayer.hpp"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

class Renderer
{
    std::vector<RenderLayerPtr> m_layers;
public:

    void render(sf::RenderWindow& window);

    void add_layer(RenderLayerPtr layer);

};

#endif // RENDERER_HPP
