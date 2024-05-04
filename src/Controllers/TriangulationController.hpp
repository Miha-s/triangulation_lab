#ifndef TRIANGULATIONCONTROLLER_HPP
#define TRIANGULATIONCONTROLLER_HPP

#include <Layers/PolygonsLayer.hpp>
#include <vector>
#include <memory>


class TriangulationController
{
    std::shared_ptr<PolygonsLayer> m_polygons_layer;
public:
    void set_polygons_layer(std::shared_ptr<PolygonsLayer> polygons_layer);
    void triangulate(std::vector<std::vector<sf::Vector2f>> polygons);
};

#endif // TRIANGULATIONCONTROLLER_HPP