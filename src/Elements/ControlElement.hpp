#ifndef CONTROLELEMENT_HPP
#define CONTROLELEMENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class ControlElement : public sf::Drawable
{
public:
    virtual bool consume_event( sf::Event event, sf::Window& window ) = 0;
};

using ControlElementPtr = std::shared_ptr< ControlElement >;

#endif  // CONTROLELEMENT_HPP
