#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <Layers/ControllLayer.hpp>
#include <Layers/ShapeAdditionLayer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "PolygonsGenerator.hpp"
#include "PolygonBuilderController.hpp"
#include "TriangulationController.hpp"
#include "ZoomController.hpp"

class Controller
{
    static constexpr int window_x = 1000;
    static constexpr int window_y = 600;
    ShapeAdditionLayerPtr m_polygon_addition_l;
    PolygonsLayerPtr m_user_polygons_l;
    PolygonsLayerPtr m_triangulated_polygons;
    ControllLayerPtr m_control_layer;

    PolygonBuilderController m_polygon_builder;
    TriangulationController m_triangulation_controller;
    PolygonsGenerator m_polygons_generator;

    sf::RenderWindow& m_window;
    int m_number_of_edges;
    int m_number_of_polygons;

    bool m_moving_map = false;
    sf::Vector2i m_previous_mouse_position;

public:
    Controller( sf::RenderWindow& window );

    void process_event( sf::Event event );
    void on_triangulazi_pressed( );
    void on_clear_pressed( );
    void on_generate_pressed( );
    void on_number_of_edges_changed( int n );
    void on_number_of_polygons_changed( int n );

    RenderLayerPtr shape_addition_layer( );
    RenderLayerPtr user_polygons_layer( );
    RenderLayerPtr triangulated_polygons_layer( );
    RenderLayerPtr control_layer( );
};

#endif  // CONTROLLER_HPP
