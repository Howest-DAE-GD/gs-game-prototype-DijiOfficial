#include "pch.h"
#include "Scene.h"

Camera::Camera(Scene* scene, const float width, const float height) 
	: GameObject{ scene }
	, m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{ 0.f, 0.f, 10240.f, 5760.f }
{
}
//void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
//{
//	m_LevelBoundaries = levelBoundaries;
//}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f{ (target.left + target.width / 2) - m_Width / 2, (target.bottom + target.height / 2) - m_Height / 2 };
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left) bottomLeftPos.x = m_LevelBoundaries.left + 1.f;
	if (bottomLeftPos.x + m_Width - m_CameraOffset > m_LevelBoundaries.left + m_LevelBoundaries.width or m_IsLocked)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width - m_CameraOffset;
	}

	if (bottomLeftPos.y < m_LevelBoundaries.bottom) bottomLeftPos.y = m_LevelBoundaries.bottom + 1.f;
	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.height + m_LevelBoundaries.bottom - m_Height;
	}
}

void Camera::Render() const
{
	Point2f CameraPos{ Track(GetOwner()->GetGameObject<Player>()->GetShape()) };
	Clamp(CameraPos);
	glTranslatef(-CameraPos.x, -CameraPos.y, 0);
}

Rectf Camera::GetCameraPos(const Rectf& target) const
{
	Point2f CameraPos{ Track(target) };
	Clamp(CameraPos);
	return Rectf{ CameraPos.x, CameraPos.y, m_Width, m_Height };
}

//bool Camera::GetCameraLock() const
//{
//	return m_IsLocked;
//}
//
//void Camera::UnlockCamera()
//{
//	m_IsLocked = false;
//}
//
//void Camera::LockCamera()
//{
//	m_IsLocked = true;
//}
//
//
//void Camera::OffsetCamera(const int offset)
//{
//	m_CameraOffset -= offset;
//}
//
//void Camera::ResetOffset()
//{
//	m_CameraOffset = 0;
//}
//
//int Camera::GetCameraOffset() const
//{
//	return m_CameraOffset;
//}