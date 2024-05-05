#include "SpinnerControl.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

static constexpr int SIZE_X = 30;
static constexpr int SIZE_Y = 30;
static constexpr int PADDING = 5;

SpinnerControl::SpinnerControl( std::string text,
                                sf::Vector2f position,
                                int counter,
                                callback_t callback )
    : m_counter{ counter }
    , m_callback{ callback }
{
    m_decrease_button = std::make_shared< RectButton >( "-",
                                                        position,
                                                        sf::Vector2f{ SIZE_X, SIZE_Y },
                                                        [ this ]( ) { on_decrease_pressed( ); } );

    m_font.loadFromFile( "../../FreeSans.ttf" );
    m_counter_text.setFont( m_font );
    m_name.setFont( m_font );

    m_name.setString( text );
    m_name.setCharacterSize( 20 );
    m_name.setFillColor( sf::Color::Black );
    auto text_width = m_name.getLocalBounds( ).width;
    m_name.setPosition( position + sf::Vector2f{ SIZE_X + PADDING, 0.f } );

    m_counter_text.setString( std::to_string( m_counter ) );
    m_counter_text.setCharacterSize( 20 );
    m_counter_text.setFillColor( sf::Color::Black );
    m_counter_text.setPosition( position + sf::Vector2f{ SIZE_X + text_width + 2 * PADDING, 0.f } );

    m_increase_button = std::make_shared< RectButton >(
            "+",
            position + sf::Vector2f{ 2 * SIZE_X + text_width + 3 * PADDING, 0.f },
            sf::Vector2f{ SIZE_X, SIZE_Y },
            [ this ]( ) { on_increase_pressed( ); } );
}

void
SpinnerControl::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    m_decrease_button->draw( target, states );
    m_increase_button->draw( target, states );
    target.draw( m_counter_text );
    target.draw( m_name );
}

bool
SpinnerControl::consume_event( sf::Event event, sf::Window& window )
{
    return m_decrease_button->consume_event( event, window )
           || m_increase_button->consume_event( event, window );
}

int
SpinnerControl::width( )
{
    return SIZE_Y * 3 + PADDING * 3 + m_name.getLocalBounds( ).width;
}

void
SpinnerControl::on_decrease_pressed( )
{
    m_counter--;
    m_counter_text.setString( std::to_string( m_counter ) );
    m_callback( m_counter );
}

void
SpinnerControl::on_increase_pressed( )
{
    m_counter++;
    m_counter_text.setString( std::to_string( m_counter ) );
    m_callback( m_counter );
}
