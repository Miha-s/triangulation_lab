#ifndef USERPOLYGONSLAYER_HPP
#define USERPOLYGONSLAYER_HPP

#include "RenderLayer.hpp"
#include "Line.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class UserPolygonsLayer : public RenderLayer
{
    std::vector<std::vector<sfLine>> m_polygons;
    std::mutex m_mutex;
public:
    void draw(sf::RenderTarget& render_targer) override;
    void clear();
    void add_polygon(std::vector<sf::Vector2f> points);
};

using UserPolygonsLayerPtr = std::shared_ptr<UserPolygonsLayer>;

#endif // USERPOLYGONSLAYER_HPP
