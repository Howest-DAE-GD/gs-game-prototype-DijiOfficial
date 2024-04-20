#include "SvgParser.h"
#include "Level.h"

Level::Level()
{
	SVGParser::GetVerticesFromSvgFile("level1test.svg", m_VerticesVec);
	for (int j = 0; j < m_VerticesVec.size(); j++)
	{
		for (int i = 0; i < m_Vertices[j].size(); i++)
		{
			m_Vertices[j][i].x *= 2;
			m_Vertices[j][i].y *= 2;
			m_Vertices[j][i].y += 90;
		}
	}
}
