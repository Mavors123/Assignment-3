#pragma once
#include <glm/detail/type_vec2.hpp>

class SpaceManager {
public:
    static SpaceManager& Instance()
    {
        static SpaceManager instance;
        return instance;
    }

    glm::vec2 ScreenToWorld(glm::vec2 ScreenPosition);
    glm::vec2 WorldToScreen(glm::vec2 WorldPosition);

    float PixelsPerMeter = 1.0f;
    glm::vec2 CameraPosition = glm::vec2{0, 0}; 

private:
     
    SpaceManager();
};
