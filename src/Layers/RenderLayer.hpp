#ifndef RENDERLAYER_HPP
#define RENDERLAYER_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <mutex>

class RenderLayer
{
public:
    virtual void clear() = 0;
    virtual void draw(sf::RenderTarget& render_target) = 0;

    virtual ~RenderLayer()
    {}
};


using RenderLayerPtr = std::shared_ptr<RenderLayer>;
using lock_guard = std::lock_guard<std::mutex>;


#endif // RENDERLAYER_HPP
