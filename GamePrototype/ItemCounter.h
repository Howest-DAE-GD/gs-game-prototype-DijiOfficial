#pragma once
#include "GameObject.h"

class Texture;
class Font;
class ItemCounter final : public GameObject
{
public:
	ItemCounter(Scene* scene);
	~ItemCounter() = default;

	void Update() override {};
	void Render() const override;
	void Reset() override;
	void AddKey();
	void RemoveKey();

	void AddFinalKey();
	void RemoveFinalKey();
private:
	Font* font = nullptr;
	Texture* m_KeyTexture = nullptr;
	Texture* m_FinalKeyTexture = nullptr;
	int m_KeyCounter = 0;
	const Point2f center{ 775.f, 475.f };
	const Point2f pos{ 750.f, 465.f };
	bool m_HasFinalKey = false;
};

