#pragma once
#include "GameObject.h"

class Camera final : public GameObject
{
public:
	Camera(Scene* scene, float width, float height);

	Camera(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera& operator=(Camera&& other) = delete;
	
	void Update() override {};
	void Render() const override;
	//void SetLevelBoundaries(const Rectf& levelBoundaries);
	Rectf GetCameraPos(const Rectf& target) const;
	//bool GetCameraLock() const;
	//void UnlockCamera();
	//void LockCamera();
	//void OffsetCamera(const int offset);
	//void ResetOffset();
	//int GetCameraOffset() const;

private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;
	int m_CameraOffset{ 0 };
	bool m_IsLocked{ 0 };

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

