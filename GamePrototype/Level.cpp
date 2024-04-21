#include "pch.h"
#include "SvgParser.h"
#include "Level.h"

Level::Level(Scene* scene)
	: GameObject{ scene }
{
	SVGParser::GetVerticesFromSvgFile("level1.svg", m_VerticesVec);
	//for (int j = 0; j < m_VerticesVec.size(); j++)
	//{
	//	for (int i = 0; i < m_VerticesVec[j].size(); i++)
	//	{
	//		m_VerticesVec[j][i].x *= 2;
	//		m_VerticesVec[j][i].y *= 2;
	//	}
	//}
}

void Level::Render()
{
	utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f });
	for (const auto& vertices : m_VerticesVec)
	{
		utils::FillPolygon(vertices);
	}

}
