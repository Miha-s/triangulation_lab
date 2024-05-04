#ifndef CONTROLLLAYER_HPP
#define CONTROLLLAYER_HPP

#include <Elements/ControlElement.hpp>
#include <vector>

#include "RenderLayer.hpp"

class ControllLayer : public RenderLayer
{
    std::vector< ControlElementPtr > m_control_elements;
    std::mutex m_mutex;

public:
    void clear( );
    void draw( sf::RenderTarget& render_target );
    void add_element( ControlElementPtr element );

    bool consume_event( sf::Event event, sf::Window& window );
};

using ControllLayerPtr = std::shared_ptr< ControllLayer >;
#endif  // CONTROLLLAYER_HPP
