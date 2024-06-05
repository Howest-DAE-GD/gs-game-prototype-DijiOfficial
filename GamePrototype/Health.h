#pragma once
#include "Subject.h"

class Health final : public Subject
{
public:
	Health(int health);

	void DealDamage(int damage);
	int GetHealth() const { return m_Health; }
	void ResetHealth(int health);
	void ResetHealth();
	void AddHealth();

	int GetTotalHealth() const { return totalHealth; }
private:
	int totalHealth = 400;
	int m_Health;
};


