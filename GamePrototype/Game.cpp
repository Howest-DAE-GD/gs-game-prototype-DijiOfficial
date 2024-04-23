#include "pch.h"
#include "Game.h"
#include "InputManager.h"

#include <iostream>
Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

void Game::Initialize( )
{
	m_Scene = std::make_unique<Scene>(GetViewPort());
}

void Game::Update( float elapsedSec )
{
	frameCount++;
	totalElapsedTime += elapsedSec;
	if (totalElapsedTime >= 0.2f)
	{
		std::cout << "FPS: " << frameCount / totalElapsedTime << "\n";
		frameCount = 0;
		totalElapsedTime = 0.0f;
	}

	auto& input = InputManager::GetInstance();
	(void) input.ProcessInput();
	m_Scene->Update();
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
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
