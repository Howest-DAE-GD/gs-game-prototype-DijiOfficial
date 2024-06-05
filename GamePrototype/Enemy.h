#pragma once
#include "GameObject.h"
#include "CollisionSingleton.h"
#include "Bullets.h"
#include <memory>
#include <vector>

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

enum class EnemyType
{
	TURRET = 0,
	GOBLIN,
	TROLL,
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
	void Reset() override = 0;

	EnemyState GetState() const { return m_State; };
	virtual void Hit(int damage) = 0;

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
	~Goblin() override;
	void Update() override;
	void Render() const override;
	void Reset() override;
	void Hit(int) override;
private:
	Rectf m_Shape;
	int m_Damage = 30;
	Rectf m_originalShape;
};

class Turret final : public Enemy
{
public:
	explicit Turret(Scene* scene, Player* player, const Point2f& pos);
	~Turret() override = default;

	void Update() override;
	void Render() const override;
	void Reset() override;
	void Hit(int damage) override;
private:
	Rectf m_Shape;
	int m_Damage = 20;
	Rectf m_originalShape;
	int health = 80;
	float timer = 0;
	bool attacked = false;
	std::vector<std::unique_ptr<Bullets>> m_Bullets;

};

class Test final : public Enemy
{ 
public:
	explicit Test(Scene* scene, Player* player, const Point2f& pos);
	void Update() override {};
	void Render() const override;
	void Reset() override {};
	void Hit(int) override;
private:
	Rectf m_Shape;
};