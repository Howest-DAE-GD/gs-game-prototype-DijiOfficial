#include "pch.h"
#include "Player.h"
#include "Texture.h"

Player::Player(Scene* scene)
	: GameObject{ scene }
	, m_Shape{ 0, 0, 36, 97 }
	, m_pSpritesTexture{ new Texture {"Images/AvatarSheet.png"} }
{
}

void Player::Update()
{
}

void Player::Render() const
{
	Rectf srcRect{};
	srcRect.width = 72.f;
	srcRect.height = 97.f;
	srcRect.left = 0.f;
	srcRect.bottom = 0.f;

	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	glPushMatrix();
	{
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		//utils::FillRect(m_Shape);
		m_pSpritesTexture->Draw(Point2f{ 0.f, 0.f }, srcRect);
	}
	glPopMatrix();
}
