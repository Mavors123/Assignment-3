#include "SpaceManager.h"

#include <glm/detail/type_vec2.hpp>

#include "Config.h"

glm::vec2 SpaceManager::ScreenToWorld(glm::vec2 ScreenPosition) {
    glm::vec2 WorldPosition = ScreenPosition + CameraPosition;
    WorldPosition.y = Config::SCREEN_HEIGHT-WorldPosition.y;
    WorldPosition /= PixelsPerMeter;
    return WorldPosition;
}

glm::vec2 SpaceManager::WorldToScreen(glm::vec2 WorldPosition) {
    glm::vec2 ScreenPosition = WorldPosition - CameraPosition;
    ScreenPosition.y = Config::SCREEN_HEIGHT - ScreenPosition.y;
    ScreenPosition *= PixelsPerMeter;
    return ScreenPosition;
}

SpaceManager::SpaceManager() {
    
}
