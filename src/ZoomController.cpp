#include "ZoomController.hpp"

static constexpr float ZOOM_STEP = 0.05;
static constexpr float MAX_ZOOM = 5;
static constexpr float MIN_ZOOM = 0.1;

void ZoomController::increaseZoom()
{
    m_zoom = std::max(MIN_ZOOM, m_zoom - ZOOM_STEP);
}

void ZoomController::decreaseZoom()
{
    m_zoom = std::min(MAX_ZOOM, m_zoom + ZOOM_STEP);
}

float ZoomController::zoom()
{
    return m_zoom;
}
