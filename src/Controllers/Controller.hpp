#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <Layers/ControllLayer.hpp>
#include <Layers/ShapeAdditionLayer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "PolygonBuilderController.hpp"
#include "TriangulationController.hpp"
#include "ZoomController.hpp"

class Controller
{
    static constexpr int window_x = 1000;
    static constexpr int window_y = 600;
    ShapeAdditionLayerPtr m_polygon_addition;
    PolygonsLayerPtr m_user_polygons;
    PolygonsLayerPtr m_triangulated_polygons;
    ControllLayerPtr m_control_layer;

    PolygonBuilderController m_polygon_builder;
    TriangulationController m_triangulation_controller;

    sf::RenderWindow& m_window;
    ZoomController m_zoom;

public:
    Controller( sf::RenderWindow& window );

    void process_event( sf::Event event );
    void on_triangulazi_pressed( );

    RenderLayerPtr shape_addition_layer( );
    RenderLayerPtr user_polygons_layer( );
    RenderLayerPtr triangulated_polygons_layer( );
    RenderLayerPtr control_layer( );
};

#endif  // CONTROLLER_HPP
