#include "pch.h"

#include "Game.h"
#include "InputManager.h"
#include "IObserver.h"

//add game object include file?
#include "Level.h"
#include "Player.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "MainMenu.h"
#include "BossManager.h"

//temp
#include <iostream>
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	InputManager::GetInstance().Init(window);
	Initialize();
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
	m_Scene = std::make_unique<Scene>();

	//make sure camera is first
	m_Scene->AddGameObject<Camera>(viewport.width, viewport.height);

	m_Scene->AddGameObject<Level>();
	m_Scene->AddGameObject<Player>();
	m_Scene->AddGameObject<EnemyManager>(m_Scene->GetGameObject<Player>());

	CollisionSingleton::GetInstance().AddPlayer(m_Scene->GetGameObject<Player>());
}

void Game::CreateHud()
{
	m_Hud = std::make_unique<Scene>();
	m_Hud->AddGameObject<PlayerHealthBar>(Rectf{ 20.0f, 20.0f, 300.0f, 40.0f }, Color4f{ 0.0f, 1.0f, 0.0f, 1.0f }, m_Scene->GetGameObject<Player>()->GetHealth());
	m_Hud->GetGameObject<PlayerHealthBar>()->SetActive();

	auto& viewport = GetViewPort();
	Rectf bossHealthBar{ viewport.width * 0.25f, viewport.height - 80.0f, viewport.width * 0.5f, 40.0f };
	m_Hud->AddGameObject<BossHealthBar>(bossHealthBar, Color4f{ 1.0f, 0.0f, 0.0f, 1.0f }, m_Scene->GetGameObject<Player>()->GetHealth());

	//oops
	m_Scene->AddGameObject<BossManager>(m_Scene->GetGameObject<Player>(), m_Hud->GetGameObject<BossHealthBar>());
	m_BossManagerPtr = m_Scene->GetGameObject<BossManager>();
}

void Game::CreateMenus()
{
	auto& viewport = GetViewPort();
	m_MainMenu = std::make_unique<Scene>();
	m_Controlls = std::make_unique<Scene>();

	m_MainMenu->AddGameObject<MainMenu>(Point2f{ viewport.width, viewport.height });
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
	if (m_GameState == GameState::LEVEL)
	{
		auto& input = InputManager::GetInstance();
		(void) input.ProcessInput();
	}

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_RETURN])
		if (m_GameState == GameState::MAIN_MENU)
		{
			int selection = m_MainMenu->GetGameObject<MainMenu>()->GetSelectedButton();
			if (selection == 0)
			{
				m_GameState = GameState::LEVEL;
			}
		}

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

	switch (m_GameState)
	{
	case GameState::INTRO:
		break;
	case GameState::MAIN_MENU:
		m_MainMenu->Update();
		break;
	case GameState::OPTIONS:
		break;
	case GameState::SETTINGS:
		break;
	case GameState::CONTROLS:
		break;
	case GameState::MENU:
		break;
	case GameState::UPGRADES:
		break;
	case GameState::CLASS_SELECTION:
		break;
	case GameState::LEVEL:
		m_Scene->Update();
		m_Hud->Update();

		if (m_BossManagerPtr->IsFinalBossDead())
			m_GameState = GameState::WIN;
		break;
	case GameState::PAUSE:
		break;
	case GameState::WIN:
		break;
	default:
		break;
	}

}

void Game::Draw( ) const
{
	ClearBackground();

	switch (m_GameState)
	{
	case GameState::INTRO:
		break;
	case GameState::MAIN_MENU:
		m_MainMenu->Render();
		break;
	case GameState::OPTIONS:
		break;
	case GameState::SETTINGS:
		break;
	case GameState::CONTROLS:
		break;
	case GameState::MENU:
		break;
	case GameState::UPGRADES:
		break;
	case GameState::CLASS_SELECTION:
		break;
	case GameState::LEVEL:
		glPushMatrix();
		{
			m_Scene->Render();
		}
		glPopMatrix();

		m_Hud->Render();
		break;
	case GameState::PAUSE:
		break;
	default:
		break;
	}
	
}
