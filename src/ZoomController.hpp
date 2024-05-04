#ifndef ZOOMCONTROLLER_HPP
#define ZOOMCONTROLLER_HPP

#include <algorithm>

class ZoomController
{
    float m_zoom = 1;
public:
    void increaseZoom();
    void decreaseZoom();

    float zoom();
};


#endif // ZOOMCONTROLLER_HPP
