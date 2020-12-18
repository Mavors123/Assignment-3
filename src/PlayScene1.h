#pragma once
#include "Background.h"
#include "FallingBall.h"
#include "Projectile.h"
#include "Scene.h"
#include "ship.h"

class PlayScene1 : public Scene {
public:
    PlayScene1();
    ~PlayScene1();

    // Scene LifeCycle Functions
    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;
    virtual void handleEvents() override;
    virtual void start() override;
    void GUI_Function();

    std::string m_guiTitle;
    Background* m_pBackground;
    Projectile* m_pProjectile;

    Ship* m_pSpaceship;
    
    std::vector<FallingBall*> m_pFallingBallPool;
};
