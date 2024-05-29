#pragma once
#include <vector>
class Scene;

class Doors final
{ 
public:
	Doors(const std::vector<Point2f> points, const unsigned int ID);
	~Doors() = default;

    Doors(const Doors& other) = delete;
    Doors(Doors&& other) = delete;
    Doors& operator=(const Doors& other) = delete;
    Doors& operator=(Doors&& other) = delete;

	void Render() const;
    void OPENGNEEGNOOOOOR() { m_IsOpen = true; };
    bool IsOpen() const { return m_IsOpen; }
    Rectf GetShape() const { return m_Shape; }
    unsigned int GetID() const { return m_ID; }
    void Reset() { m_IsOpen = false; }
private:
	bool m_IsOpen = false;
	Rectf m_Shape;
    const unsigned int m_ID;

    Rectf CreateRectFromPoints(const std::vector<Point2f>& points)
    {
        // Ensure we have at least two points
        if (points.size() < 2)
        {
            // Return an empty rectangle or handle the error as needed
            return Rectf{ 0.0f, 0.0f, 0.0f, 0.0f };
        }

        // Get the minimum and maximum x and y values from the points
        float minX = points[0].x;
        float maxX = points[0].x;
        float minY = points[0].y;
        float maxY = points[0].y;

        for (const auto& point : points)
        {
            minX = std::min(minX, point.x);
            maxX = std::max(maxX, point.x);
            minY = std::min(minY, point.y);
            maxY = std::max(maxY, point.y);
        }

        // Fill the Rectf struct
        Rectf rect;
        rect.left = minX;
        rect.bottom = minY;
        rect.width = maxX - minX;
        rect.height = maxY - minY;

        return rect;
    }
};

