#ifndef OUTLINEPOLYGONSLAYER_HPP
#define OUTLINEPOLYGONSLAYER_HPP

#include <Elements/Line.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "PolygonsLayer.hpp"

class OutlinePolygonsLayer : public PolygonsLayer
{
    std::vector< std::vector< sfLine > > m_polygons;
    std::vector< sf::Color > m_colors;
    int current_color = 0;
    std::mutex m_mutex;
public:
    OutlinePolygonsLayer( std::vector< sf::Color > colors );

protected:
    void draw_polygons( sf::RenderTarget& render_targer ) override;
    void clear_polygons( ) override;
    void add_polygon( const std::vector< sf::Vector2f >& points ) override;
};

using OutlinePolygonsLayerPtr = std::shared_ptr< OutlinePolygonsLayer >;

#endif  // OUTLINEPOLYGONSLAYER_HPP
