#pragma once

class Bullets final
{
public:
	Bullets(const Point2f& pos, float angle, Color4f color);
	~Bullets() = default;

	Bullets(const Bullets& other) = delete;
	Bullets(Bullets&& other) = delete;
	Bullets& operator=(const Bullets& other) = delete;
	Bullets& operator=(Bullets&& other) = delete;

	void Update();
	void Render() const;
	Rectf GetShape() const { return m_Shape; }

private:
	Color4f m_Color;
	Rectf m_Shape;
	const float m_AngleDeg;
	const float m_AngleRad;
	const float m_Speed = 600.f;

};

