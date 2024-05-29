#pragma once
#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "IObserver.h"

//add game object include file?
#include "Level.h"
#include "Player.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "BossManager.h"
#include "DoorManager.h"
#include "SceneManager.h"
#include "ItemManager.h"
#include "ItemCounter.h"

//temp
#include <iostream>
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	InputManager::GetInstance().Init(window);
	Initialize();

	ItemManager::GetInstance().Init(SceneManager::GetInstance().GetScene("Level"), SceneManager::GetInstance().GetScene("Level")->GetGameObject<Player>());
	//BossManager::GetInstance().InitBoss(SceneManager::GetInstance().GetScene("Level")->GetGameObject<Player>(), SceneManager::GetInstance().GetScene("Hud")->GetGameObject<BossHealthBar>());
}

#pragma region Initialization
void Game::Initialize( )
{
	CreateMenus();
	CreateScene();
	CreateHud();

	//temp code

	CommandInit();
	CreateObservers();
}

void Game::CreateScene()
{
	auto& viewport = GetViewPort();
	const auto& scene = SceneManager::GetInstance().CreateScene("Level");

	//make sure camera is first
	scene->AddGameObject<Camera>(viewport.width, viewport.height);

	scene->AddGameObject<Level>();
	scene->AddGameObject<Player>();
	scene->AddGameObject<EnemyManager>(scene->GetGameObject<Player>());
	scene->AddGameObject<DoorManager>(scene->GetGameObject<Player>());
	scene->AddGameObject<Test>(scene->GetGameObject<Player>(), Point2f{ 4925.f, 1350.f });

	CollisionSingleton::GetInstance().AddPlayer(scene->GetGameObject<Player>());
}

void Game::CreateHud()
{
	const auto& scene = SceneManager::GetInstance().GetScene("Level");

	const auto& hud = SceneManager::GetInstance().CreateScene("Hud");
	hud->AddGameObject<PlayerHealthBar>(Rectf{ 20.0f, 20.0f, 300.0f, 40.0f }, Color4f{ 0.0f, 1.0f, 0.0f, 1.0f }, scene->GetGameObject<Player>()->GetHealth());
	hud->GetGameObject<PlayerHealthBar>()->SetActive();

	auto& viewport = GetViewPort();
	Rectf bossHealthBar{ viewport.width * 0.25f, viewport.height - 80.0f, viewport.width * 0.5f, 40.0f };
	hud->AddGameObject<BossHealthBar>(bossHealthBar, Color4f{ 1.0f, 0.0f, 0.0f, 1.0f }, scene->GetGameObject<Player>()->GetHealth());
	hud->AddGameObject<ItemCounter>();

	//oops
	scene->AddGameObject<BossManager>(scene->GetGameObject<Player>(), hud->GetGameObject<BossHealthBar>());
	//m_BossManagerPtr = scene->GetGameObject<BossManager>();
}

void Game::CreateMenus()
{
	auto& viewport = GetViewPort();
	const auto& menu = SceneManager::GetInstance().CreateScene("Menu");
	const auto& controls = SceneManager::GetInstance().CreateScene("Controls");
	//m_Controlls = std::make_unique<Scene>();

	menu->AddGameObject<MainMenu>(Point2f{ viewport.width, viewport.height });
}

void Game::CommandInit() const
{
	auto& input = InputManager::GetInstance();
	auto player = SceneManager::GetInstance().GetScene("Level")->GetGameObject<Player>();

	input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_W, player, Movement::Up);
	input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_A, player, Movement::Left);
	input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_S, player, Movement::Down);
	input.BindCommand<Move>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_D, player, Movement::Right);
	input.BindCommand<Rotate>(PlayerIdx::KEYBOARD, KeyState::MOUSEMOTION, SDL_SCANCODE_UNKNOWN, player);
	input.BindCommand<Attack>(PlayerIdx::KEYBOARD, KeyState::MOUSEUP, SDL_SCANCODE_UNKNOWN, player);
	input.BindCommand<Debug>(PlayerIdx::KEYBOARD, KeyState::HELD, SDL_SCANCODE_O, player);

	input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadUp, player, Movement::Up);
	input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadLeft, player, Movement::Left);
	input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadDown, player, Movement::Down);
	input.BindCommand<Move>(PlayerIdx::PLAYER1, KeyState::HELD, Controller::Button::DPadRight, player, Movement::Right);
}

void Game::CreateObservers()
{
	auto player = SceneManager::GetInstance().GetScene("Level")->GetGameObject<Player>();
	
	player->GetHealthObject()->AddObserver(MessageTypes::HEALTH_CHANGE, SceneManager::GetInstance().GetScene("Hud")->GetGameObject<PlayerHealthBar>());
}
#pragma endregion

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	InputManager::GetInstance().ProcessMouseMotionEvent(e);
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	InputManager::GetInstance().ProcessMouseUpEvent(e);
}

void Game::Update( float elapsedSec )
{
	SceneManager::GetInstance().Update();
	ItemManager::GetInstance().IsCollidingWithPlayer();
	//BossManager::GetInstance().Update();

	{ //ghetto fps counter
		frameCount++;
		totalElapsedTime += elapsedSec;
		if (totalElapsedTime >= 0.2f)
		{
			//std::cout << "FPS: " << frameCount / totalElapsedTime << "\n";
			frameCount = 0;
			totalElapsedTime = 0.0f;
		}
	}
}

void Game::Draw( ) const
{
	ClearBackground();

	SceneManager::GetInstance().Render();
	//BossManager::GetInstance().Render();
}
