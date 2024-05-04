#ifndef RECTBUTTON_HPP
#define RECTBUTTON_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>

#include "ControlElement.hpp"

class RectButton : public ControlElement
{
    using callback_t = std::function< void( ) >;

    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rectangle;
    callback_t m_callback;

public:
    RectButton( std::string text, sf::Vector2f position, sf::Vector2f size, callback_t callback );
    void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    bool consume_event( sf::Event event, sf::Window& window );
};

#endif  // RECTBUTTON_HPP
