#pragma once
#include "HealthBar.h"

enum class MessageTypes
{
	HEALTH_CHANGE,
	SCORE_CHANGE,
	LEVEL_COLLISION,
	ENEMY_COLLISION,
	PICKUP_COLLISION
};
class Subject;

class IObserver
{
public:
	IObserver() = default;
	virtual ~IObserver() = default;

	IObserver(const IObserver& other) = delete;
	IObserver(IObserver&& other) = delete;
	IObserver& operator=(const IObserver& other) = delete;
	IObserver& operator=(IObserver&& other) = delete;

	virtual void OnNotify(MessageTypes message, Subject* subject) = 0;
};

class PlayerHealthBar final : public HealthBar , public IObserver
{
public:
	PlayerHealthBar(Scene* scene, const Rectf& shape, const Color4f& color, int health);
		
	virtual ~PlayerHealthBar() = default;

	void OnNotify(MessageTypes message, Subject* subject) override;
};