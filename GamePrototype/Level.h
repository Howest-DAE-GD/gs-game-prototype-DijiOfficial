#pragma once
#include "utils.h"

class Level final
{
public:
	Level();
	~Level() = default;

	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;

	void Update();
	void Render();

private:
	std::vector<std::vector<Point2i>> m_VerticesVec;

};

