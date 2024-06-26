#include "pch.h"

#include "Health.h"

Health::Health(int health)
	: m_Health{ health }
{
}

void Health::DealDamage(int damage)
{
	m_Health -= damage;
	Notify(MessageTypes::HEALTH_CHANGE);
}

void Health::ResetHealth(int health)
{
	m_Health = health;
	Notify(MessageTypes::HEALTH_CHANGE);
}

void Health::ResetHealth()
{
	m_Health = totalHealth;
	Notify(MessageTypes::HEALTH_CHANGE);
}

void Health::AddHealth()
{
	totalHealth += 20;
	m_Health = totalHealth;
	Notify(MessageTypes::HEALTH_CHANGE);
}
