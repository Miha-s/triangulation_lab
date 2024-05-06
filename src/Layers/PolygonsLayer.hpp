#ifndef POLYGONSLAYER_HPP
#define POLYGONSLAYER_HPP

#include <vector>

#include "RenderLayer.hpp"

class PolygonsLayer;
using PolygonsLayerPtr = std::shared_ptr< PolygonsLayer >;

class PolygonsLayer : public RenderLayer
{
    PolygonsLayerPtr m_next_polygon_layer;
protected:
    virtual void draw_polygons( sf::RenderTarget& render_targer ) = 0;
    virtual void add_polygon( const std::vector< sf::Vector2f >& points ) = 0;
    virtual void clear_polygons( ) = 0;

public:

    void add( std::vector< sf::Vector2f > points );
    void draw( sf::RenderTarget& render_target ) override final;
    void clear( ) override final;

    void set_next( PolygonsLayerPtr layer );
};

#endif  // POLYGONSLAYER_HPP
