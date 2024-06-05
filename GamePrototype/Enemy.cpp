#include "pch.h"

#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "TimeSingleton.h"
#include "ItemManager.h"
#include <cmath>
#include "SceneManager.h"

Goblin::Goblin(Scene* scene, Player* player, const Point2f& pos)
	: Enemy(scene, player)
	, m_Shape{ pos.x, pos.y, 25.f, 25.f }
{
	m_originalShape = m_Shape;
	m_CollisionSingleton.AddCollider(this, m_Shape);
}

Goblin::~Goblin()
{

}

void Goblin::Update()
{
	if (m_State == EnemyState::DEAD)
		return;

	//add collision to the fucker but probably ion the Enemy update instead
	const Point2f playerPos = GetPlayer()->GetPosition();
	const Point2f goblinPos = Point2f{ m_Shape.left, m_Shape.bottom };
	
	if (not m_AttackPlayer and utils::GetDistance(playerPos, goblinPos) <= m_AttackRange)
		m_AttackPlayer = true;
	
	if (not m_AttackPlayer)
		return;

	const Vector2f direction = Vector2f{ playerPos - goblinPos }.Normalized();
	const float deltaTime = TimeSingleton::GetInstance().GetDeltaTime();

	m_Shape.left += direction.x * m_Speed * deltaTime;
	m_Shape.bottom += direction.y * m_Speed * deltaTime;

	m_CollisionSingleton.UpdateCollider(this, m_Shape);
	m_CollisionSingleton.HitPlayerType(m_Shape, m_Damage);

}

void Goblin::Render() const
{
	if (m_State == EnemyState::DEAD)
		return;

	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	utils::FillRect(m_Shape);
}

void Goblin::Reset()
{
	if (m_State != EnemyState::DEAD)
	{
		// Ensure the collision singleton is still valid before removing
		if (&m_CollisionSingleton != nullptr)
		{
			m_CollisionSingleton.RemoveCollider(this);
		}
	}
}

//void Goblin::Reset()
//{
//	m_AttackPlayer = false;
//	m_Shape = m_originalShape;
//	m_State = EnemyState::ALIVE;
//	//m_CollisionSingleton.AddCollider(this, m_Shape);
//}

void Goblin::Hit(int)
{
	m_State = EnemyState::DEAD;
	m_CollisionSingleton.RemoveCollider(this); //put this in the destructor (of enemy even?)
	std::srand(std::time(nullptr));
	if (std::rand() % 10 < 1)
	{
		ItemManager::GetInstance().DropItem(69, Point2f{ m_Shape.left, m_Shape.bottom });
	}
}

Test::Test(Scene* scene, Player* player, const Point2f& pos)
	: Enemy(scene, player)
	, m_Shape{ pos.x, pos.y, 35.f, 35.f }
{
	m_CollisionSingleton.AddCollider(this, m_Shape);
}

void Test::Render() const
{
	if (m_State == EnemyState::DEAD)
		return;

	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	utils::FillRect(m_Shape);
}

void Test::Hit(int)
{
	m_State = EnemyState::DEAD;
	m_CollisionSingleton.RemoveCollider(this);

	ItemManager::GetInstance().DropItem(7, Point2f{ m_Shape.left, m_Shape.bottom });
}

Turret::Turret(Scene* scene, Player* player, const Point2f& pos)
	: Enemy(scene, player)
	, m_Shape{ pos.x, pos.y, 25.f, 25.f }
{
	m_originalShape = m_Shape;
	m_CollisionSingleton.AddCollider(this, m_Shape);
}

void Turret::Update()
{
	if (not m_Bullets.empty())
	{
		auto& collision = CollisionSingleton::GetInstance();
		for (size_t i{}; i < m_Bullets.size(); ++i)
		{
			m_Bullets[i]->Update();
		}

		for (auto it = m_Bullets.begin(); it != m_Bullets.end();)
		{
			const auto& shape = (*it)->GetShape();
			if (SceneManager::GetInstance().GetScene("Level")->GetGameObject<Level>()->IsPlayerColliding(shape) or collision.HitPlayerType(shape, m_Damage))
				it = m_Bullets.erase(it);
			else
				++it;
		}
	}

	if (m_State == EnemyState::DEAD)
		return;

	const Point2f playerPos = GetPlayer()->GetPosition();
	const Point2f goblinPos = Point2f{ m_Shape.left, m_Shape.bottom };

	if (not m_AttackPlayer and utils::GetDistance(playerPos, goblinPos) <= m_AttackRange)
		m_AttackPlayer = true;

	if (not m_AttackPlayer)
		return;

	if (attacked)
	{
		timer += TimeSingleton::GetInstance().GetDeltaTime();
		if (timer >= 1.5f)
		{
			timer = 0;
			attacked = false;
		}
		return;
	}

	const auto& playerShape = GetPlayer()->GetShape();

	const Point2f playerCenter = Point2f{
		playerShape.left + playerShape.width * 0.5f,
		playerShape.bottom + playerShape.height * 0.5f
	};

	const Point2f turretCenter = Point2f{
		m_Shape.left + m_Shape.width * 0.5f,
		m_Shape.bottom + m_Shape.height * 0.5f
	};

	const float dirX = playerCenter.x - turretCenter.x;
	const float dirY = playerCenter.y - turretCenter.y;

	const float angle = std::atan2(dirY, dirX);

	const float cannonLength = 30.f;
	const float cannonWidth = 5.f;

	Point2f cannonEnd = Point2f{
		turretCenter.x + cannonLength * std::cos(angle),
		turretCenter.y + cannonLength * std::sin(angle)
	};

	const float angleDeg = static_cast<float>(angle * (180.0 / M_PI));

	m_Bullets.push_back(std::make_unique<Bullets>(cannonEnd, angleDeg, Color4f{ 0.f,0.f,1.f,1.f }));
	attacked = true;

}

void Turret::Render() const
{
	if (not m_Bullets.empty())
	{
		for (size_t i{}; i < m_Bullets.size(); ++i)
		{
			m_Bullets[i]->Render();
		}
	}

	if (m_State == EnemyState::DEAD)
		return;

	utils::SetColor(Color4f{ 0.75f, 1.f, 0.75f, 1.f });
	utils::FillRect(m_Shape);

	const auto& playerPos = GetPlayer()->GetShape();
	Point2f playerCenter = Point2f{
		playerPos.left + playerPos.width  * 0.5f,
		playerPos.bottom + playerPos.height  * 0.5f
	};
	Point2f turretCenter = Point2f{
		m_Shape.left + m_Shape.width * 0.5f,
		m_Shape.bottom + m_Shape.height * 0.5f
	};
	float dirX = playerCenter.x - turretCenter.x;
	float dirY = playerCenter.y - turretCenter.y;

	float angle = std::atan2(dirY, dirX);

	float cannonLength = 30.f;
	float cannonWidth = 5.f;

	Point2f cannonEnd = Point2f{
		turretCenter.x + cannonLength * std::cos(angle),
		turretCenter.y + cannonLength * std::sin(angle)
	};

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::DrawLine(turretCenter, cannonEnd, cannonWidth);
}

void Turret::Reset()
{
	if (m_State != EnemyState::DEAD)
	{
		// Ensure the collision singleton is still valid before removing
		if (&m_CollisionSingleton != nullptr)
		{
			m_CollisionSingleton.RemoveCollider(this);
		}
	}
}

void Turret::Hit(int damage)
{
	health -= damage;
	if (health > 0)
		return;

	m_State = EnemyState::DEAD;
	m_CollisionSingleton.RemoveCollider(this);
	std::srand(std::time(nullptr));
	if (std::rand() % 7 < 1)
	{
		ItemManager::GetInstance().DropItem(69, Point2f{ m_Shape.left, m_Shape.bottom });
	}
}
