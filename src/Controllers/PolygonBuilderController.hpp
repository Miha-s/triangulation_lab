#ifndef POLYGONBUILDERCONTROLLER_HPP
#define POLYGONBUILDERCONTROLLER_HPP

#include <Layers/ShapeAdditionLayer.hpp>
#include <Layers/OutlinePolygonsLayer.hpp>

class PolygonBuilderController
{
public:
    using Result = std::vector<std::vector<sf::Vector2f>>;
private:
    ShapeAdditionLayerPtr m_polygon_addition_l;
    PolygonsLayerPtr m_user_polygons_l;

    Result m_user_polygons;
    std::vector<sf::Vector2f> m_current_points;
public:
    void set_polygon_layer(PolygonsLayerPtr user_polygons_l);
    void set_polygon_addition_layer(ShapeAdditionLayerPtr polygon_addition_l);

    void add_point(sf::Vector2f point);
    Result get_result();
};

#endif // POLYGONBUILDERCONTROLLER_HPP
