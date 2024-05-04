#include <Controllers/Controller.hpp>
#include "Renderer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    Controller controller(window);

    window.setActive(false);

    Renderer renderer;
    renderer.add_layer(controller.shape_addition_layer());
    renderer.add_layer(controller.user_polygons_layer());
    renderer.add_layer(controller.triangulated_polygons_layer());
    renderer.add_layer(controller.control_layer());

    std::thread render_thread{[&window, &renderer](){
            renderer.render(window);
    }};

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            controller.process_event(event);
        }
    }

    render_thread.join();
    return 0;
}
