#include "FallingBall.h"


#include "SpaceManager.h"
#include "TextureManager.h"

FallingBall::FallingBall() {
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

FallingBall::~FallingBall() = default;

void FallingBall::draw() {
    // alias for x and y
    const auto x = getTransform()->position.x;
    const auto y = getTransform()->position.y;

    const auto ScreenPosition = SpaceManager::Instance().WorldToScreen(glm::vec2(x,y));
    
    // draw the ship
    TextureManager::Instance()->draw("ball", ScreenPosition.x, ScreenPosition.y, 0, 255, true);
}

void FallingBall::update() {
    m_move();
}

void FallingBall::clean() {
}

void FallingBall::m_reset() {
    getRigidBody()->acceleration = glm::vec2(0, -9.8f);
    getTransform()->position.x = rand() % (Config::SCREEN_WIDTH - 100) + 50;
    getTransform()->position.y = Config::SCREEN_HEIGHT + (rand() % 100 + 1);
    getRigidBody()->velocity = glm::vec2();
}

void FallingBall::m_move() {
    getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration * (1.f / 60.f);
    
    if (getTransform()->position.y <= 0) {
        m_reset();
    }
    
    getTransform()->position = getTransform()->position + getRigidBody()->velocity;
}
