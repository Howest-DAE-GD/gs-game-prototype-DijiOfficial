#pragma once
#include "pch.h"

class Player final
{
public:
	Player();
	~Player() = default;

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	void Update();
	void Render();

private:
	Point2i m_Pos;
};

