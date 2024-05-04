#include "RectButton.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
RectButton::RectButton(std::string text, sf::Vector2f position, sf::Vector2f size, callback_t callback)
    :  m_callback{callback}
{
    m_rectangle.setPosition(position);
    m_rectangle.setSize(size);
    m_rectangle.setFillColor(sf::Color{149, 154, 161});
    m_rectangle.setOutlineColor(sf::Color{95, 101, 110});
    m_rectangle.setOutlineThickness(2);

    m_font.loadFromFile("../../FreeSans.ttf");
    m_text.setFont(m_font); // font is a sf::Font

    m_text.setString(text);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position + sf::Vector2f{5, 5});
}

void RectButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rectangle);
    target.draw(m_text);
}

bool RectButton::consume_event(sf::Event event, sf::Window &window)
{
    if(event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f pixelPos{static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)};
            if(m_rectangle.getLocalBounds().contains(pixelPos)) {
                m_callback();
                return true;
            }
        }
    }
    return false;
}
