#include "pch.h"

#include "Game.h"
#include "InputManager.h"
#include "IObserver.h"

//add game object include file?
#include "Level.h"
#include "Player.h"
#include "Camera.h"
#include "EnemyManager.h"

//temp
#include <iostream>
#include "EnemyManager.h"
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	InputManager::GetInstance().Init(window);
	Initialize();
}

#pragma region Initialization
void Game::Initialize( )
{
	CreateScene();
	CreateHud();

	//temp code
	m_Scene->GetGameObject<EnemyManager>()->AddEnemy(m_Scene.get(), m_Scene->GetGameObject<Player>(), Point2f{ 5300.0f, 1300.0f });

	CommandInit();
	CreateObservers();
}

void Game::CreateScene()
{
	auto& viewport = GetViewPort();
	m_Scene = std::make_unique<Scene>();

	//make sure camera is first
	m_Scene->AddGameObject<Camera>(viewport.width, viewport.height);

	m_Scene->AddGameObject<Level>();
	m_Scene->AddGameObject<Player>();
	m_Scene->AddGameObject<EnemyManager>();

	CollisionSingleton::GetInstance().AddPlayer(m_Scene->GetGameObject<Player>());
}

void Game::CreateHud()
{
	m_Hud = std::make_unique<Scene>();
	m_Hud->AddGameObject<PlayerHealthBar>(Rectf{ 20.0f, 20.0f, 300.0f, 40.0f }, Color4f{ 0.0f, 1.0f, 0.0f, 1.0f }, m_Scene->GetGameObject<Player>()->GetHealth());
}

void Game::CommandInit() const
{
	auto& input = InputManager::GetInstance();
	auto player = m_Scene->GetGameObject<Player>();

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

void Game::CreateObservers()
{
	auto player = m_Scene->GetGameObject<Player>();

	player->GetHealthObject()->AddObserver(MessageTypes::HEALTH_CHANGE, m_Hud->GetGameObject<PlayerHealthBar>());
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
	frameCount++;
	totalElapsedTime += elapsedSec;
	if (totalElapsedTime >= 0.2f)
	{
		//std::cout << "FPS: " << frameCount / totalElapsedTime << "\n";
		frameCount = 0;
		totalElapsedTime = 0.0f;
	}

	auto& input = InputManager::GetInstance();
	(void) input.ProcessInput();
	m_Scene->Update();
	m_Hud->Update();
}

void Game::Draw( ) const
{
	glPushMatrix();
	{
		m_Scene->Render();
	}
	glPopMatrix();

	m_Hud->Render();
}
