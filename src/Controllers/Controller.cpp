#include "Controller.hpp"
#include <Layers/ConvexPolygonsLayer.hpp>
#include <Elements/RectButton.hpp>
#include <iostream>

static constexpr float ZOOM_STEP = 0.05;

Controller::Controller(sf::RenderWindow &window) : m_window{window}
{
    m_polygon_addition = std::make_shared<ShapeAdditionLayer>();
    m_user_polygons = std::make_shared<OutlinePolygonsLayer>();

    m_polygon_builder.set_polygon_addition_layer(m_polygon_addition);
    m_polygon_builder.set_polygon_layer(m_user_polygons);

    m_triangulated_polygons = std::make_shared<ConvexPolygonsLayer>();
    m_triangulated_polygons->set_next(std::make_shared<OutlinePolygonsLayer>());
    m_triangulation_controller.set_polygons_layer(m_triangulated_polygons);

    m_control_layer = std::make_shared<ControllLayer>();
    m_control_layer->add_element(std::make_shared<RectButton>("Triangulize", sf::Vector2f{5, 5}, sf::Vector2f{110, 30}, [this](){on_triangulazi_pressed();}));

    m_window.create(sf::VideoMode(window_x, window_y), "My window");
    sf::View main_view(sf::FloatRect(0.f, 0.f, window_x, window_y));
    m_window.setView(main_view);
}

void Controller::process_event(sf::Event event)
{
    if(m_control_layer->consume_event(event, m_window)) {
        return;
    }
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
        sf::View view = m_window.getView();
        sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
        view.reset(visibleArea);
        m_window.setView(view);
        return;
    }
    if(event.type == sf::Event::MouseWheelScrolled) {
        sf::View view = m_window.getView();
        view.zoom(1 - ZOOM_STEP*event.mouseWheelScroll.delta);
        m_window.setView(view);
    }
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Enter) {
            std::cout << "Enter pressed" << std::endl;
        }
    }

}

void Controller::on_triangulazi_pressed()
{
    m_triangulation_controller.triangulate(m_polygon_builder.get_result());
}

std::shared_ptr<RenderLayer> Controller::shape_addition_layer()
{
    return m_polygon_addition;
}

std::shared_ptr<RenderLayer> Controller::user_polygons_layer()
{
    return m_user_polygons;
}

RenderLayerPtr Controller::triangulated_polygons_layer()
{
    return m_triangulated_polygons;
}

RenderLayerPtr Controller::control_layer()
{
    return m_control_layer;
}
