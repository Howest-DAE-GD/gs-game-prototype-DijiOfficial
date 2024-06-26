#pragma once
#include "structs.h"
#include "GameObject.h"

class Scene;

class HealthBar : public GameObject
{
public:
	HealthBar(Scene* scene, const Rectf& shape, const Color4f& color, int health);
		
	virtual ~HealthBar() = default;

	void Update() override;
	void Render() const override;
	void Reset() override = 0;
	void SetActive() { m_IsActive = true; };
	void SetInactive() { m_IsActive = false; };
protected:
	int m_CurrentHealth;

private:
	Rectf m_Shape;
	Rectf m_HealthBar;
	Color4f m_Color;
	const int m_TotalHealth;
	int m_LastFrameHealth;
	bool m_IsActive = false;

};