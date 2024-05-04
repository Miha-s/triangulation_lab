#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "ShapeAdditionLayer.hpp"
#include "ZoomController.hpp"
#include "UserPolygonsLayer.hpp"
#include "PolygonBuilderController.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


class Controller
{
    static constexpr int window_x = 1000;
    static constexpr int window_y = 600;
    std::shared_ptr<ShapeAdditionLayer> m_polygon_addition;
    std::shared_ptr<UserPolygonsLayer> m_user_polygons;
    PolygonBuilderController m_polygon_builder;

    sf::RenderWindow& m_window;
    ZoomController m_zoom;
public:
    Controller(sf::RenderWindow& window);

    void process_event(sf::Event event);

    std::shared_ptr<RenderLayer> shape_addition_layer();
    std::shared_ptr<RenderLayer> user_polygons_layer();

};


#endif // CONTROLLER_HPP
