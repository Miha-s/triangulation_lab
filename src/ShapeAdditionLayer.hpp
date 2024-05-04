#ifndef SHAPEADDITIONLAYER_HPP
#define SHAPEADDITIONLAYER_HPP

#include "RenderLayer.hpp"
#include "OutlinePolygonsLayer.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <vector>
#include <mutex>

class ShapeAdditionLayer : public RenderLayer
{
    std::vector<sf::CircleShape> m_points;
    std::mutex m_mutex;
public:
    void draw(sf::RenderTarget& render_target) override;
    void clear() override;
    void add_point(sf::Vector2f point);

    ~ShapeAdditionLayer(){}
};

using ShapeAdditionLayerPtr = std::shared_ptr<ShapeAdditionLayer>;

#endif // SHAPEADDITIONLAYER_HPP
