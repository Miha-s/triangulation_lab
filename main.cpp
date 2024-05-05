#include <Controllers/Controller.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>

#include "Renderer.hpp"

int
main( )
{
    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "My window", sf::Style::Default, settings );

    Controller controller( window );

    Renderer renderer;
    renderer.add_layer( controller.shape_addition_layer( ) );
    renderer.add_layer( controller.user_polygons_layer( ) );
    renderer.add_layer( controller.triangulated_polygons_layer( ) );
    renderer.add_layer( controller.control_layer( ) );

    // run the program as long as the window is open
    while ( window.isOpen( ) )
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            controller.process_event( event );
        }

        renderer.render( window );
    }

    return 0;
}
