#include "pch.h"
#include "Scene.h"

#include "Level.h"
#include "Player.h"
#include "Camera.h"

#include "InputManager.h"
#include "EnemyManager.h"

Scene::Scene(Rectf viewport)
{
    //make sure camera is first
    AddGameObject<Camera>(viewport.width, viewport.height);
    
    AddGameObject<Level>();
    AddGameObject<Player>();
    AddGameObject<EnemyManager>();

    CommandInit();
}

void Scene::Update()
{
    for (auto& gameObject : m_GameObjects)
    {
        gameObject->Update();
    }
}

void Scene::Render() const
{
    for (const auto& gameObject : m_GameObjects)
    {
		gameObject->Render();
	}
}

void Scene::CommandInit() const
{
    auto& input = InputManager::GetInstance();
    auto player = GetGameObject<Player>();

    input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_W, player, Movement::Up);
    input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_A, player, Movement::Left);
    input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_S, player, Movement::Down);
    input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_D, player, Movement::Right);
    input.BindCommand<Rotate>(PlayerIdx::KEYBOARD, KeyState::MOUSEMOTION, SDL_SCANCODE_UNKNOWN, player);
    input.BindCommand<Attack>(PlayerIdx::KEYBOARD, KeyState::MOUSEUP, SDL_SCANCODE_UNKNOWN, player);

    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadUp, player, Movement::Up);
    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadLeft, player, Movement::Left);
    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadDown, player, Movement::Down);
    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadRight, player, Movement::Right);
}
