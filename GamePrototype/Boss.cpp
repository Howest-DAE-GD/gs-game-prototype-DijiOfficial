#include "pch.h"

#include "Boss.h"
#include "Player.h"
#include "TimeSingleton.h"
#include "ItemManager.h"

FinalBoss::FinalBoss(Scene* scene, Player* player)
	: Boss(scene, player, 0, 400)
{
	m_Shape = Rectf{ 6600, 300, 120.f, 120.f };
}

void FinalBoss::Update()
{
	if (m_State == BossState::DEAD or m_State == BossState::DISABLED)
		return;

	const Point2f playerPos = GetPlayer()->GetPosition();
	const Point2f bossPos = Point2f{ m_Shape.left, m_Shape.bottom };

	const Vector2f direction = Vector2f{ playerPos - bossPos }.Normalized();
	const float deltaTime = TimeSingleton::GetInstance().GetDeltaTime();

	m_Shape.left += direction.x * m_Speed * deltaTime;
	m_Shape.bottom += direction.y * m_Speed * deltaTime;

	m_CollisionSingleton.UpdateCollider(this, m_Shape);
	//m_CollisionSingleton.HitPlayerType(m_Shape, m_Damage);
}

void FinalBoss::Render() const
{
	if (m_State == BossState::DEAD)
		return;

	utils::SetColor(Color4f{ 1.f, 0.f, 1.f, 1.f });
	utils::FillRect(m_Shape);
}

void FinalBoss::Reset()
{
	m_Health->ResetHealth(400);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 6600, 300, 120.f, 120.f };
}

void Boss::Hit(int damage)
{
	m_Health->DealDamage(damage);

	if (m_Health->GetHealth() <= 0)
	{
		m_State = BossState::DEAD;
		ItemManager::GetInstance().DropItem(m_ID, Point2f{ m_Shape.left, m_Shape.bottom });
	}

	//m_CollisionSingleton.RemoveCollider(this); //put this in the destructor (of enemy even?)
}

FirstBoss::FirstBoss(Scene* scene, Player* player)
	: Boss(scene, player, 1, 100)
{
	m_Shape = Rectf{ 1400, 1200, 120.f, 120.f };
}

void FirstBoss::Update()
{
	if (m_State == BossState::DEAD or m_State == BossState::DISABLED)
		return;

	const Point2f playerPos = GetPlayer()->GetPosition();
	const Point2f bossPos = Point2f{ m_Shape.left, m_Shape.bottom };

	const Vector2f direction = Vector2f{ playerPos - bossPos }.Normalized();
	const float deltaTime = TimeSingleton::GetInstance().GetDeltaTime();

	m_Shape.left += direction.x * m_Speed * deltaTime;
	m_Shape.bottom += direction.y * m_Speed * deltaTime;

	m_CollisionSingleton.UpdateCollider(this, m_Shape);
	//m_CollisionSingleton.HitPlayerType(m_Shape, m_Damage);
}

void FirstBoss::Render() const
{
	if (m_State == BossState::DEAD)
		return;

	utils::SetColor(Color4f{ 0.5f, 0.5f, 1.f, 1.f });
	utils::FillRect(m_Shape);
}

void FirstBoss::Reset()
{
	m_Health->ResetHealth(100);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 1400, 1200, 120.f, 120.f };
}
