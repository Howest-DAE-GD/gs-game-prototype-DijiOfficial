#pragma once
#include "GameObject.h"

class Player;
class Scene;
class Enemy : public GameObject
{
public:
	explicit Enemy(Scene* scene, Player* player) 
		: GameObject(scene)
		, m_PlayerPtr(player)
	{};
	~Enemy() override = default;

	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;

	void Update() override = 0;
	void Render() const override = 0;

protected:
	Player* GetPlayer() const { return m_PlayerPtr; }
	bool m_AttackPlayer = false;
	const int m_AttackRange = 400;
	int m_Speed = 250;

private:
	Player* m_PlayerPtr;
};

class Goblin final : public Enemy
{ 
public:
	explicit Goblin(Scene* scene, Player* player, const Point2f& pos);
	void Update() override;
	void Render() const override;

private:
	Rectf m_Shape;

};