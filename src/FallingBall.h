#pragma once
#include "DisplayObject.h"

class FallingBall : public DisplayObject {
public:
    FallingBall();
    ~FallingBall();

    // Inherited via GameObject
    void draw() override;
    void update() override;
    void clean() override;

    void m_reset();
    void m_move();

    bool bHit = false;
};
