#include "pch.h"

#include "IObserver.h"
#include "Health.h"
#include "Scene.h"

PlayerHealthBar::PlayerHealthBar(Scene* scene, const Rectf& shape, const Color4f& color, int health)
	: HealthBar{ scene, shape, color, health }
{
};

void PlayerHealthBar::OnNotify(MessageTypes message, Subject* subject)
{
	if (message == MessageTypes::HEALTH_CHANGE)
	{
		Health* health = dynamic_cast<Health*>(subject);
		if (not health)
			return;

		m_CurrentHealth = health->GetHealth();
	}
}
