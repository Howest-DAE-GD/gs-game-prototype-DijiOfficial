#include "pch.h"

#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "TimeSingleton.h"
#include "ItemManager.h"

Goblin::Goblin(Scene* scene, Player* player, const Point2f& pos)
	: Enemy(scene, player)
	, m_Shape{ pos.x, pos.y, 25.f, 25.f }
{
	m_originalShape = m_Shape;
	m_CollisionSingleton.AddCollider(this, m_Shape);
}

Goblin::~Goblin()
{
	if (m_State != EnemyState::DEAD)
		m_CollisionSingleton.RemoveCollider(this);
};

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

//void Goblin::Reset()
//{
//	m_AttackPlayer = false;
//	m_Shape = m_originalShape;
//	m_State = EnemyState::ALIVE;
//	//m_CollisionSingleton.AddCollider(this, m_Shape);
//}

void Goblin::Hit()
{
	m_State = EnemyState::DEAD;
	m_CollisionSingleton.RemoveCollider(this); //put this in the destructor (of enemy even?)
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

void Test::Hit()
{
	m_State = EnemyState::DEAD;
	m_CollisionSingleton.RemoveCollider(this);

	ItemManager::GetInstance().DropItem(7, Point2f{ m_Shape.left, m_Shape.bottom });
}
