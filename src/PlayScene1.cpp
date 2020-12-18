#include "PlayScene1.h"


#include "Background.h"
#include "EventManager.h"
#include "Game.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "ship.h"

PlayScene1::PlayScene1() {
    PlayScene1::start();
}

PlayScene1::~PlayScene1() = default;

void PlayScene1::draw() {

    drawDisplayList();

    if (EventManager::Instance().isIMGUIActive()) {
        GUI_Function();
    }

    SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene1::update() {
    updateDisplayList();

    for (auto pBall : m_pFallingBallPool) {
        if (CollisionManager::AABBCheck(pBall, m_pSpaceship)) {
            if (!pBall->bHit) {
                pBall->bHit = true;
                SoundManager::Instance().playSound("thunder");
            }
        }
    }
    
    // updateLabels();
}

void PlayScene1::clean() {

    removeAllChildren();
}

void PlayScene1::handleEvents() {
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
    
    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) {
        m_pSpaceship->moveLeft();
    }
    
    if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)) {
        m_pSpaceship->moveRight();
    }
}

void PlayScene1::start() {
    // Set GUI Title
    m_guiTitle = "Play Scene 2";

    SoundManager::Instance().load("../Assets/audio/thunder.ogg", "thunder", SOUND_SFX);

    m_pBackground = new Background();
    const auto Height = Config::SCREEN_HEIGHT;
    const auto Width = Config::SCREEN_WIDTH;
    
    m_pBackground->setWidth(Width);
    m_pBackground->setHeight(Height);
    addChild(m_pBackground);

    // m_pProjectile = new Projectile();
    // addChild(m_pProjectile);
    
    for (auto i = 0; i < 10; i++) {
        auto pFallingBall = new FallingBall();
        m_pFallingBallPool.push_back(pFallingBall);

        pFallingBall->m_reset();
        
        addChild(pFallingBall);
    }

    m_pSpaceship = new Ship();
    m_pSpaceship->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH/ 2.f, 50.f);
    addChild(m_pSpaceship);
}

void PlayScene1::GUI_Function() {
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
