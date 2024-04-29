#include "pch.h"
#include "Game.h"
#include "InputManager.h"

//temp
#include <iostream>
#include "EnemyManager.h"
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	InputManager::GetInstance().Init(window);
	Initialize();
}

void Game::Initialize( )
{
	m_Scene = std::make_unique<Scene>(GetViewPort());
	//temp code
	m_Scene->GetGameObject<EnemyManager>()->AddEnemy(m_Scene.get(), m_Scene->GetGameObject<Player>(), Point2f{ 5300.0f, 1300.0f });
}

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
}

void Game::Draw( ) const
{
	ClearBackground( );
	glPushMatrix();
	{
		m_Scene->Render();
	}
	glPopMatrix();
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.9f, 0.9f, 0.9f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
