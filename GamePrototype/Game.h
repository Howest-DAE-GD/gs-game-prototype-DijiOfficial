#pragma once
#include "BaseGame.h"
#include "Scene.h"

enum class GameState
{
	INVALID,
	INTRO,
	MAIN_MENU,
	OPTIONS,
	SETTINGS,
	CONTROLS,
	MENU,
	UPGRADES,
	CLASS_SELECTION,
	LEVEL,
	PAUSE,
};

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
	std::unique_ptr<Scene> m_MainMenu;
	std::unique_ptr<Scene> m_Controlls;

	GameState m_GameState = GameState::MAIN_MENU;
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
};