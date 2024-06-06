#include "pch.h"

#include "Boss.h"
#include "Player.h"
#include "TimeSingleton.h"
#include "ItemManager.h"
#include "SceneManager.h"
#include "ItemCounter.h"
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
		SceneManager::GetInstance().GetScene("Hud")->GetGameObject<ItemCounter>()->AddDeadBoss();

		if (SceneManager::GetInstance().GetScene("Level")->GetGameObject<BossManager>()->GetAreAllBossesDead())
		{
			ItemManager::GetInstance().DropItem(0, Point2f{ m_Shape.left, m_Shape.bottom });
		}
		else
			ItemManager::GetInstance().DropItem(m_ID, Point2f{ m_Shape.left, m_Shape.bottom });
		
		m_CollisionSingleton.RemoveCollider(this);
	}

}

FirstBoss::FirstBoss(Scene* scene, Player* player, int id, int health )
	: Boss(scene, player, id, health)
{
	//m_Shape = Rectf{ 1400, 1200, 120.f, 120.f };
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
	m_CollisionSingleton.HitPlayerType(m_Shape, 20);
	//m_CollisionSingleton.HitPlayerType(m_Shape, m_Damage);
}

void FirstBoss::Render() const
{
	if (m_State == BossState::DEAD)
		return;

	utils::SetColor(Color4f{ 0.5f, 0.5f, 1.f, 1.f });
	utils::FillRect(m_Shape);
}

void RealFirstBoss::Reset()
{
	m_Health->ResetHealth(100);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 1400, 1200, 120.f, 120.f };
}

RealFirstBoss::RealFirstBoss(Scene* scene, Player* player)
	: FirstBoss(scene, player, 1, 100)
{
	m_Shape = Rectf{ 1400, 1200, 120.f, 120.f };
}
SecondBoss::SecondBoss(Scene* scene, Player* player)
	: FirstBoss(scene, player, 2, 200)
{
	m_Shape = Rectf{ 4000.f, 3850.f, 120.f, 120.f };
}

void SecondBoss::Reset()
{
	m_Health->ResetHealth(200);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 4000.f, 3850.f, 120.f, 120.f };
}

ThirdBoss::ThirdBoss(Scene* scene, Player* player)
	: FirstBoss(scene, player, 3, 300)
{
	m_Shape = Rectf{ 1150.f, 4930.f, 120.f, 120.f };
}

void ThirdBoss::Reset()
{
	m_Health->ResetHealth(300);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 1150.f, 4930.f, 120.f, 120.f };
}

FourthBoss::FourthBoss(Scene* scene, Player* player)
	: FirstBoss(scene, player, 4, 400)
{
	m_Shape = Rectf{ 8400.f, 3300.f, 120.f, 120.f };
}

void FourthBoss::Reset()
{
	m_Health->ResetHealth(400);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 8400.f, 3300.f, 120.f, 120.f };
}

FifthBoss::FifthBoss(Scene* scene, Player* player)
	: FirstBoss(scene, player, 5, 400)
{
	m_Shape = Rectf{ 9000.f, 400.f, 120.f, 120.f };
}

void FifthBoss::Reset()
{
	m_Health->ResetHealth(400);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 9000.f, 400.f, 120.f, 120.f };
}

SixthBoss::SixthBoss(Scene* scene, Player* player)
	: FirstBoss(scene, player, 6, 400)
{
	m_Shape = Rectf{ 5450.f, 1900.f, 120.f, 120.f };
}

void SixthBoss::Reset()
{
	m_Health->ResetHealth(400);
	m_State = BossState::DISABLED;
	m_Shape = Rectf{ 5450.f, 1900.f, 120.f, 120.f };
}