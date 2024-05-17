#include "Controller.hpp"

#include <Elements/RectButton.hpp>
#include <Elements/SpinnerControl.hpp>
#include <Layers/ConvexPolygonsLayer.hpp>
#include <iostream>

static constexpr float ZOOM_STEP = 0.05;
static constexpr int INITIAL_EDGES = 3;
static constexpr int INITIAL_POLYGONS = 3;

sf::FloatRect
getViewBounds( const sf::View& view )
{
    sf::FloatRect rt;
    rt.left = view.getCenter( ).x - view.getSize( ).x / 2.f;
    rt.top = view.getCenter( ).y - view.getSize( ).y / 2.f;
    rt.width = view.getSize( ).x;
    rt.height = view.getSize( ).y;
    return rt;
}

Controller::Controller( sf::RenderWindow& window )
    : m_window{ window }
{
    m_polygon_addition_l = std::make_shared< ShapeAdditionLayer >( );
    m_user_polygons_l = std::make_shared< OutlinePolygonsLayer >(
            std::vector< sf::Color >{ sf::Color{ 74, 222, 33 } } );

    m_polygon_builder.set_polygon_addition_layer( m_polygon_addition_l );
    m_polygon_builder.set_polygon_layer( m_user_polygons_l );
    m_polygon_builder.set_number_of_edges( INITIAL_EDGES );

    m_number_of_edges = INITIAL_EDGES;
    m_number_of_polygons = INITIAL_POLYGONS;

    m_triangulated_whole_polygons = std::make_shared< ConvexPolygonsLayer >( sf::Color::Red );
    m_triangulated_outline_polygons = ( std::make_shared< OutlinePolygonsLayer >(
            std::vector< sf::Color >{ sf::Color::Yellow } ) );

    m_triangulation_controller.set_outline_polygons_layer( m_triangulated_outline_polygons );
    m_triangulation_controller.set_whole_polygons_layer( m_triangulated_whole_polygons );

    m_control_layer = std::make_shared< ControllLayer >( );
    auto triangulize_button =
            std::make_shared< RectButton >( "Triangulate",
                                            sf::Vector2f{ 5, 5 },
                                            sf::Vector2f{ 110, 30 },
                                            [ this ]( ) { on_triangulazi_pressed( ); } );
    auto clear_button = std::make_shared< RectButton >( "Clear",
                                                        sf::Vector2f{ 120, 5 },
                                                        sf::Vector2f{ 60, 30 },
                                                        [ this ]( ) { on_clear_pressed( ); } );
    auto generate_button =
            std::make_shared< RectButton >( "Generate",
                                            sf::Vector2f{ 185, 5 },
                                            sf::Vector2f{ 100, 30 },
                                            [ this ]( ) { on_generate_pressed( ); } );
    auto number_of_edges_spinner = std::make_shared< SpinnerControl >(
            "Edges",
            sf::Vector2f{ 290, 5 },
            INITIAL_EDGES,
            [ this ]( int n ) { on_number_of_edges_changed( n ); } );
    auto number_of_polygons_spinner = std::make_shared< SpinnerControl >(
            "Polygons",
            sf::Vector2f{ 295.f + number_of_edges_spinner->width( ), 5 },
            INITIAL_POLYGONS,
            [ this ]( int n ) { on_number_of_polygons_changed( n ); } );

    m_control_layer->add_element( triangulize_button );
    m_control_layer->add_element( clear_button );
    m_control_layer->add_element( generate_button );
    m_control_layer->add_element( number_of_edges_spinner );
    m_control_layer->add_element( number_of_polygons_spinner );

    m_window.create( sf::VideoMode( window_x, window_y ), "My window" );
    sf::View main_view( sf::FloatRect( 0.f, 0.f, window_x, window_y ) );
    m_window.setView( main_view );
}

void
Controller::process_event( sf::Event event )
{
    if ( m_control_layer->consume_event( event, m_window ) )
    {
        return;
    }
    if ( event.type == sf::Event::Closed )
    {
        m_window.close( );
        return;
    }
    if ( event.type == sf::Event::MouseButtonPressed )
    {
        if ( event.mouseButton.button == sf::Mouse::Right )
        {
            m_moving_map = true;
            m_previous_mouse_position = sf::Mouse::getPosition( m_window );
        }
        if ( event.mouseButton.button == sf::Mouse::Left )
        {
            sf::Vector2i pixelPos{ event.mouseButton.x, event.mouseButton.y };
            sf::Vector2f worldPos = m_window.mapPixelToCoords( pixelPos );
            std::cout << pixelPos.x << " " << pixelPos.y << std::endl;
            std::cout << worldPos.x << " " << worldPos.y << std::endl;
            m_polygon_builder.add_point( worldPos );
        }
        return;
    }
    if ( event.type == sf::Event::MouseButtonReleased )
    {
        if ( event.mouseButton.button == sf::Mouse::Right )
        {
            m_moving_map = false;
        }
        return;
    }
    if ( event.type == sf::Event::MouseMoved )
    {
        if ( !m_moving_map )
        {
            return;
        }
        sf::View view = m_window.getView( );
        auto mouse_position = sf::Mouse::getPosition( m_window );
        sf::Vector2f worldPos = m_window.mapPixelToCoords( mouse_position );
        auto delta = worldPos - m_window.mapPixelToCoords( m_previous_mouse_position );
        m_previous_mouse_position = mouse_position;
        view.move( -delta );
        m_window.setView( view );

        return;
    }
    if ( event.type == sf::Event::Resized )
    {
        // update the view to the new size of the window
        sf::View view = m_window.getView( );
        sf::FloatRect visibleArea( 0.f, 0.f, event.size.width, event.size.height );
        view.reset( visibleArea );
        m_window.setView( view );
        return;
    }
    if ( event.type == sf::Event::MouseWheelScrolled )
    {
        sf::View view = m_window.getView( );
        view.zoom( 1 - ZOOM_STEP * event.mouseWheelScroll.delta );
        m_window.setView( view );
    }
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Enter )
        {
            m_triangulation_controller.switch_mode( );
            std::cout << "Enter pressed" << std::endl;
        }
        if ( event.key.code == sf::Keyboard::Right )
        {
            m_triangulation_controller.show_next( );
            std::cout << "Right pressed" << std::endl;
        }
        if ( event.key.code == sf::Keyboard::Left )
        {
            m_triangulation_controller.show_prev( );
            std::cout << "Left pressed" << std::endl;
        }
    }
}

void
Controller::on_triangulazi_pressed( )
{
    m_triangulation_controller.triangulate( m_polygon_builder.get_result( ) );
}

void
Controller::on_clear_pressed( )
{
    m_triangulation_controller.clear( );
    m_polygon_builder.clear( );
}

void
Controller::on_generate_pressed( )
{
    on_clear_pressed( );
    auto rect = getViewBounds( m_window.getView( ) );

    auto polygons = m_polygons_generator.generate( rect, m_number_of_polygons, m_number_of_edges );

    for ( auto& polygon : polygons )
    {
        m_polygon_builder.add_polygon( polygon );
    }
}

void
Controller::on_number_of_edges_changed( int n )
{
    m_number_of_edges = n;
    m_polygon_builder.set_number_of_edges( n );
}

void
Controller::on_number_of_polygons_changed( int n )
{
    on_clear_pressed( );
    m_number_of_polygons = n;
}

std::shared_ptr< RenderLayer >
Controller::shape_addition_layer( )
{
    return m_polygon_addition_l;
}

std::shared_ptr< RenderLayer >
Controller::user_polygons_layer( )
{
    return m_user_polygons_l;
}

RenderLayerPtr
Controller::triangulated_whole_polygons_layer( )
{
    return m_triangulated_whole_polygons;
}

RenderLayerPtr
Controller::triangulated_outline_polygons_layer( )
{
    return m_triangulated_outline_polygons;
}

RenderLayerPtr
Controller::control_layer( )
{
    return m_control_layer;
}
