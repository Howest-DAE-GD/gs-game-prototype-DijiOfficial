#pragma once
#include "Bullets.h"

#include <vector>
#include <memory>

class Level;

class PlayerAttacks
{
public:
	PlayerAttacks() = default;
	virtual ~PlayerAttacks() = default;

	PlayerAttacks(const PlayerAttacks& other) = delete;
	PlayerAttacks(PlayerAttacks&& other) = delete;
	PlayerAttacks& operator=(const PlayerAttacks& other) = delete;
	PlayerAttacks& operator=(PlayerAttacks&& other) = delete;

	virtual void Update() = 0;
	virtual void Render() const = 0;

	int GetDamage() const { return damage; };
	void IncreaseDamage() { damage += 10; };
protected:
	int damage{ 25 };
};

class ShootAttack final : public PlayerAttacks
{
public:
	ShootAttack(Level* level) : m_LevelPtr{ level } {};
	~ShootAttack() override = default;

	//bullet is manged here and updated from player
	void Update() override;
	void Render() const override;

	void Attack(const Point2f& pos, float angle);
	void ReduceCooldown()
	{
		if (m_AttackCoolDown > 0.f)
		{
			m_AttackCoolDown -= 0.2f;
		}
	};

private:
	Level* m_LevelPtr;
	std::vector<std::unique_ptr<Bullets>> m_Bullets;
	bool m_HasAttacked{ false };
	float timer{ 0.f };
	float m_AttackCoolDown{ 1.2f };
};