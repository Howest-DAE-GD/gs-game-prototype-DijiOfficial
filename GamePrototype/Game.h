#pragma once
#include "BaseGame.h"
#include "Scene.h"

class BossManager;

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
	BossManager* m_BossManagerPtr = nullptr;
	int frameCount = 0;
	float totalElapsedTime = 0.0f;
	
	// FUNCTIONS
	void Initialize();
	void CreateScene();
	void CreateHud();
	void CreateMenus();
	void CommandInit() const;
	void CreateObservers();
	
	void ClearBackground() const { glClearColor(0.3f, 0.3f, 0.3f, 1.0f); glClear(GL_COLOR_BUFFER_BIT); }

	//temp code 
};