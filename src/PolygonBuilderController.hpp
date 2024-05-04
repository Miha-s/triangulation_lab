#ifndef POLYGONBUILDERCONTROLLER_HPP
#define POLYGONBUILDERCONTROLLER_HPP

#include "ShapeAdditionLayer.hpp"
#include "UserPolygonsLayer.hpp"

struct Result
{

};

class PolygonBuilderController
{
    ShapeAdditionLayerPtr m_polygon_addition_l;
    UserPolygonsLayerPtr m_user_polygons_l;

    std::vector<std::vector<sf::Vector2f>> m_user_polygons;
    std::vector<sf::Vector2f> m_current_points;
public:
    void set_polygon_layer(UserPolygonsLayerPtr user_polygons_l);
    void set_polygon_addition_layer(ShapeAdditionLayerPtr polygon_addition_l);

    void add_point(sf::Vector2f point);
    Result get_result();
};

#endif // POLYGONBUILDERCONTROLLER_HPP
