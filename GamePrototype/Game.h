#pragma once
#include "BaseGame.h"
#include "Scene.h"

class Game final : public BaseGame
{
public:
	explicit Game( const Window& window );
	~Game() = default;

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

private:
	std::unique_ptr<Scene> m_Scene;
	std::unique_ptr<Scene> m_Hud;

	int frameCount = 0;
	float totalElapsedTime = 0.0f;
	
	// FUNCTIONS
	void Initialize();
	void CreateScene();
	void CreateHud();
	void CommandInit() const;
	void CreateObservers();
	
};