#ifndef CONVEXPOLYGONSLAYER_HPP
#define CONVEXPOLYGONSLAYER_HPP

#include "PolygonsLayer.hpp"
#include "Line.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class ConvexPolygonsLayer : public PolygonsLayer
{
    std::vector<std::vector<sfLine>> m_polygons;
    std::mutex m_mutex;
public:
    void draw_polygons(sf::RenderTarget& render_targer) override;
    void clear() override;
    void add_polygon(std::vector<sf::Vector2f> points) override;
};

using ConvexPolygonsLayerPtr = std::shared_ptr<ConvexPolygonsLayer>;


#endif // CONVEXPOLYGONSLAYER_HPP
