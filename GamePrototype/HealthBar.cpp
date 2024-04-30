#include "pch.h"

#include "HealthBar.h"
#include "Scene.h"

HealthBar::HealthBar(Scene* scene, const Rectf& shape, const Color4f& color, int health)
	: GameObject{ scene }
	, m_Shape{ shape }
	, m_Color{ color }
	, m_TotalHealth{ health }
	, m_CurrentHealth{ health }
	, m_LastFrameHealth{ 0 }
{
}

void HealthBar::Update()
{
	if (m_CurrentHealth == m_LastFrameHealth)
		return;

	m_LastFrameHealth = m_CurrentHealth;
	m_HealthBar = Rectf{ m_Shape.left, m_Shape.bottom, m_Shape.width * (static_cast<float>(m_CurrentHealth) / m_TotalHealth), m_Shape.height };
}

void HealthBar::Render() const
{
	utils::SetColor(m_Color);
	utils::FillRect(m_HealthBar);

	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	utils::DrawRect(m_Shape);
}
