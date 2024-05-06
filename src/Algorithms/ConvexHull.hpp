#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>

std::vector< sf::Vector2f > convex_hull( const std::vector< sf::Vector2f >& a,
                                         bool include_collinear = false );

#endif // CONVEXHULL_HPP
