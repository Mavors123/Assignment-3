#include "BouncingBall.h"

#include <glm/detail/func_geometric.inl>


#include "SpaceManager.h"
#include "TextureManager.h"

BouncingBall::BouncingBall() {
    TextureManager::Instance()->load("../Assets/textures/mine.png", "ball");

    auto size = TextureManager::Instance()->getTextureSize("ball");
    setWidth(size.x);
    setHeight(size.y);

    getTransform()->position = glm::vec2(100.0f, 100.0f);
    getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    getRigidBody()->isColliding = false;
    setType(FALLING_BALL);
}

BouncingBall::~BouncingBall() = default;

void BouncingBall::draw() {
    // alias for x and y
    const auto x = getTransform()->position.x;
    const auto y = getTransform()->position.y;

    const auto ScreenPosition = SpaceManager::Instance().WorldToScreen(glm::vec2(x, y));

    // draw the ship
    TextureManager::Instance()->draw("ball", ScreenPosition.x, ScreenPosition.y, 0, 255, true);
}

void BouncingBall::update() {
    m_move();
    m_checkBounds();
}

void BouncingBall::clean() {
}

void BouncingBall::m_reset() {
    // getRigidBody()->acceleration = glm::vec2(0, -9.8f);
    getTransform()->position.x = rand() % (Config::SCREEN_WIDTH - 100) + 50;
    getTransform()->position.y = rand() % (Config::SCREEN_HEIGHT - 100) + 50;
    getRigidBody()->velocity = glm::vec2(rand() % 2 + 1, rand() % 10 + 1);
}

void BouncingBall::m_checkBounds() {
    auto vDirect = getRigidBody()->velocity;
    auto vNormal = glm::vec2(0, 0);

    if (getTransform()->position.x > Config::SCREEN_WIDTH) {
        vNormal = glm::vec2(-1.f, 0);
    }

    if (getTransform()->position.x < 0) {
        vNormal = glm::vec2(1.f, 0);
    }

    if (getTransform()->position.y > Config::SCREEN_HEIGHT) {
        vNormal = glm::vec2(0, 1);
    }

    if (getTransform()->position.y < 0) {
        vNormal = glm::vec2(0, -1);
    }

    // r=d−2(d⋅n)n
    auto vReflect = vDirect - 2 * (glm::dot(vDirect, vNormal)) * vNormal;
    getRigidBody()->velocity = vReflect;

    // Reset ball if it managed to escape the game field
    if ((getTransform()->position.x >= Config::SCREEN_WIDTH * 2)
        || getTransform()->position.x <= -Config::SCREEN_WIDTH
        || getTransform()->position.y <= -Config::SCREEN_HEIGHT
        || getTransform()->position.y >= Config::SCREEN_HEIGHT * 2) {
        m_reset();
    }

}

void BouncingBall::m_bounce() {
    // getTransform()->position.x = rand() % (Config::SCREEN_WIDTH - 100) + 50;
    // getTransform()->position.y = Config::SCREEN_HEIGHT + (rand() % 100 + 1);
    // getRigidBody()->velocity = glm::vec2();
}

void BouncingBall::m_move() {
    getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration * (1.f / 60.f);
    getTransform()->position = getTransform()->position + getRigidBody()->velocity;
    getRigidBody()->velocity *= frictionFactor;
}
