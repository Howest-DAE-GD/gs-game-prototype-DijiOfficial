#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "TimeSingleton.h"

Goblin::Goblin(Scene* scene, Player* player, const Point2f& pos)
	: Enemy(scene, player)
	, m_Shape{ pos.x, pos.y, 25.f, 25.f }
{

};


void Goblin::Update()
{
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
}

void Goblin::Render() const
{
	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	utils::FillRect(m_Shape);
}
