#pragma once
#include "Background.h"
#include "BouncingBall.h"
#include "Brick.h"
#include "Scene.h"
#include "ship.h"

class PlayScene2 : public Scene {
public:
    PlayScene2();
    ~PlayScene2();

    // Scene LifeCycle Functions
    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
    virtual void handleEvents() override;
    virtual void start() override;
    void GUI_Function();

    std::string m_guiTitle;
    Background* m_pBackground;

    Brick* m_pBrick;
    
    BouncingBall* m_pBouncingBall;
};
