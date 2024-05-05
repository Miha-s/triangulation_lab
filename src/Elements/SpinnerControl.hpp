#ifndef SPINNERCONTROL_HPP
#define SPINNERCONTROL_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include "RectButton.hpp"
#include "ControlElement.hpp"

class SpinnerControl : public ControlElement
{
    using callback_t = std::function< void( int ) >;

    sf::Font m_font;
    sf::Text m_counter_text;
    sf::Text m_name;
    std::shared_ptr< RectButton > m_decrease_button;
    std::shared_ptr< RectButton > m_increase_button;
    int m_counter = 0;

    callback_t m_callback;

public:
    SpinnerControl( std::string text, sf::Vector2f position, int counter, callback_t callback );

    void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    bool consume_event( sf::Event event, sf::Window& window );
    int width( );

private:
    void on_decrease_pressed( );
    void on_increase_pressed( );
};

#endif  // SPINNERCONTROL_HPP
