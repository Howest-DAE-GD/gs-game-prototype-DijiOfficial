#pragma once
#include "GameObject.h"

class Level final : public GameObject
{
public:
	Level(Scene* scene);
	~Level() override = default;

	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;

	void Update() override {};
	void Render() const override;

private:
	std::vector<std::vector<Point2f>> m_VerticesVec;

};

