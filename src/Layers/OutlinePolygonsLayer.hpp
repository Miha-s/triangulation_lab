#ifndef OUTLINEPOLYGONSLAYER_HPP
#define OUTLINEPOLYGONSLAYER_HPP

#include <Elements/Line.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "PolygonsLayer.hpp"

class OutlinePolygonsLayer : public PolygonsLayer
{
    std::vector< std::vector< sfLine > > m_polygons;
    std::mutex m_mutex;

public:
    void draw_polygons( sf::RenderTarget& render_targer ) override;
    void clear( ) override;
    void add_polygon( std::vector< sf::Vector2f > points ) override;
};

using OutlinePolygonsLayerPtr = std::shared_ptr< OutlinePolygonsLayer >;

#endif  // OUTLINEPOLYGONSLAYER_HPP
