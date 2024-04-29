#pragma once
#include "GameObject.h"
#include "CollisionSingleton.h"

class Player;
class Scene;

enum class EnemyState
{
	DISABLED = -1,
	ALIVE = 0,
	HIT,
	DYING,
	DEAD,

};

class Enemy : public GameObject
{
public:
	explicit Enemy(Scene* scene, Player* player) 
		: GameObject(scene)
		, m_PlayerPtr(player)
	{
	};
	~Enemy() override = default;

	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;

	void Update() override = 0;
	void Render() const override = 0;

	EnemyState GetState() const { return m_State; };
	virtual void Hit() = 0;

protected:
	Player* GetPlayer() const { return m_PlayerPtr; }
	bool m_AttackPlayer = false;
	const int m_AttackRange = 400;
	const int m_Speed = 250;

	EnemyState m_State = EnemyState::ALIVE;
	CollisionSingleton& m_CollisionSingleton = CollisionSingleton::GetInstance();

private:
	Player* m_PlayerPtr;
};

class Goblin final : public Enemy
{ 
public:
	explicit Goblin(Scene* scene, Player* player, const Point2f& pos);
	void Update() override;
	void Render() const override;

	void Hit() override;
private:
	Rectf m_Shape;

};