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

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

private:
	std::unique_ptr<Scene> m_Scene;

	// FUNCTIONS
	void Initialize();
	void ClearBackground( ) const;
};