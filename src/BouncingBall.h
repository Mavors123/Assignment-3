#pragma once
#include "DisplayObject.h"
#include "GameObject.h"

class BouncingBall : public DisplayObject {
public:
    BouncingBall();
    ~BouncingBall();

    // Inherited via GameObject
    void draw() override;
    void update() override;
    void clean() override;

    void m_reset();
    void m_checkBounds();
    void m_bounce();
    void m_move();

    float frictionFactor = 0.999f;
};
