#include "pch.h"
#include "Scene.h"

#include "Level.h"
#include "Player.h"
#include "Camera.h"

#include "InputManager.h"

Scene::Scene()
{
    AddGameObject<Level>();
    AddGameObject<Player>();
    AddGameObject<Camera>(1920.f, 1080.f);

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

    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadUp, player, Movement::Up);
    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadLeft, player, Movement::Left);
    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadDown, player, Movement::Down);
    input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadRight, player, Movement::Right);
}
