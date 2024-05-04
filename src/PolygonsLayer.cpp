#include "PolygonsLayer.hpp"

void PolygonsLayer::draw(sf::RenderTarget &render_target)
{
    draw_polygons(render_target);

    if(m_next_polygon_layer)
        m_next_polygon_layer->draw(render_target);
}

void PolygonsLayer::set_next(PolygonsLayerPtr layer)
{
    m_next_polygon_layer = layer;
}
