#include "Controller.hpp"
#include <iostream>

Controller::Controller(sf::RenderWindow &window) : m_window{window}
{
    m_polygon_addition = std::make_shared<ShapeAdditionLayer>();
    m_user_polygons = std::make_shared<OutlinePolygonsLayer>();

    m_polygon_builder.set_polygon_addition_layer(m_polygon_addition);
    m_polygon_builder.set_polygon_layer(m_user_polygons);

    m_window.create(sf::VideoMode(window_x, window_y), "My window");
    sf::View main_view(sf::FloatRect(0.f, 0.f, window_x, window_y));
    m_window.setView(main_view);
}

void Controller::process_event(sf::Event event)
{
    if (event.type == sf::Event::Closed) {
        m_window.close();
        return;
    }
    if(event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos{event.mouseButton.x, event.mouseButton.y};
            sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
            m_polygon_builder.add_point(worldPos);
        }
        return;
    }
    if (event.type == sf::Event::Resized)
    {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
        m_window.setView(sf::View(visibleArea));
        return;
    }
    if(event.type == sf::Event::MouseWheelScrolled) {
        event.mouseWheelScroll.delta > 0 ? m_zoom.increaseZoom() : m_zoom.decreaseZoom();

        sf::View view = m_window.getDefaultView();
        view.zoom(m_zoom.zoom());
        m_window.setView(view);
    }

}

std::shared_ptr<RenderLayer> Controller::shape_addition_layer()
{
    return m_polygon_addition;
}

std::shared_ptr<RenderLayer> Controller::user_polygons_layer()
{
    return m_user_polygons;
}
