#ifndef CONVEXPOLYGONSLAYER_HPP
#define CONVEXPOLYGONSLAYER_HPP

#include <SFML/Graphics/ConvexShape.hpp>
#include <vector>

#include "PolygonsLayer.hpp"

class ConvexPolygonsLayer : public PolygonsLayer
{
    std::vector< sf::ConvexShape > m_polygons;
    std::mutex m_mutex;
    sf::Color m_color;
public:
    ConvexPolygonsLayer( sf::Color color );

protected:
    void draw_polygons( sf::RenderTarget& render_targer ) override;
    void clear_polygons( ) override;
    void add_polygon( const std::vector< sf::Vector2f >& points ) override;
};

using ConvexPolygonsLayerPtr = std::shared_ptr< ConvexPolygonsLayer >;

#endif  // CONVEXPOLYGONSLAYER_HPP
