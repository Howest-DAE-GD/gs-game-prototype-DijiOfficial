#include "pch.h"

#include "Bullets.h"
#include "TimeSingleton.h"
#include "utils.h"

Bullets::Bullets(const Point2f& pos, float angle, Color4f color)
	: m_Shape{ pos.x, pos.y, 8.f, 4.f }
	, m_AngleDeg{ angle }
	, m_AngleRad{ static_cast<float>(angle * M_PI / 180.0f) }
	, m_Color{ color }
{
}

void Bullets::Update()
{
	auto deltaTime = TimeSingleton::GetInstance().GetDeltaTime();

	m_Shape.left += static_cast<float>(m_Speed * cos(m_AngleRad) * deltaTime);
	m_Shape.bottom += static_cast<float>(m_Speed * sin(m_AngleRad) * deltaTime);
}

void Bullets::Render() const
{
	const float centerX = m_Shape.left + (m_Shape.width * 0.5f);
	const float centerY = m_Shape.bottom + (m_Shape.height * 0.5f);

	glPushMatrix();
	{
		glTranslatef(centerX, centerY, 0.0);
		glRotatef(m_AngleDeg, 0.0f, 0.0f, 1.0f);
		glTranslatef(-centerX, -centerY, 0.0);

		utils::SetColor(m_Color);
		utils::FillRect(m_Shape);
	}
	glPopMatrix();
}
