#include "pch.h"
#include "Player.h"

Player::Player(Scene* scene)
	: GameObject{ scene }
	, m_Shape{ 0, 0, 45, 45 }
{
}

void Player::Update()
{
}

void Player::Render()
{
	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	utils::FillRect(m_Shape);
}
