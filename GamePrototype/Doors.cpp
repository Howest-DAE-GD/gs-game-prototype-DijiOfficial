#include "pch.h"
#include "Doors.h"
#include "GameObject.h"
#include "utils.h"

Doors::Doors(const std::vector<Point2f> points, const unsigned int ID)
	: m_ID{ ID }
{
	m_Shape = CreateRectFromPoints(points);
}

void Doors::Render() const
{
	if (m_IsOpen)
		return;

	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	if (m_ID == 0)
		utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	utils::FillRect(m_Shape);
	utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f });
	utils::DrawRect(m_Shape, 4.0f);
}

