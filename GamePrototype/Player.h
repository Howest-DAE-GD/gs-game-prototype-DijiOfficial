#pragma once
#include "pch.h"
#include "GameObject.h"
#include "PlayerAttacks.h"

class Texture;
class Level;
class Player final : public GameObject
{
public:
	Player(Scene* scene);
	~Player() override = default;

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	void Update() override;
	void Render() const override;

	//lmao shape as no business being private If i can just publicly change it
	Rectf GetShape() const { return m_Shape; }
	void SetShape(Rectf& shape) { m_Shape = shape; }
	Point2f GetPosition() const { return Point2f{ m_Shape.left + m_Shape.width * 0.5f, m_Shape.bottom + m_Shape.height * 0.5f }; }

	void SetAngle(float angle) { m_Angle = angle; }
	bool IsColliding(const Rectf& actorShape) const;
	Point2f GetRelativeCenter() const;

	void Attack();
private:
	Rectf m_Shape;
	//Texture* m_pSpritesTexture;
	Level* m_LevelPtr;
	float m_Angle = 0.f;

	std::unique_ptr<ShootAttack> m_BasicAttack;
};

