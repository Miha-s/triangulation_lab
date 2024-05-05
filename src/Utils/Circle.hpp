#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

inline float
distance( const sf::Vector2f& first, const sf::Vector2f& second )
{
    auto vec = second - first;
    return std::sqrt( vec.x * vec.x + vec.y * vec.y );
}

struct Circle
{
    sf::Vector2f center;
    float radius;

    bool
    contains_point( const sf::Vector2f& point ) const
    {
        return distance( point, center ) < radius;
    }

    bool
    overlaps( const Circle& other ) const
    {
        return distance( center, other.center ) < radius + other.radius;
    }

    sf::Vector2f
    point_on_circle( const float& angle ) const
    {
        auto point =
                center + sf::Vector2f{ radius * std::cos( angle ), radius * std::sin( angle ) };
        return point;
    }
};


#endif // CIRCLE_HPP
