#ifndef POLYGONSLAYER_HPP
#define POLYGONSLAYER_HPP

#include "RenderLayer.hpp"
#include <vector>

class PolygonsLayer;
using PolygonsLayerPtr = std::shared_ptr<PolygonsLayer>;

class PolygonsLayer : public RenderLayer
{
    PolygonsLayerPtr m_next_polygon_layer;
public:
    virtual void draw_polygons(sf::RenderTarget& render_targer) = 0;
    virtual void add_polygon(std::vector<sf::Vector2f> points) = 0;

    void draw(sf::RenderTarget& render_target) override final
    {
        draw_polygons(render_target);

        if(m_next_polygon_layer)
            m_next_polygon_layer->draw(render_target);
    }

    void set_next(PolygonsLayerPtr layer) {
        m_next_polygon_layer = layer;
    }
};

#endif // POLYGONSLAYER_HPP
