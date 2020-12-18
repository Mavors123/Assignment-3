#include "PlayScene2.h"


#include "Background.h"
#include "Brick.h"
#include "EventManager.h"
#include "Game.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "ship.h"
#include "SpaceManager.h"

PlayScene2::PlayScene2() {
    PlayScene2::start();
}

PlayScene2::~PlayScene2() = default;

void PlayScene2::draw() {

    drawDisplayList();

    if (EventManager::Instance().isIMGUIActive()) {
        GUI_Function();
    }

    SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene2::update() {
    updateDisplayList();

    if (CollisionManager::circleAABBCheck(m_pBouncingBall, m_pBrick)) {
        m_pBouncingBall->getRigidBody()->velocity += m_pBrick->getRigidBody()->velocity;
    }
}

void PlayScene2::clean() {

    removeAllChildren();
}

void PlayScene2::handleEvents() {
    EventManager::Instance().update();

    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->quit();
    }

    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0)) {
        TheGame::Instance()->changeSceneState(START_SCENE);
    }

    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1)) {
        TheGame::Instance()->changeSceneState(PLAY1_SCENE);
    }

    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2)) {
        TheGame::Instance()->changeSceneState(PLAY2_SCENE);
    }

    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3)) {
        TheGame::Instance()->changeSceneState(END_SCENE);
    }
    
    // if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) {
    //     m_pBrick->moveLeft();
    // }
    //
    // if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)) {
    //     m_pBrick->moveRight();
    // }

    m_pBrick->getTransform()->position = SpaceManager::Instance().ScreenToWorld(EventManager::Instance().getMousePosition());
}

void PlayScene2::start() {
    // Set GUI Title
    m_guiTitle = "Play Scene 2";

    SoundManager::Instance().load("../Assets/audio/yay.ogg", "thunder", SOUND_SFX);

    m_pBackground = new Background();
    const auto Height = Config::SCREEN_HEIGHT;
    const auto Width = Config::SCREEN_WIDTH;
    
    m_pBackground->setWidth(Width);
    m_pBackground->setHeight(Height);
    addChild(m_pBackground);

    // m_pProjectile = new Projectile();
    // addChild(m_pProjectile);
    
    m_pBouncingBall = new BouncingBall();
    m_pBouncingBall->m_reset();
    addChild(m_pBouncingBall);

    m_pBrick = new Brick();
    m_pBrick->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH/ 2.f, 50.f);
    addChild(m_pBrick);
}

void PlayScene2::GUI_Function() {
    // Always open with a NewFrame
    ImGui::NewFrame();

    // See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
    ImGui::ShowDemoWindow();

    ImGui::Begin("Sim Options", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

    ImGui::Separator();

    ImGui::End();

    // Don't Remove this
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
    ImGui::StyleColorsDark();
}
