#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TimeSingleton.h"

Player::Player(Scene* scene)
	: GameObject{ scene }
	, m_Shape{ 4900, 1000, 64.f, 64.f }
{
	//m_pSpritesTexture = ResourceManager::GetInstance().LoadTexture("Images/AvatarSheet.png");
	m_LevelPtr = GetOwner()->GetGameObject<Level>();
	m_BasicAttack = std::make_unique<ShootAttack>(m_LevelPtr);
	m_Health = std::make_unique<Health>(400);
}

void Player::Update()
{
	m_BasicAttack->Update();

	//maybe it's own function or class?
	const float dt = TimeSingleton::GetInstance().GetDeltaTime();
	if (m_IsInvincible)
	{
		m_Iframes += dt;
		if (m_Iframes >= 0.5f)
		{
			m_IsInvincible = false;
			m_Iframes = 0.0f;
		}
	}
}

void Player::Render() const
{
	Rectf srcRect{};
	srcRect.width = 72.f;
	srcRect.height = 97.f;
	srcRect.left = 0.f;
	srcRect.bottom = 0.f;

	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });

	const float centerX = m_Shape.left + (m_Shape.width * 0.5f);
	const float centerY = m_Shape.bottom + (m_Shape.height * 0.5f);

	glPushMatrix();
	{
		glTranslatef(centerX, centerY, 0.0);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(-centerX, -centerY, 0.0);
	
		const Rectf smallRect{ centerX + m_Shape.width *0.5f, centerY - 3, 12.f, 6.f };
		
		utils::FillRect(m_Shape);
		utils::FillRect(smallRect);
		
	}
	glPopMatrix();

	m_BasicAttack->Render();
	//utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	//utils::DrawRect(m_Shape);
}

bool Player::IsColliding(const Rectf& actorShape) const
{
	return m_LevelPtr->IsPlayerColliding(actorShape);
}

Point2f Player::GetRelativeCenter() const
{
	const auto& camera = GetOwner()->GetGameObject<Camera>();
	const Point2f playerCenter{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2 };
	const Rectf cameraPos = camera->GetCameraPos(m_Shape);

	const Point2f relativeCenter{
		playerCenter.x - cameraPos.left,
		playerCenter.y - cameraPos.bottom
	};

	return relativeCenter;
}

void Player::Attack()
{
	const double angle = m_Angle * M_PI / 180.0;

	//radius x and y for non square shapes
	const float radius = m_Shape.width * 0.5f;
	const float centerX = m_Shape.left + radius;
	const float centerY = m_Shape.bottom + radius;

	Point2f projectilePosition;
	projectilePosition.x = centerX + radius * cos(angle);
	projectilePosition.y = centerY + radius * sin(angle);

	m_BasicAttack->Attack(projectilePosition, m_Angle);
}

void Player::DealDamage(const int damage)
{
	m_Health->DealDamage(damage);
	// maybe get type of damage so you can still get hit by projectiles?
	m_IsInvincible = true;
	//get health if 0 die or some
}
