#pragma once
#include "pch.h"
#include "GameObject.h"

class Texture;
class Player final : public GameObject
{
public:
	Player(Scene* scene);
	//~Player() override = default;
	~Player() override { delete m_pSpritesTexture; };

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;

	void Update() override;
	void Render() const override;

	//lmao shape as no business being private If i can just publicly change it
	Rectf GetShape() const { return m_Shape; }
	void SetShape(Rectf& shape) { m_Shape = shape; }

private:
	Rectf m_Shape;
	Texture* m_pSpritesTexture;

};

